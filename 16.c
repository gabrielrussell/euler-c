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
    s = bn_format(n);
    int i; char j;
    int sum = 0;
    for ( i = 0; i < s->element_count; i++ ) {
        dar_fetch(s,&j,i);
        sum += ( j - '0' );
    }
    checkanswer(sum,1366,"problem 16");

    
    
    return(0);
}
