#include <stdio.h>
#include <math.h>

int main(int argc, char ** argv) {
	unsigned long n = 600851475143;
	long sn = sqrt(n);
	long i;
	for (i = 2; i<sn; i++) {
		while (n%i==0) {
			n/=i;
			sn = sqrt(n);
		}
	}
	printf("%d\n",n);
	return(0);
}
