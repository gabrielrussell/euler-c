#include <stdio.h>
#include "euler.h"
#include "isqrt.h"

uint64_t count_divisors(uint64_t n) {
    uint64_t s = isqrt(n), i, d=0;
    for (i=1;i<s;i++) if (n%i==0) d+=2;
    if (n%s==0) d++;
    return(d);
}


int main(int argc, char** argv) {
    uint64_t n=0, t=0, d=0;
    while (d<500) d = count_divisors( (t += ++n) );
    checkanswer(t,76576500,"problem 12");
    return(0);
}
