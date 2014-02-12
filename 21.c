#include "euler.h"
#include "factor.h"
#include <assert.h>
#include <stdio.h>

uint64_t dar_uint64_sum( dar_t * d ) {
    assert(d->element_size == sizeof(uint64_t));
    uint64_t i, r = 0, v;
    for ( i = 0; i < d->element_count; i++ ) {
        dar_fetch(d,&v,i);
        r += v;
    }
    dar_destroy(d);
    return r;
}

int is_amicable( int i ) {
    int j = dar_uint64_sum(proper_divisors(i));
    int k = dar_uint64_sum(proper_divisors(j));
    return (i==k && i!=j) ;
}

int main ( int argc, char ** argv ) {
    quietly_checkanswer(dar_uint64_sum(proper_divisors(220)),284,"d(220) = 284");
    quietly_checkanswer(dar_uint64_sum(proper_divisors(284)),220,"d(284) = 220");
    quietly_checkanswer(dar_uint64_sum(proper_divisors(dar_uint64_sum(proper_divisors(220)))),220,"d(d(220)) = 220");
    quietly_checkanswer(is_amicable(220),1,"is_amicable(220)");
    int i;
    int sum = 0;
    for (i=2;i<10000;i++) {
        if (is_amicable(i)) sum += i;
    }
    checkanswer(sum,31626,"problem 21");
    return(0);
}
