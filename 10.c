#include <stdio.h>

#include "dar.h"
#include "euler.h"
#include "primes.h"

int main (int argc, char ** argv) {
    uint64_t i = 0;
    uint64_t n = 0;
    dar_t * p = dar_new(sizeof(uint64_t),20000);
    do {
        i += n;
        next_prime(&n,p);
    } while ( n < 2000000 );
    checkanswer(i,142913828922,"problem 10");
    return(0);
}
