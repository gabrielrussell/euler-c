include <stdint.h>
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
        // to calculate (a+b)^2 when we have a , a^2 and b, when b=2^n
        // without any multiplies
        // 2^n = 1 << n
        // (a+b)^2 = a^2 +  2ab        + b^2
        //         = a^2 +  2*a*2^n    + 2^2n
        //         = a^2 +  a*2^(n+1)  + 2^2n
        //         = a^2 +  a*1<<(n+1) + 1<<2n
        //         = a^2 +  a<<(n+1)   + 1<<(n+n)
        ns = s + ( r << ( p + 1 ) ) + ( 1UL << ( p + p ) ); 
        if ( ns <= n ) {
            s = ns;
            r |= 1UL << p;
        }
    } while (p--);

    return r;
}

