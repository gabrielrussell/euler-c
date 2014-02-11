#include "dar.h"
#include "bn.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

bn_t * bn_new(void) {
    bn_t * r = calloc(sizeof(*r),1);
    r->dar = dar_new( 4, 1 );
    return r;
}

void bn_destroy(bn_t * n) {
    dar_destroy(n->dar);
    free(n);
}

bn_t * bn_scan_dar(dar_t * d) {
    return bn_scan(d->data,d->element_count);
}

bn_t * bn_scan(char *string, int len) {
    int i;
    bn_t * r = bn_new();
    bn_t * q;
    for (i=0;i<len;i++) {
        q = bn_new();
        bn_imulti(q,r,10);
        bn_iadd(q,string[i]-'0',0);
        bn_destroy(r);
        r = q;
    }
    return(r);
}

void bn_iadd( bn_t * r,uint32_t i, int shift) {
    int offset = shift / 32;
    shift = shift % 32;

    if (shift) {
        int small_part = i << shift;
        int large_part = i >> ( 32 - shift );
        bn_iadd(r,small_part, offset * 32);
        bn_iadd(r,large_part,( offset + 1 ) * 32);
    } else {
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
}

int bn_isub( bn_t * r, uint32_t i, int shift ) {
    int offset = shift / 32;
    shift = shift % 32;
    int underflow = 0;

    if ( shift ) {
        int small_part = i << shift;
        int large_part = i >> ( 32 - shift );
        bn_isub(r,small_part, offset * 32);
        bn_isub(r,large_part,( offset + 1 ) * 32);
    } else {
        uint32_t w; // word
        int o = offset;
        do {
            (void)dar_fetch(r->dar,&w,o);
            underflow = (w - i > w);
            w -= i;
            dar_store(r->dar,&w,o);
            i = underflow;
            o++;
        } while ( i && r->dar->element_count > o );
    }

    return underflow; 
}

int bn_sub( bn_t * r, bn_t * n, int shift ) {
    int i;
    uint32_t x;
    int underflow;
    for (i=0;i<n->dar->element_count;i++) {
        (void)dar_fetch(n->dar,&x,i);
        if ((underflow = bn_isub(r,x,shift + i * 32 ))) return underflow;
        /* in the case of underflow, r is trash */
    }
    return 0;
}

void bn_add( bn_t * r, bn_t * n, int shift ) {
    int i;
    uint32_t x;
    for (i=0;i<n->dar->element_count;i++) {
        (void)dar_fetch(n->dar,&x,i);
        bn_iadd(r,x,shift + i * 32 );
    }
}

bn_t * bn_multi(bn_t * n, bn_t * m) {
    bn_t * r = bn_new();
    /* implement */
    return(r);
}

void bn_imulti( bn_t * r, bn_t * n, uint32_t i ) {
    int j = 0;
    while( i ) {
        if ( i & 1 ) {
            bn_add( r, n, j );
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

void bn_trim( bn_t * a ) {
    int r;
    uint32_t w;
    while( a->dar->element_count ) {
        r = dar_fetch( a->dar, &w, a->dar->element_count - 1 );
        assert( r );
        if ( !w ) {
	    a->dar->element_count--;
	    a->dar->element_free++;
        } else {
            return;
        }
    }
}

int bn_equal(bn_t * a, bn_t * b) {
    int i;
    bn_trim(a);
    bn_trim(b);
    uint32_t aw, bw;
    if ( a->dar->element_count != b->dar->element_count ) return(0);
    for (i=0;i<a->dar->element_count;i++) {
        (void)dar_fetch(a->dar,&aw,i);
        (void)dar_fetch(b->dar,&bw,i);
        if (aw != bw) return(0);
    }
    return(1);
}

void bn_clear(bn_t * n) {
    n->dar->element_count = 0;
}

int bn_icmp(bn_t * a, uint32_t i, int shift) {
    uint32_t w;
    int o;
    uint32_t small_part;
    uint32_t large_part;

    bn_trim(a);

    int offset = shift / 32;
    shift = shift % 32;

    if (shift) {
        small_part = i << shift;
        large_part = i >> ( 32 - shift );
    } else {
        small_part = i;
        large_part = 0;
    }

    if ( large_part ) {
        if ( offset + 1 + 1 > a->dar->element_count ) return -1;
        if ( offset + 1 + 1 < a->dar->element_count ) return 1;
        (void)dar_fetch(a->dar,&w,offset + 1);
        if ( large_part > w ) return -1;
        if ( large_part < w ) return 1;
    } else {
        if ( offset + 1 < a->dar->element_count ) return 1;
    }
    if ( offset + 1 > a->dar->element_count ) return -1;
    (void)dar_fetch(a->dar,&w,offset);
    if ( small_part > w ) return -1;
    if ( small_part < w ) return 1;

    for (o = offset - 1; o >= 0; o-- ) {
        (void)dar_fetch(a->dar,&w,o);
        if (w) return 1;
    }
    return 0;
    
}

bn_t * bn_idiv( bn_t * a, uint32_t i, uint32_t * r ) {
    bn_trim(a);
    bn_t * answer = bn_new();
    bn_t * remainder = bn_copy(a);
    int b;
    for ( b = a->dar->element_count * 32; b>=0; b-- ) {
        if ( bn_icmp(remainder,i,b) != -1 ) {
            bn_isub(remainder,i,b);
            bn_iadd(answer,1,b);
        }
    }
    if (r) *r = bn_to_uint32(remainder);
    bn_destroy(remainder);
    return answer;
}

dar_t * bn_format(bn_t * a) {
    uint32_t r;
    bn_trim(a);
    dar_t * digits = dar_new( 1, 8 );
    bn_t * b = bn_copy( a );
    bn_t * c;
    while ( b->dar->element_count ) {
        c = bn_idiv( b, 10, &r );
        r += '0';
        dar_push( digits, &r );
        bn_destroy( b );
        b = c;
    }
    dar_t * rdigits = dar_reverse( digits );
    bn_destroy( b );
    dar_destroy( digits );
    return(rdigits);
}

uint64_t bn_sum_digits(bn_t * n) {
    uint64_t r = 0;
    dar_t * s = bn_format(n);
    int i; char j;
    for ( i = 0; i < s->element_count; i++ ) {
        dar_fetch(s,&j,i);
        r += ( j - '0' );
    }
    dar_destroy(s);
    return r;
}

bn_t * bn_factorial( int n ) {
    bn_t * r = bn_from_uint32(1);
    do {
        bn_t * partial = bn_new();
        bn_imulti(partial,r,n);
        bn_destroy(r);
        r = partial;
    } while ( --n );
    return r;
}
