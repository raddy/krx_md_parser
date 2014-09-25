#ifndef _A3PARSE_H_
#define	_A3PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you

static void commodity_a3(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=2;


	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.total_bids = 0;
	top_md.total_asks = 0;
	top_md.tradeprice = atoul_8(s+sizeof(char)*(21+offset));
	top_md.tradesize = atoul_6(s+sizeof(char)*(29+offset));
	top_md.total_volume = atoul_7(s+sizeof(char)*(97+offset));
	top_md.exchange_time = atoul_8(s+sizeof(char)*(37+offset));

	int64_t side = atoul_1(s+sizeof(char)*135);
	if (side == 1)
		top_md.tradesize *= -1;
}

static void future_a3(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=2;

	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.total_bids = 0;
	top_md.total_asks = 0;
	top_md.tradeprice = atoul_5(s+sizeof(char)*(20+offset));
	top_md.tradesize = atoul_6(s+sizeof(char)*(25+offset));
	top_md.total_volume = atoul_7(s+sizeof(char)*(75+offset));
	top_md.exchange_time = atoul_8(s+sizeof(char)*(33+offset));

	int64_t side = atoul_1(s+sizeof(char)*96);
	if (exture_p==2)
		side = atoul_1(s+sizeof(char)*103);
	if (side == 1)
		top_md.tradesize *= -1;
}

static void option_a3(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=2;

	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.total_bids = 0;
	top_md.total_asks = 0;
	top_md.tradeprice = atoul_5(s+sizeof(char)*(20+offset));
	top_md.tradesize = atoul_7(s+sizeof(char)*(25+offset));
	top_md.total_volume = atoul_8(s+sizeof(char)*(62+offset));
	top_md.exchange_time = atoul_8(s+sizeof(char)*(34+offset));

	int64_t side = atoul_1(s+sizeof(char)*83);
	if (exture_p==2)
		side = atoul_1(s+sizeof(char)*91);
	if (side == 1)
		top_md.tradesize *= -1;


}

static void elw_a3(const char * const s,short exture_p,top2 &top_md){

	top_md.bid1 =  0;
	top_md.bidsize1 = 0;
	top_md.ask1 = 0;
	top_md.asksize1 = 0;
	top_md.bid2 =  0;
	top_md.bidsize2 = 0;
	top_md.ask2 = 0;
	top_md.asksize2 = 0;
	top_md.total_bids = 0;
	top_md.total_asks = 0;
	top_md.tradeprice = atoul_9(s+sizeof(char)*(34));
	top_md.tradesize = atoul_10(s+sizeof(char)*(43));
	top_md.total_volume = atoul_12(s+sizeof(char)*(82));
	top_md.exchange_time = 0;

	int64_t side = atoul_1(s+sizeof(char)*112);
	if (side == 2)
		top_md.tradesize *= -1;
}


#endif