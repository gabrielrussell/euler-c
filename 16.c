#include "euler.h"
#include "bn.h"
#include "dar.h"
#include <stdio.h>
#include <unistd.h>

int main( int argc, char ** argv ) {
    bn_t * n;
    dar_t * s;

    /* first verify the base case given in the problem */
    n = bn_new();
    bn_iadd(n,1,15);
    s = bn_format(n);
    dar_t * t = dar_new_from_bytes(1,"32768",5);
    quietly_checkanswer(dar_eq(s,t),1,"32768 eq 1<<15");
    bn_destroy(n);
    dar_destroy(t);
    dar_destroy(s);

    /* then answer the problem */
    n = bn_new();
    bn_iadd(n,1,1000);
    uint64_t sum = bn_sum_digits(n);
    checkanswer(sum,1366,"problem 16");
    return(0);
}
