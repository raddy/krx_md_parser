#ifndef IPUTIL_H
#define IPUTIL_H

unsigned int ip_to_int (const char * ip) {
    
    int i;
    char c;
    const char * begin;
	unsigned res = 0;
    
    begin = ip;

    for (i = 0; i < 4; i++) {
        
        int n = 0;
        while (1) {
            c = *begin;
            begin++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                return 0;
            }
        }
        if (n >= 256) {
            return 0;
        }
        res *= 256;
        res += n;
    }
    return res;
}

char* ip_to_string(unsigned int ip)
{
  char result[16];

  sprintf(result, "%u.%u.%u.%u",
    (ip >> 24) & 0xFF,
    (ip >> 16) & 0xFF,
    (ip >>  8) & 0xFF,
    (ip      ) & 0xFF);

  return result;
}

#endif