#include <stdio.h>
#include "euler.h"
#include "isqrt.h"

int main(int argc, char ** argv) {
	unsigned long n = 600851475143, sn = isqrt(n), i = 2;
	while ( i < sn ) {
		if ( n % i ) {
                    i++;
                } else {
		    n /= i;
		    sn = isqrt( n );
		}
	}
        checkanswer(n,6857,"problem 3");
	return(0);
}
