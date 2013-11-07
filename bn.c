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
    bn_t * q;
    for (i=0;i<len;i++) {
        q = bn_imulti(r,10);
        bn_offset_iadd(q,string[i]-'0',0);
        bn_destroy(r);
        r = q;
    }
    return(r);
}

void bn_shift_iadd( bn_t * r,uint64_t i, int shift) {
    int word_offset = shift / 32;
    int bit_offset = shift % 32;
    int small_part = i << bit_offset;
    int large_part = i >> ( 32 - bit_offset );
    bn_offset_iadd(r,small_part,word_offset);
    bn_offset_iadd(r,large_part,word_offset+1);
}

void bn_offset_iadd( bn_t * r,uint32_t i, int offset) {
    uint32_t zero = 0;
    uint32_t w; // word
    int overflow = 0;
    int o = offset;
    do {
        /* first extend the number left-wise to accommodate the new data */
        while ( r->dar->element_count < o + 1 ) dar_push(r->dar, &zero );
        (void)dar_fetch(r->dar,&w,o);
        overflow = (w + i < w);
        w += i;
        dar_store(r->dar,&w,o);
        i = overflow;
        o++;
    } while (i);
}

void bn_shift_add( bn_t * r, bn_t * n, int offset) {
    int i;
    uint32_t x;
    for (i=0;i<n->dar->element_count;i++) {
        (void)dar_fetch(n->dar,&x,i);
        bn_shift_iadd(r,x,offset + i * 32 );
    }
}

bn_t * bn_multi(bn_t * n, bn_t * m) {
    bn_t * r = bn_new();
    return(r);
}

bn_t * bn_imulti(bn_t * n, int i) {
    int j = 0;
    bn_t * r = bn_new();
    while( i ) {
        if ( i & 1 ) {
            bn_shift_add( r, n, j );
        }
        j++;
        i>>=1;
    }
    return r;
}

bn_t * bn_copy(bn_t * n) {
    bn_t * nn = malloc(sizeof(*nn));
    *nn = *n;
    nn->dar = dar_copy( n->dar );
    return nn;
}

uint32_t bn_to_uint32(bn_t * n) {
    uint32_t v;
    dar_fetch(n->dar,&v,0);
    return v;
}

uint64_t bn_to_uint64(bn_t * n) {
    uint64_t r = 0;
    uint32_t v;
    if (n->dar->element_count > 0) {
        dar_fetch(n->dar,&v,0);
        r += v;
    }
    if (n->dar->element_count > 1) {
        dar_fetch(n->dar,&v,1);
        r += (uint64_t)v << 32;
    }
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

void bn_zero(bn_t * n) {
    n->dar->element_count = 0;
}
