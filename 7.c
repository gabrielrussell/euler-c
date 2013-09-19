#include <stdio.h>

#include "dar.h"
#include "euler.h"

void next_prime(int *n,dar_t *primes) {
    if (*n==0) {
        *n=2;
    } else {
        int is_prime;
        int i , *p;
        do {
            (*n)++;
            is_prime = 1;
            for (i=0;i<primes->element_count;i++) {
                dar_fetch(primes,i,(void **)&p);
                if (! ( *n % *p) ) {
                    is_prime = 0;
                    break;
                }
            }
        } while (!is_prime);
    }
    dar_push(primes,n);
}

int main (int argc, char ** argv) {
    int i;
    int n = 0;
    dar_t * p = dar_new(sizeof(int),20000);

    for (i = 1; i<=10001; i++) {
        next_prime(&n,p);
    }
    checkanswer(n,104743);
    return(0);
}
