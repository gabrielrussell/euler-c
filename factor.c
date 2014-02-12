#include <stdint.h>
#include <assert.h>
#include <stddef.h>
#include "isqrt.h"
#include "ht.h"
#include "dar.h"

/* hmm, maybe just make a ht_merge function that takes a pointer
 * to a value merge function */

void min_factor(ht_t * f, uint64_t n,uint64_t m) {
    uint64_t * existing_count;
    int existing_count_size;
    if (ht_fetch(f,&n,sizeof(n),(void **)&existing_count,&existing_count_size)) {
        assert(existing_count_size == sizeof(m));
        if (m > *existing_count) *existing_count = m;
    } else {
        ht_insert(f,&n,sizeof(n),&m,sizeof(m));
    }
}

void add_factor(ht_t * f, uint64_t n,uint64_t m) {
    uint64_t * existing_count;
    int existing_count_size;
    if (ht_fetch(f,&n,sizeof(n),(void **)&existing_count,&existing_count_size)) {
        assert(existing_count_size == sizeof(m));
        *existing_count += m;
    } else {
        ht_insert(f,&n,sizeof(n),&m,sizeof(m));
    }
}

ht_t * factor(uint64_t n) {
    ht_t * f = ht_new();
    uint64_t i,p,pc;
    uint64_t small_primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    for (p=0;p<10;p++) {
        pc = 0;
        while (n%small_primes[p]==0) {
            n/=small_primes[p];
            pc++;
        }
        if (pc) add_factor(f,small_primes[p],pc);

    }
    uint64_t limit = isqrt(n);
    for ( i=31; i<=limit; i+=2) {
        pc = 0;
        while (n%i==0) {
            n/=i;
            pc++;
        }
        if (pc) add_factor(f,i,pc);
        limit = isqrt(n);
    }
    if (n>1) add_factor(f,n,1);
    return f;
}

void lcm( ht_t * a, ht_t * b ) {
    int i;
    for (i=0;i<b->size;i++) if (b->table[i]) {
        min_factor(a,*(uint64_t *)b->table[i]->key,*(uint64_t *)b->table[i]->value);
    }
}

uint64_t defactor(ht_t * f) {
    uint64_t d=1,i,j,n,m;
    for (i=0;i<f->size;i++) if (f->table[i]) {
        n = *(uint64_t *)f->table[i]->key;
        m = *(uint64_t *)f->table[i]->value;
        for (j=0;j<m;j++) d*=n;
    }
    return(d);    
}

dar_t * divisors( uint64_t n ) { 
    uint64_t sqrt = isqrt( n ) ;
    int64_t i;
    dar_t * r = dar_new(sizeof(uint64_t),8 );
    dar_t * rtop = dar_new(sizeof(uint64_t),8 );
    for ( i = 1; i<=sqrt; i++ ) {
        if ( n % i == 0 ) {
            uint64_t j = n / i;
            dar_push(r,&i);
            if (j!=i) dar_push(rtop,&j);
        }
    }
    uint64_t k;
    while ( dar_pop(rtop,&k) ) dar_push(r, &k );
    dar_destroy(rtop);
    return r;
}

dar_t * proper_divisors( uint64_t n ) {
    dar_t * r = divisors( n );
    (void)dar_pop( r, NULL );
    return r;
}
