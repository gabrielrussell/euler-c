#include "dar.h"

typedef struct bn {
    dar_t data;
    int negative;
} bn_t;

bn_t * bn_new(void) ;

bn_t * bn_scan(char *string, int len) ;

void bn_imulti(bn_t * n, long i) ;

bn_t * bn_copy(bn_t * n) ;
