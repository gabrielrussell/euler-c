#include <stdio.h>

void init_fib_state(int state[2]) ;
int fib (int state[2]) ;

int main(int argc, char ** argv) {
	int fib_state[2];
	int i = 0;
	int sum;

	init_fib_state(fib_state);
	
	while ((i=fib(fib_state))<4000000) {	
		if (i%2 == 0) sum+=i;
	}
	printf("%d\n",sum);
}

int fib (int state[2]) {
	int j = state[0];
	state[0] = state[1];
	state[1] += j;
	return state[0];
}

void init_fib_state(int state[2]) {
	state[0] = state[1] = 1;
}
