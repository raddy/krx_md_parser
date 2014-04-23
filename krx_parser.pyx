import numpy as np
import pandas as pd
import sys
cimport cython
cimport numpy as np
from libcpp.string cimport string

cdef extern from "stdint.h" nogil:
    ctypedef  signed long  int64_t 

cdef extern from "quickutil.h" nogil:
    struct top2:
        int64_t bid1
        int64_t bidsize1
        int64_t ask1
        int64_t asksize1
        int64_t bid2
        int64_t bidsize2
        int64_t ask2
        int64_t asksize2
        int64_t total_bids
        int64_t total_asks
        int64_t tradeprice
        int64_t tradesize
        int64_t total_volume
        int64_t exchange_time
        int64_t seq
        char symbol[13]
        char msg_type[3]

    struct tick:
        top2 md
        short code
        int64_t ts
        int64_t src_prt
        int64_t dst_prt
        int64_t src_ip
        int64_t dst_ip

cdef extern from "<vector>" namespace "std":
    cdef cppclass bbos "std::vector<tick>":
        bbos()
        tick& operator[] (const int64_t& k)
        int size()

cdef extern from "krxparser.cpp":
    struct ip:
        pass
    cdef cppclass MD:
        bbos tick_data
    MD read_pcap(string,string,int)

@cython.cdivision(True)
@cython.boundscheck(False)
cdef bbos_to_df(bbos dat):
    cdef:
        int i =0,j=0, dlen = dat.size()
        np.ndarray packet_info = np.ndarray((dlen,),
            dtype=[('symbol','a13'),('bid1','i8'),('bidsize1','u4'),('ask1','i8'),('asksize1','u4'),
                   ('bid2','i8'),('bidsize2','u4'),('ask2','i8'),('asksize2','u4'),
                   ('total_bids','u4'),('total_asks','u4'),('msg_type','a3'),
                   ('tradeprice','i8'),('tradesize','i8'),('total_volume','u4'),('exchange_time','u4'),('seq','i4'),
                   ('source_port','u4'),('source_ip','u4'), ('dest_port','u4'),('dest_ip','u4')])
        np.ndarray[long,ndim=1] times = np.zeros(dlen,dtype=long)

    for i from 0<=i<dlen:

        if dat[i].code ==1:
            times[j] = dat[i].ts
            packet_info[j][0] = dat[i].md.symbol
            packet_info[j][1] = dat[i].md.bid1
            packet_info[j][2] = dat[i].md.bidsize1
            packet_info[j][3] = dat[i].md.ask1
            packet_info[j][4] = dat[i].md.asksize1
            packet_info[j][5] = dat[i].md.bid2
            packet_info[j][6] = dat[i].md.bidsize2
            packet_info[j][7] = dat[i].md.ask2
            packet_info[j][8] = dat[i].md.asksize2 
            packet_info[j][9] = dat[i].md.total_bids
            packet_info[j][10] = dat[i].md.total_asks
            packet_info[j][11] = dat[i].md.msg_type
            packet_info[j][12] = dat[i].md.tradeprice 
            packet_info[j][13] = dat[i].md.tradesize
            packet_info[j][14] = dat[i].md.total_volume
            packet_info[j][15] = dat[i].md.exchange_time
            packet_info[j][16] = dat[i].md.seq

            packet_info[j][17] = dat[i].src_prt
            packet_info[j][18] = dat[i].src_ip
            packet_info[j][19] = dat[i].dst_prt
            packet_info[j][20] = dat[i].src_ip
            j+=1
    df =  pd.DataFrame(packet_info,index=times,columns=packet_info.dtype.names)
    return df.query('index>0')

@cython.cdivision(True)
@cython.boundscheck(False)
cdef bbos_to_dicts(bbos dat):
    cdef:
        int i =0,j=0, dlen = dat.size()
    
    expiration_dict = dict()
    strike_dict = dict()

    for i from 0<=i<dlen:
        if dat[i].code == 2:
            python_code = dat[i].md.symbol
            if python_code[2:6]=='4201' or python_code[2:6]=='4301':
                rawstrike = float(python_code[8:11])
            if rawstrike % 5 !=0:
                rawstrike+=.5
            strike_dict[python_code] = rawstrike*100
            expiration_dict[python_code] = str(dat[i].md.exchange_time)
        elif dat[i].code == 3:
            python_code = dat[i].md.symbol
            strike_dict[python_code] = dat[i].md.tradeprice
        elif dat[i].code == 4:
            python_code = dat[i].md.symbol
            last_trading_day  = str(dat[i].md.exchange_time)
            expiration_dict[python_code] = last_trading_day 
    return expiration_dict,strike_dict

def parse_pcap(fn,target,quit):
    cdef MD mymd = read_pcap(fn,target,quit)
    # first rip the MD out of the pcap
    df = (bbos_to_df(mymd.tick_data))
    # now go back through and build the expiration dict
    expiry_dict,strike_dict = bbos_to_dicts(mymd.tick_data)
    return [df,expiry_dict,strike_dict]

