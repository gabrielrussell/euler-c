
#include <stdint.h>
#include "dar.h"
#include <math.h>

void next_prime(uint64_t *n,dar_t *primes) {
    if (*n==0) {
        *n=2;
    } else {
        int is_prime;
        uint64_t i , *p;
        do {
            (*n)++;
            is_prime = 1;
            uint64_t nsqr = sqrt(*n);
            for ( i=0; i < primes->element_count; i++) {
                p = dar_fetch(primes,i);
                if ( *p > nsqr ) break;
                if ( ( *n % *p ) == 0 ) {
                    is_prime = 0;
                    break;
                }
            }
        } while ( ! is_prime );
    }
    dar_push(primes,n);
}
