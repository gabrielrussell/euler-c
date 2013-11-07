#include <stdint.h>

uint64_t isqrt( uint64_t n ) {
    uint64_t bit;
    uint64_t r = 0;
    bit = 1ULL << 32;
    while (bit>n) bit >>= 1; //skip past bits that we know can't be in the answer

    while (bit) {
        if ( (r|bit) * (r|bit) <= n ) r |= bit; //set the bit if it doesn't make the answer too large
        bit >>= 1;
    }
    return r;
}

