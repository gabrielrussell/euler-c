#include "dar.h"
#include "ht.h"

ht_t * factor(uint64_t n) ;
void add_factor(ht_t * f, uint64_t n,uint64_t m) ;
uint64_t defactor(ht_t * f) ;
void lcm( ht_t * a, ht_t * b ) ;
dar_t * divisors( uint64_t n ) ;
dar_t * proper_divisors( uint64_t n ) ;
