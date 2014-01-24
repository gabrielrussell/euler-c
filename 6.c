#include <stdio.h>
#include <stdint.h>
#include "euler.h"

int main(int argc, char ** argv) {
    uint64_t a=0, b=0;
    int i;
    for (i=1;i<=100;i++) {
        a += i*i;
        b += i;
    }
    b = b*b;
    checkanswer(b-a,25164150,"problem 6");
    return(0);
}
