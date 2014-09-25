#ifndef _B7PARSE_H_
#define	_B7PARSE_H_

#include "quickutil.h"

static void elw_b7(const char * const s,short exture_p,top2 &top_md){

	top_md.bid1 =  atoul_9(s+sizeof(char)*(43));
	top_md.bidsize1 = atoul_12(s+sizeof(char)*(64));
	top_md.ask1 = atoul_9(s+sizeof(char)*(34));
	top_md.asksize1 = atoul_12(s+sizeof(char)*(52));
	top_md.bid2 =  atoul_9(s+sizeof(char)*(109));
	top_md.bidsize2 = atoul_12(s+sizeof(char)*(130));
	top_md.ask2 = atoul_9(s+sizeof(char)*(100));
	top_md.asksize2 = atoul_12(s+sizeof(char)*(118));
	top_md.total_bids = 0;
	top_md.total_asks = 0;
	top_md.tradeprice = atoul_9(s+sizeof(char)*(770));
	top_md.tradesize = atoul_12(s+sizeof(char)*(779));
	top_md.total_volume = atoul_12(s+sizeof(char)*(22));
	top_md.exchange_time = 0;

	int64_t side = atoul_1(s+sizeof(char)*791);
	if (side == 1)
		top_md.tradesize *= -1;

}

#endif