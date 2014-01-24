#include <stdlib.h>
#include <string.h>

#include "dar.h"

#include <stdio.h>

void dar_readyplus(dar_t * a, int more) {
	if (more > a->element_free) {
                int total = a->element_free + a->element_count;
                if ( more < total / 2 ) more = total / 2;
                more = ( more | 0x00000F ) + 1;
                a->data_size += more * a->element_size ;
		a->data = realloc(a->data, a->data_size ); 
		a->element_free += more;
	}
}

int dar_eq(dar_t * a, dar_t * b) {
    if ( a->element_count != b->element_count ) return 0;
    if ( a->element_size != b->element_size ) return 0;
    return ! memcmp(a->data,b->data,b->element_size * b->element_count);
}

dar_t * dar_new_from_bytes(int element_size, void * b, int len) {
    if ( len % element_size ) return NULL;
    dar_t * r = dar_new(element_size, len / element_size);
    memcpy(r->data,b,len);
    r->element_count += len / element_size;
    r->element_free  -= len / element_size;
    return r;
}

void dar_ready(dar_t * a, int size) {
    if ( size > a->element_free + a->element_count ) dar_readyplus( a, size - ( a->element_free + a->element_count ) ); 
}

dar_t * dar_new(int element_size, int initial_size) {
	dar_t * a;
	a = malloc(sizeof(*a));
        dar_init(a,element_size, initial_size);
        return(a);
}

void dar_destroy( dar_t * a ) {
    free(a->data);
    free(a);
}

void dar_init(dar_t * a, int element_size, int initial_size) {
        initial_size = ( initial_size | 0x00000F ) + 1;
	a->data_size = element_size * initial_size;
	a->element_size = element_size;
        a->element_free = 0;
        a->data = 0;
	a->element_count = 0;
	dar_ready(a,initial_size);
}

void dar_push(dar_t * a, void * e) {
	dar_readyplus(a,1);
	dar_store(a,e,a->element_count);
	a->element_count++;
	a->element_free--;
}

int dar_pop(dar_t * a,void *e ) {
        if ( ! a->element_count ) return(0);
	int r = dar_fetch(a,e,a->element_count - 1 );
        if (!r) return(0);
	a->element_count--;
	a->element_free++;
        return(1);
}

int dar_fetch(dar_t * a, void * e, int i) {
    if ( i > a->element_count - 1 ) return(0);
    if ( i < 0 ) return(0); // error
    if (e) memcpy(e, dar_index( a, i ), a->element_size);
    return(1); // success
}

void dar_store(dar_t * a, void * e, int i) {
    memcpy(a->data + ( i * a->element_size), e, a->element_size);
}

dar_t * dar_copy(dar_t * a) {
    dar_t * b = malloc(sizeof(*b));
    *b = *a;
    b->data = malloc(b->data_size);
    memcpy(b->data,a->data,b->data_size);
    return(b);
}

dar_t * dar_reverse( dar_t * a ) {
    int i;
    dar_t * r = dar_new(a->element_size,a->element_count);
    for ( i=a->element_count-1; i>=0; i-- ) dar_push(r, dar_index( a , i) );
    return r;
}

void * dar_index( dar_t * a, int i ) {
    return a->data + a->element_size * i;
}

void dar_trim( dar_t * a, int i ) {
    int d;
    if ( a->element_count > i ) {
        d = a->element_count - i;
        a->element_count -= d;
        a->element_free += d;
    }
}
