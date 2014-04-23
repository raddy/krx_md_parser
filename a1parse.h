#ifndef _A1PARSE_H_
#define	_A1PARSE_H_

#include "quickutil.h"


static void parse_a1_cash(const char * const s,bool exture_p,top2 &top_md){
	top_md.exchange_time = atoul_8(s+sizeof(char)*332);

}


#endif