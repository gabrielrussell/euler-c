#include <stdio.h>
#include <math.h>
#include "euler.h"

int main(int argc, char ** argv) {
	unsigned long n = 600851475143, sn = sqrt(n), i = 2;
	while ( i < sn ) {
		if ( n % i ) {
                    i++;
                } else {
		    n /= i;
		    sn = sqrt( n );
		}
	}
        checkanswer(n,6857);
	return(0);
}
