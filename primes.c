
#include <stdint.h>
#include "dar.h"

void next_prime(uint64_t *n,dar_t *primes) {
    if (*n==0) {
        *n=2;
    } else {
        int is_prime;
        int i , *p;
        do {
            (*n)++;
            is_prime = 1;
            for ( i=0; i<primes->element_count; i++) {
                dar_fetch(primes,i,(void **)&p);
                if ( ( *n % *p ) == 0 ) {
                    is_prime = 0;
                    break;
                }
            }
        } while ( ! is_prime );
    }
    dar_push(primes,n);
}
