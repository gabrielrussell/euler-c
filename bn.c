#include "dar.h"

typedef struct bn {
    dar_t data;
    int negative;
} bn_t;

bn_t * bn_new(void) {
    bn_t * r = calloc(sizeof(*r),1);
    dar_init(r,4,1);
    return r;
}

bn_t * bn_scan(char *string, int len) {
    int i;
    bn_t * r = bn_new();
    for (i=0;i<len;i++) {
        bn_imulti(r,10);
        bn_iadd(r,string[i]);
    }
    return(r);
}

void bn_imulti(bn_t * n, long i) {
    int j = 0;
    bn_t * r;
    while( i ) {
        if ( i & 1 ) {
            bn_shift_add( r, n, j );
        }
        j++;
        i>>1;
    }
}

bn_t * bn_copy(bn_t * n) {
    bn_t * nn = malloc(sizeof(*nn));
    *nn = *n;
    nn->data = bn_copy( n->data );
}
