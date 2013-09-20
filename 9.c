#include <stdio.h>
#include "euler.h"

int main(int argc, char ** argv) {
    int a,b,c;
    for ( a = 3; a <= 1000; a++ ) {
        for ( b = 2; b < a; b++ ) {
            c = 1000 - a - b;
            if ( a * a + b * b == c * c ) {
                checkanswer( a * b * c, 31875000 );
                return(0);
            }
        }
    }
    checkanswer( a * b * c, 31875000 );
    return(1);
}
