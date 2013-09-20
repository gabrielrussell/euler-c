#include <stdio.h>

#include "dar.h"
#include "euler.h"
#include "primes.h"

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
