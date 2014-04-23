#ifndef _QUICKBBO_H_
#define	_QUICKBBO_H_

#include <string.h>
#include "b6parse.h"
#include "g7parse.h"
#include "a3parse.h"
#include "b2parse.h"
#include "a0parse.h"
#include "b7parse.h"
#include "a1parse.h"

using namespace std;


__BEGIN_DECLS

//Msg Type Codes as ushort
#define B6 13890
#define G7 14151
#define A3 13121
#define B2 12866
#define A0 12353
#define A1 12609
#define B7 14146

//Product Type Codes as ushort
#define FUTURE 12592
#define OPTION 13104
#define ELW 12848


static inline uint16 msg_type(const char *s){
	return ((uint16 *)s)[0];
}

static inline uint16 product_type(const char *s){
	return ((uint16 *)s)[1];
}

static inline void parse_msg_type(const char * const s,top2 &res){
	memcpy(res.msg_type,s,sizeof(char)*2);
	res.msg_type[2] = 0;
}

static inline void parse_issue_code(const char * const s,top2 &res){
	memcpy(res.symbol,s+sizeof(char)*5,sizeof(char)*12);
	res.symbol[12] = 0;
}

static inline int ic_is_elw(const char * s){
	return s[0]=='K' && s[1] == 'R' && s[2] == 'A';
}


static inline int market_type_cash(const char *s){
	return (s[4] != '4');
}


/* Laziest possible code to parse a msg
	* Just parses B6s for now and 

*/
static int parse_msg(const char *s,short exture_plus,top2 &result){
	

	//ignore non derivatives md for now
	if ((s[4] != '4') && (s[4]!='6') && s[4]!= '1')
		return 0;
	short commodity_flag = (s[4] == '6');
	short equity_flag = (s[4] == '1');

	bool exture_p = bool(exture_plus);
		
	parse_msg_type(s,result);
	
	switch(msg_type(s)){
		case B6:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					if (commodity_flag>0)
						commodity_b6(s,exture_p,result);
					else if (equity_flag>0)
						return 0;
					else
						future_b6(s,exture_p,result);
					return 1;
				case OPTION:
					option_b6(s,exture_p,result);
					return 1;
				default:
					return 0;
			}
		case G7:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					if (commodity_flag>0)
						commodity_g7(s,exture_p,result);
					else
						future_g7(s,exture_p,result);
					return 1;
				case OPTION:
					option_g7(s,exture_p,result);
					return 1;
				default:
					return 0;
			}
		case A3:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					if (commodity_flag>0)
						commodity_a3(s,exture_p,result);
					else if (equity_flag>0)
						return 0;
					else
						future_a3(s,exture_p,result);
					return 1;
				case OPTION:
					option_a3(s,exture_p,result);
					return 1;
				case ELW:
					elw_a3(s,exture_p,result);
					return 1;
				default:
					return 0;
			}
		case B2:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case FUTURE:
					if (commodity_flag>0)
						commodity_b2(s,exture_p,result);
					else if (equity_flag>0)
						return 0;
					else
						future_b2(s,exture_p,result);
					return 1;
				case OPTION:
					option_b2(s,exture_p,result);
					return 1;
				default:
					return 0;
			}
		case B7:
			parse_issue_code(s,result);
			switch(product_type(s)){
				case ELW:
					elw_b7(s,exture_p,result);
				default:
					return 0;
			}
		case A1:
			parse_issue_code(s,result);
			if (!ic_is_elw(result.symbol)){
					return 0;
			}
			parse_a1_cash(s,exture_p,result);
			return 4;
		case A0:
			if (equity_flag>0){
				parse_issue_code(s,result);
				if (!ic_is_elw(result.symbol)){
					return 0;
				}
				parse_a0_cash(s,exture_p,result);
				return 3;
			}
			parse_issue_code_a0(s,result);
			switch(product_type(s)){
				case FUTURE:
					parse_a0(s,exture_p,result);
					break;
				case OPTION:
					parse_a0(s,exture_p,result);
					break;
				default:
					return 0;

			}
			return 2;
		default:
			return 0;
	}
}


__END_DECLS

#endif