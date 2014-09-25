#ifndef _H1PARSE_H_
#define	_H1PARSE_H_

#include "quickutil.h"

//copy pasting is bad for you
static void commodity_h1(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=1;

	top_md.total_volume = atoul_4(s+sizeof(char)*(32));
	top_md.bid1 =  atoul_18(s+sizeof(char)*(54));
	top_md.bidsize1 = atoul_9(s+sizeof(char)*(36));
	top_md.ask1 = atoul_18(s+sizeof(char)*(72));
	top_md.asksize1 = atoul_9(s+sizeof(char)*(45));
	top_md.tradesize = 0;
}

static void future_h1(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=1;

	top_md.total_volume = atoul_4(s+sizeof(char)*(32));
	top_md.bid1 =  atoul_18(s+sizeof(char)*(54));
	top_md.bidsize1 = atoul_9(s+sizeof(char)*(36));
	top_md.ask1 = atoul_18(s+sizeof(char)*(72));
	top_md.asksize1 = atoul_9(s+sizeof(char)*(45));
	top_md.tradesize = 0;

}

static void option_h1(const char * const s,short exture_p,top2 &top_md){
	int offset = 0;
	if (likely(exture_p>=1))
		offset=1;

	top_md.total_volume = atoul_4(s+sizeof(char)*(33));
	top_md.bid1 =  atoul_18(s+sizeof(char)*(55));
	top_md.bidsize1 = atoul_9(s+sizeof(char)*(37));
	top_md.ask1 = atoul_18(s+sizeof(char)*(73));
	top_md.asksize1 = atoul_9(s+sizeof(char)*(46));
	if (s[32]=='C')
		top_md.tradesize = 1;
	else
		top_md.tradesize = 2;
}


#endif