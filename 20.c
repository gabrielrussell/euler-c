#include "euler.h"
#include "bn.h"

int main( int argc, char ** argv ) {
    bn_t * fe = bn_factorial(10);
    quietly_checkanswer(bn_sum_digits(fe),27,"example for problem 20");
    bn_destroy(fe);

    bn_t * f = bn_factorial(100);
    checkanswer(bn_sum_digits(f),648,"problem 20");
    bn_destroy(f);
    return 0;
}
