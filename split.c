#include <string.h>

int split(char * string, int length, char seperator, int(*callback)(void *,char *, int), void * context ) {
    char * s = string; 
    int l = length;
    char * m;
    int r;
    while (l>0) {
        if ( ! ( m = memchr(s,seperator,l) ) ) m = s+l;
        if ( ( r = callback(context,s,m-s) ) ) return r;
        l -= 1 + m - s;
        s = m + 1;
    }
    return 0;
}
