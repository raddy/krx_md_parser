#ifndef _B6PARSE_H_
#define	_B6PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you

static void commodity_b6(const char * const s,bool exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p))
		offset=2;

	top_md.bid1 =  atoul_8(s+sizeof(char)*(29+offset));
	top_md.bidsize1 = atoul_6(s+sizeof(char)*(37+offset));
	top_md.ask1 = atoul_8(s+sizeof(char)*(110+offset));
	top_md.asksize1 = atoul_6(s+sizeof(char)*(118+offset));
	top_md.bid2 =  atoul_8(s+sizeof(char)*(44+offset));
	top_md.bidsize2 = atoul_6(s+sizeof(char)*(52+offset));
	top_md.ask2 = atoul_8(s+sizeof(char)*(125+offset));
	top_md.asksize2 = atoul_6(s+sizeof(char)*(133+offset));
	
	top_md.total_bids = atoul_6(s+sizeof(char)*(22+offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(103+offset));

	top_md.tradeprice = 0;
	top_md.tradesize = 0;
	top_md.total_volume = 0;
	top_md.exchange_time = atoul_8(s+sizeof(char)*(234+offset));
}


static void future_b6(const char * const s,bool exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p))
		offset=2;

	top_md.bid1 =  atoul_5(s+sizeof(char)*(28+offset));
	top_md.bidsize1 = atoul_6(s+sizeof(char)*(33+offset));
	top_md.ask1 = atoul_5(s+sizeof(char)*(94+offset));
	top_md.asksize1 = atoul_6(s+sizeof(char)*(99+offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(40+offset));
	top_md.bidsize2 = atoul_6(s+sizeof(char)*(45+offset));
	top_md.ask2 = atoul_5(s+sizeof(char)*(106+offset));
	top_md.asksize2 = atoul_6(s+sizeof(char)*(111+offset));
	top_md.total_bids = atoul_6(s+sizeof(char)*(21+offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(87+offset));
	top_md.tradeprice = 0;
	top_md.tradesize = 0;
	top_md.total_volume = 0;
	top_md.exchange_time = atoul_8(s+sizeof(char)*(203+offset));
}

static void option_b6(const char * const s,bool exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p))
		offset=2;

	top_md.bid1 =  atoul_5(s+sizeof(char)*(29+offset));
	top_md.bidsize1 = atoul_7(s+sizeof(char)*(34+offset));
	top_md.ask1 = atoul_5(s+sizeof(char)*(96+offset));
	top_md.asksize1 = atoul_7(s+sizeof(char)*(101+offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(41+offset));
	top_md.bidsize2 = atoul_7(s+sizeof(char)*(46+offset));
	top_md.ask2 = atoul_5(s+sizeof(char)*(108+offset));
	top_md.asksize2 = atoul_7(s+sizeof(char)*(113+offset));
	top_md.total_bids = atoul_7(s+sizeof(char)*(22+offset));
	top_md.total_asks = atoul_7(s+sizeof(char)*(89+offset));
	top_md.tradeprice = 0;
	top_md.tradesize = 0;
	top_md.total_volume = 0;
	top_md.exchange_time = atoul_8(s+sizeof(char)*(206+offset));
}


#endif