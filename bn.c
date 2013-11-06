#include "dar.h"
#include "bn.h"
#include <stdlib.h>
#include <stdint.h>

bn_t * bn_new(void) {
    bn_t * r = calloc(sizeof(*r),1);
    r->dar = dar_new(4,1);
    return r;
}

void bn_destroy(bn_t * n) {
    dar_destroy(n->dar);
    free(n);
}

bn_t * bn_scan(char *string, int len) {
    int i;
    bn_t * r = bn_new();
    for (i=0;i<len;i++) {
        bn_imulti(r,10);
        bn_shift_iadd(r,string[i]-'0',0);
    }
    return(r);
}

void bn_shift_iadd( bn_t * r,uint64_t i, int offset) {

}

void bn_shift_add( bn_t * r, bn_t * n, int offset) {

}

void bn_imulti(bn_t * n, long i) {
    int j = 0;
    bn_t * r = bn_new();
    while( i ) {
        if ( i & 1 ) {
            bn_shift_add( r, n, j );
        }
        j++;
        i>>=1;
    }
}

bn_t * bn_copy(bn_t * n) {
    bn_t * nn = malloc(sizeof(*nn));
    *nn = *n;
    nn->dar = dar_copy( n->dar );
    return nn;
}

uint32_t bn_to_uint32(bn_t * n) {
    return *(uint32_t*)dar_fetch(n->dar,0);
}

uint64_t bn_to_uint64(bn_t * n) {
    uint64_t r = 0;
    if (n->dar->element_count > 0) r += *( uint32_t * )dar_fetch(n->dar,0);
    if (n->dar->element_count > 1) r += ( ((uint64_t)*( uint32_t * )dar_fetch(n->dar,1)) << 32 );
    return r;
}

bn_t * bn_from_uint32(uint32_t i) {
    bn_t * n = bn_new();
    dar_push(n->dar,&i);
    return n;
}

bn_t * bn_from_uint64(uint64_t i) {
    uint32_t part;
    bn_t * n = bn_new();
    part = i;
    dar_push(n->dar,&part);
    part = i >> 32;
    dar_push(n->dar,&part);
    return n;
}
