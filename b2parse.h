#ifndef _B2PARSE_H_
#define	_B2PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void commodity_b2(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=1;

	top_md.bid1 =  atoul_8(s+sizeof(char)*(123+offset));
	top_md.bidsize1 = atoul_6(s+sizeof(char)*(131+offset));
	top_md.ask1 = atoul_8(s+sizeof(char)*(104+offset));
	top_md.asksize1 = atoul_6(s+sizeof(char)*(112+offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(161+offset));
	top_md.bidsize2 = atoul_6(s+sizeof(char)*(169+offset));
	top_md.ask2 = atoul_8(s+sizeof(char)*(142+offset));
	top_md.asksize2 = atoul_6(s+sizeof(char)*(150+offset));

	top_md.total_bids = atoul_6(s+sizeof(char)*(304+offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(293+offset));

	top_md.tradeprice = atoul_8(s+sizeof(char)*(21));
	top_md.tradesize = 0;
	top_md.total_volume = atoul_7(s+sizeof(char)*(81));
	top_md.exchange_time = 0;
}

static void future_b2(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=1;

	top_md.bid1 =  atoul_5(s+sizeof(char)*(98+offset));
	top_md.bidsize1 = atoul_6(s+sizeof(char)*(103+offset));
	top_md.ask1 = atoul_5(s+sizeof(char)*(82+offset));
	top_md.asksize1 = atoul_6(s+sizeof(char)*(87+offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(130+offset));
	top_md.bidsize2 = atoul_6(s+sizeof(char)*(135+offset));
	top_md.ask2 = atoul_5(s+sizeof(char)*(114+offset));
	top_md.asksize2 = atoul_6(s+sizeof(char)*(119+offset));

	top_md.total_bids = atoul_6(s+sizeof(char)*(252+offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(241+offset));

	top_md.tradeprice = atoul_5(s+sizeof(char)*(20));
	top_md.tradesize = 0;
	top_md.total_volume = atoul_7(s+sizeof(char)*(62));
	top_md.exchange_time = 0;
}

static void option_b2(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=1;

	top_md.bid1 =  atoul_5(s+sizeof(char)*(84+offset));
	top_md.bidsize1 = atoul_7(s+sizeof(char)*(89+offset));
	top_md.ask1 = atoul_5(s+sizeof(char)*(68+offset));
	top_md.asksize1 = atoul_7(s+sizeof(char)*(73+offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(116+offset));
	top_md.bidsize2 = atoul_7(s+sizeof(char)*(121+offset));
	top_md.ask2 = atoul_5(s+sizeof(char)*(100+offset));
	top_md.asksize2 = atoul_7(s+sizeof(char)*(105+offset));

	top_md.total_bids = atoul_6(s+sizeof(char)*(240+offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(228+offset));

	top_md.tradeprice = atoul_5(s+sizeof(char)*(20));
	top_md.tradesize = 0;
	top_md.total_volume = atoul_8(s+sizeof(char)*(49));
	top_md.exchange_time = 0;
}


#endif