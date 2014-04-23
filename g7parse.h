#ifndef _G7PARSE_H_
#define	_G7PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you

static void commodity_g7(const char * const s,bool exture_p,top2 &top_md){
	int quote_offset = 0;
	int volume_offset = 0;
	
	if (likely(exture_p)){
		quote_offset=1;
		volume_offset = 2;
	}

	top_md.bid1 =  atoul_8(s+sizeof(char)*(142+quote_offset));
	top_md.bidsize1 = atoul_6(s+sizeof(char)*(150+quote_offset));
	top_md.ask1 = atoul_8(s+sizeof(char)*(223+quote_offset));
	top_md.asksize1 = atoul_6(s+sizeof(char)*(231+quote_offset));
	top_md.bid2 =  atoul_8(s+sizeof(char)*(157+quote_offset));
	top_md.bidsize2 = atoul_6(s+sizeof(char)*(165+quote_offset));
	top_md.ask2 = atoul_8(s+sizeof(char)*(238+quote_offset));
	top_md.asksize2 = atoul_6(s+sizeof(char)*(246+quote_offset));
	top_md.total_bids = atoul_6(s+sizeof(char)*(135+quote_offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(216+quote_offset));
	top_md.tradeprice = atoul_8(s+sizeof(char)*(21+volume_offset));
	top_md.tradesize = atoul_6(s+sizeof(char)*(29+volume_offset));
	top_md.total_volume = atoul_7(s+sizeof(char)*(97+volume_offset));
	top_md.exchange_time = atoul_8(s+sizeof(char)*(37+volume_offset));

	int64_t side = atoul_1(s+sizeof(char)*135);
	if (side == 1){ //trade was on a BID
			top_md.tradesize *= -1;
	}
	top_md.total_volume = side;
		
}

static void future_g7(const char * const s,bool exture_p,top2 &top_md){
	int quote_offset = 0;
	int volume_offset = 0;
	
	if (likely(exture_p)){
		quote_offset=1;
		volume_offset = 2;
	}

	top_md.bid1 =  atoul_5(s+sizeof(char)*(103+quote_offset));
	top_md.bidsize1 = atoul_6(s+sizeof(char)*(108+quote_offset));
	top_md.ask1 = atoul_5(s+sizeof(char)*(169+quote_offset));
	top_md.asksize1 = atoul_6(s+sizeof(char)*(174+quote_offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(115+quote_offset));
	top_md.bidsize2 = atoul_6(s+sizeof(char)*(120+quote_offset));
	top_md.ask2 = atoul_5(s+sizeof(char)*(181+quote_offset));
	top_md.asksize2 = atoul_6(s+sizeof(char)*(186+quote_offset));
	top_md.total_bids = atoul_6(s+sizeof(char)*(96+quote_offset));
	top_md.total_asks = atoul_6(s+sizeof(char)*(162+quote_offset));
	top_md.tradeprice = atoul_5(s+sizeof(char)*(20+volume_offset));
	top_md.tradesize = atoul_6(s+sizeof(char)*(25+volume_offset));
	top_md.total_volume = atoul_7(s+sizeof(char)*(75+volume_offset));
	top_md.exchange_time = atoul_8(s+sizeof(char)*(33+volume_offset));

	int64_t side = atoul_1(s+sizeof(char)*96);
	if (side == 1)
		top_md.tradesize *= -1;
}

static void option_g7(const char * const s,bool exture_p,top2 &top_md){
	int quote_offset = 0;
	int volume_offset = 0;
	
	if (likely(exture_p)){
		quote_offset=1;
		volume_offset = 2;
	}

	top_md.bid1 =  atoul_5(s+sizeof(char)*(90+quote_offset));
	top_md.bidsize1 = atoul_7(s+sizeof(char)*(95+quote_offset));
	top_md.ask1 = atoul_5(s+sizeof(char)*(157+quote_offset));
	top_md.asksize1 = atoul_7(s+sizeof(char)*(162+quote_offset));
	top_md.bid2 =  atoul_5(s+sizeof(char)*(102+quote_offset));
	top_md.bidsize2 = atoul_7(s+sizeof(char)*(107+quote_offset));
	top_md.ask2 = atoul_5(s+sizeof(char)*(169+quote_offset));
	top_md.asksize2 = atoul_7(s+sizeof(char)*(174+quote_offset));
	top_md.total_bids = atoul_7(s+sizeof(char)*(83+quote_offset));
	top_md.total_asks = atoul_7(s+sizeof(char)*(150+quote_offset));
	top_md.tradeprice = atoul_5(s+sizeof(char)*(20+volume_offset));
	top_md.tradesize = atoul_7(s+sizeof(char)*(25+volume_offset));
	top_md.total_volume = atoul_8(s+sizeof(char)*(62+volume_offset));
	top_md.exchange_time = atoul_8(s+sizeof(char)*(34+volume_offset));

	int64_t side = atoul_1(s+sizeof(char)*83);
	if (side == 1)
		top_md.tradesize *= -1;
}


#endif