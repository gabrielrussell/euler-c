#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t isqrt( uint64_t n ) {
    uint64_t r = 0; // result
    uint64_t s = 0; // squared result
    uint64_t ns; // potential new s
    uint64_t p; // bit position
    p = 32;
    while ( (1UL << p) > n ) p--;

    do {
        // (a+b)^2 = a^2 + 2ab + b^2
        ns = s + ( r << ( p + 1 ) ) + ( 1UL << ( p + p ) ); 
        if ( ns <= n ) {
            s = ns;
            r |= 1UL << p;
        }
    } while (p--);

    return r;
}

