#include "euler.h"
#include <stdlib.h>
#include <stdio.h>

uint64_t counts_paths(uint64_t size) {
    uint64_t r;
    uint64_t * counts = calloc(sizeof(uint64_t),(size + 1)*(size +1));
    uint64_t d;
    uint64_t x2,y2;
    uint64_t x,y;
    counts[0] = 1;
    for (d = 1; d<=size*2; d++ ) {
        if ( d < size ) {
            x = 0; y = d;
            x2 = d; y2 = 0;
        } else {
            x = d - size; y = size;
            x2 = size; y2 = d - size;
        }
        while ( y >= y2 && x <= x2 ) {
            counts[ x * (size +1) + y ] = (x?counts[ ( x - 1 ) * (size +1) + y ]:0) + (y?counts[ x * ( size + 1) + ( y - 1 ) ]:0);
            y--; x++;
        }
    }
    r = counts[ ( size + 1 ) * ( size + 1 ) - 1 ];
    free(counts);
    return(r);
}

int main( int argc, char ** argv ) {
    //checkanswer(counts_paths(2),6,"as given in the question, 2x2 grid has 6 routes");
    checkanswer(counts_paths(20),137846528820,"problem 15");
    return(0);
}
