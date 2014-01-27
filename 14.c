#include "euler.h"
#include <inttypes.h>

uint64_t collatz_length(uint64_t n) {
    uint64_t r = 1;
    while (n > 1) {
        if (n%2) { // odd
            n = 3*n + 1; 
        } else { // even
            n = n / 2;
        }
        r++;
    }
    return r;
}

int main (int argc, char ** argv) {
    //checkanswer(collatz_length(13),10,"as per question, the collatz sequence length of 13 is 10");
    uint64_t max_length = 0;
    uint64_t max_number = 0;
    uint64_t l;
    uint64_t i;
    for ( i = 1; i < 1000000; i++ ) {
        if ( ( l = collatz_length(i) ) > max_length ) {
            max_length = l;
            max_number = i;
        }
    }
    checkanswer(max_number,837799,"problem 14");
    return 0;
}
