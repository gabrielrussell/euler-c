#ifndef BN_H
#define BN_H
#include "dar.h"
#include <stdint.h>

typedef struct bn {
    dar_t * dar;
    int negative; //uhh
} bn_t;

bn_t * bn_new(void) ;

bn_t * bn_scan(char *string, int len) ;

void bn_imulti( bn_t * r, bn_t * n, uint32_t i ) ;

bn_t * bn_multi(bn_t * n, bn_t * m) ;

void bn_iadd(bn_t * r,uint32_t i, int offset) ;

void bn_add(bn_t * r, bn_t * n, int offset) ;

bn_t * bn_copy(bn_t * n) ;

void bn_destroy(bn_t * n) ;

bn_t * bn_copy(bn_t * n) ;

uint32_t bn_to_uint32(bn_t * n) ;

uint64_t bn_to_uint64(bn_t * n) ;

bn_t * bn_from_uint32(uint32_t i) ;

bn_t * bn_from_uint64(uint64_t i) ;

void bn_offset_iadd( bn_t * r,uint32_t i, int offset) ;

void bn_clear(bn_t * n) ;

int bn_isub( bn_t * r, uint32_t i, int shift ) ;

int bn_sub( bn_t * r, bn_t * n, int shift ) ;

int bn_equal(bn_t * a, bn_t * b) ;

int bn_icmp(bn_t * a, uint32_t i, int shift) ;

bn_t * bn_idiv( bn_t * a, uint32_t i, uint32_t * r ) ;

dar_t * bn_format(bn_t * a) ;

bn_t * bn_scan_dar(dar_t * d) ;

#endif
