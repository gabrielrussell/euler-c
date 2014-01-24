#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "factor.h"
#include "ht.h"
#include "euler.h"

int main (int argc, char ** argv) {
    ht_t * f, * r;
    r = ht_new();
    int i;
    for ( i=2; i<=20; i++ ) {
        f = factor(i);
        lcm(r,f);
        ht_destroy(f);
    }
    uint64_t n = defactor(r);
    checkanswer(n,232792560,"problem 5");
    return(0);
}

