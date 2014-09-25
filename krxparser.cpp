#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <map>
#include <set>
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <stdbool.h>

#include "iputil.h"
#include "quickbbo.h"

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

#define ETHER_TYPE_IP (0x0800)
#define ETHER_TYPE_8021Q (0x8100)

#define SEP2014 1409529600000000000

#define TH_SYNACK 0x012

void printBBO(const struct top2 &bbo){
	std::cout<<bbo.symbol<<" ";
	std::cout<<bbo.bid1<<" ";
	std::cout<<bbo.ask1<<std::endl;
}

int  processUDP(unsigned int & pktNum, const long &ts, const struct ip *ipHdr, int pktLen, struct tick &bbo, short exture_version) {
	// Get to the data.
	int ipHdrLen(ipHdr->ip_hl * 4);
	const struct udphdr *udpHdr((struct udphdr *) ((char *) ipHdr + ipHdrLen));
	
	#if defined(__linux__)
		unsigned short srcPort(ntohs(udpHdr->source));
		unsigned short destPort(ntohs(udpHdr->dest));
		unsigned ip_source(ntohl((ipHdr->ip_src).s_addr));
		unsigned ip_dest(ntohl((ipHdr->ip_dst).s_addr));
	#elif defined(__APPLE__) && defined(__MACH__)
		unsigned short srcPort(ntohs(udpHdr->uh_sport));
		unsigned short destPort(ntohs(udpHdr->uh_dport));
		unsigned ip_source(ntohl((ipHdr->ip_src).s_addr));
		unsigned ip_dest(ntohl((ipHdr->ip_dst).s_addr));
	#endif

	unsigned short udpHdrLen(sizeof(udphdr));
	int pktDataLen(pktLen - udpHdrLen - ipHdrLen);
	const char *pktData(((char *) udpHdr) + udpHdrLen);
	std::string pktDataStr(pktData, pktDataLen);

	bbo.ts = ts;

	if (ts>SEP2014)
		exture_version=2;
	else
		exture_version=1;

	bbo.src_prt = int64_t(srcPort);
	bbo.dst_prt = int64_t(destPort);
	bbo.src_ip = int64_t(ip_source);
	bbo.dst_ip = int64_t(ip_dest);

	bbo.code = parse_msg(pktDataStr.c_str(),exture_version,bbo.md);
	if (bbo.code == 9)
		std::cout<<"Found H1\n";
	return bbo.code;
}	

class MD{
	public:
		std::vector<tick> tick_data;

};


MD read_pcap(std::string inFile,std::string target_ip,int quit_early, short exture_version){
	
	unsigned target = ip_to_int(target_ip.c_str());
	unsigned their_ip;
	long raw_time; 
	long n = 20000000;
	//struct top2 *bbos = (struct top2 *)malloc(n*sizeof(struct top2));
	printf("Parsing pcap file %s ... with target:: %u", inFile.c_str(),target);
	pcap_t *handle;
	char errbuf[PCAP_ERRBUF_SIZE]; //not sure what to do with this, oh well
	handle = pcap_open_offline(inFile.c_str(), errbuf);   //call pcap library function


	MD md;


	if (handle == NULL) {
		fprintf(stderr,"Couldn't open pcap file %s: %s\n", inFile.c_str(), errbuf);
		return(md);
	}
	
	
	md.tick_data.reserve(20000000);

	const u_char *packet;
	struct pcap_pkthdr header;
	unsigned int pktNum(0);

	while (packet = pcap_next(handle, &header)) {
		u_char *pktPtr = (u_char *)packet;

		

		// Parse the header, grabbing the type field.
		int ether_type = ((int)(pktPtr[12]) << 8) | (int)pktPtr[13];
		int ether_offset = 0;

		if (ether_type == ETHER_TYPE_IP) { //most common
			ether_offset = 14;
		} else {
			continue;
		}

		raw_time = header.ts.tv_sec * 1000000000 +header.ts.tv_usec*1000;


		//parse the IP header
		pktPtr += ether_offset;  //skip past the Ethernet II header
		struct ip *ipHdr = (struct ip *)pktPtr; //point to an IP header structure
		int pktLen = ntohs(ipHdr->ip_len);
		int msg_type; //used to branch a0/a1/normal md accordingly

		tick bbo;
		
		if (ipHdr->ip_p == 17) { //UDP BRO
				//TCP MESSAGE EITHER TO OR FROM OUR TARGET IP
				msg_type = processUDP(pktNum,raw_time,ipHdr,pktLen,bbo,exture_version);
				if ( msg_type >= 1){
					//bbos[pktNum] = bbo;
					md.tick_data.push_back(bbo);
				}
		}

		pktNum++; //increment number of packets seen
		if (unlikely(quit_early>0)&&(unlikely(pktNum>quit_early) || unlikely(pktNum>n)))
			break;
	}
	printf("\nParsed %u packets\n",pktNum);
	return md;
	pcap_close(handle);
}	