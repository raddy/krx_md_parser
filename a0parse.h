#ifndef _A0PARSE_H_
#define	_A0PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void parse_a0(const char * const s,short exture_p,top2 &top_md){
	if (likely(exture_p>=1))
		top_md.exchange_time = atoul_8(s+sizeof(char)*382);
	else
		top_md.exchange_time = atoul_8(s+sizeof(char)*381);
}

static void parse_a0_cash(const char * const s,short exture_p,top2 &top_md){
	if (likely(exture_p>=1)){
		top_md.exchange_time = atoul_8(s+sizeof(char)*388);
		top_md.tradeprice = atoul_12(s+sizeof(char)*396) / 10;
	}
	else{
		top_md.exchange_time = atoul_8(s+sizeof(char)*388);
		top_md.tradeprice = atoul_12(s+sizeof(char)*396) /10 ;
	}
}

static inline void parse_issue_code_a0(const char * const s,top2 &res){
	memcpy(res.symbol,s+sizeof(char)*18,sizeof(char)*12);
	res.symbol[12] = 0;
}

#endif