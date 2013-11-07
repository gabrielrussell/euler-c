#include <stdio.h>
#include <inttypes.h>
#include "isqrt.h"
#include "dar.h"

void next_prime(uint64_t *n,dar_t *primes) {
    if (*n==0) {
        *n=2;
    } else {
        int is_prime;
        uint64_t i , p;
        do {
            (*n)++;
            is_prime = 1;
            uint64_t nsqr = isqrt(*n);
            for ( i=0; i < primes->element_count; i++) {
                (void)dar_fetch(primes,&p,i);
                if ( p > nsqr ) break;
                if ( ( *n % p ) == 0 ) {
                    is_prime = 0;
                    break;
                }
            }
        } while ( ! is_prime );
    }
    dar_push(primes,n);
}

