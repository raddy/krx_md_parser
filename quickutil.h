#pragma once
#include <stdbool.h>
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)
typedef unsigned short uint16;
#if defined(__linux__)
	typedef long int64_t;
#elif defined(__APPLE__) && defined(__MACH__)
	typedef long long int64_t;
#endif


static inline int64_t atoul_12(const char * const s){
    return int64_t(s[0]-'0')*100000000000
    		+int64_t(s[1]-'0')*10000000000+int64_t(s[2]-'0')*1000000000+int64_t(s[3]-'0')*100000000
    		+int64_t(s[4]-'0')*10000000+(s[5]-'0')*1000000+(s[6]-'0')*100000
    		+(s[7]-'0')*10000+(s[8]-'0')*1000+(s[9]-'0')*100+(s[10]-'0')*10
    		+(s[11]-'0');
}

static inline int64_t atoul_10(const char * const s){
    return int64_t(s[0]-'0')*1000000000+int64_t(s[1]-'0')*100000000
    		+(s[2]-'0')*10000000+(s[3]-'0')*1000000+(s[4]-'0')*100000
    		+(s[5]-'0')*10000+(s[6]-'0')*1000+(s[7]-'0')*100+(s[8]-'0')*10
    		+(s[9]-'0');
}

static inline int64_t atoul_9(const char * const s){
    return int64_t(s[0]-'0')*100000000
    		+(s[1]-'0')*10000000+(s[2]-'0')*1000000+(s[3]-'0')*100000
    		+(s[4]-'0')*10000+(s[5]-'0')*1000+(s[6]-'0')*100+(s[7]-'0')*10
    		+(s[8]-'0');
}

static inline int64_t atoul_8(const char * const s){
    return (s[0]-'0')*10000000+(s[1]-'0')*1000000+(s[2]-'0')*100000
    		+(s[3]-'0')*10000+(s[4]-'0')*1000+(s[5]-'0')*100+(s[6]-'0')*10
    		+(s[7]-'0');
}

static inline int64_t atoul_7(const char * const s){
    return (s[0]-'0')*1000000+(s[1]-'0')*100000+(s[2]-'0')*10000
    		+(s[3]-'0')*1000+(s[4]-'0')*100+(s[5]-'0')*10+(s[6]-'0');
}

static inline int64_t atoul_6(const char * const s){
    return (s[0]-'0')*100000+(s[1]-'0')*10000+(s[2]-'0')*1000+(s[3]-'0')*100+(s[4]-'0')*10+(s[5]-'0');
}

static inline int64_t atoul_5(const char * const s){
    return (s[0]-'0')*10000+(s[1]-'0')*1000+(s[2]-'0')*100+(s[3]-'0')*10+(s[4]-'0');
}

static inline int64_t atoul_1(const char * const s){
    return (s[0]-'0');
}

struct bbo{
	int64_t bid1;
	int64_t bidsize1;
	int64_t ask1;
	int64_t asksize1;
	int64_t tradeprice;
	int64_t tradesize;
	int64_t total_volume;
	int64_t exchange_time;
	char symbol[13];
	char msg_type[3];
};

typedef struct top2{
	int64_t bid1;
	int64_t bidsize1;
	int64_t ask1;
	int64_t asksize1;
	int64_t bid2;
	int64_t bidsize2;
	int64_t ask2;
	int64_t asksize2;
	int64_t total_bids;
	int64_t total_asks;
	int64_t tradeprice;
	int64_t tradesize;
	int64_t total_volume;
	int64_t exchange_time;
	int64_t seq;	
	char symbol[13];
	char msg_type[3];
} top2;

typedef struct tick{
	top2 md;
	int64_t ts;
	int64_t src_prt;
	int64_t dst_prt;
	int64_t src_ip;
	int64_t dst_ip;
	short code;
} tick;