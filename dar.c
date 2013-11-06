#include <stdlib.h>
#include <string.h>

#include "dar.h"

#include <stdio.h>

void dar_ready(dar_t * a, int more) {
	if (more > a->element_space) {
                int total = a->element_space + a->element_count;
                if ( more < total / 2 ) more = total / 2;
                more = ( more | 0x00000F ) + 1;
                a->data_size += more * a->element_size ;
		a->data = realloc(a->data, a->data_size ); 
		a->element_space += more;
	}
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
        a->element_space = 0;
        a->data = 0;
	a->element_count = 0;
	dar_ready(a,initial_size);
}

void dar_push(dar_t * a, void * e) {
	dar_ready(a,1);
	memcpy(a->data+(a->element_count * a->element_size),e,a->element_size);
	a->element_count++;
	a->element_space--;
}

int dar_pop(dar_t * a,void *e ) {
        if (!a->element_count) return(0);
	memcpy(e, a->data + ( ( a->element_count - 1 ) * a->element_size), a->element_size);
	a->element_count--;
	a->element_space++;
        return(1);
}

void * dar_fetch(dar_t * a, int i) {
    // XXX bounds check
    return ((char *)a->data) + (i * a->element_size);
}

dar_t * dar_copy(dar_t * a) {
    dar_t * b = malloc(sizeof(*b));
    *b = *a;
    b->data = malloc(b->data_size);
    memcpy(b->data,a->data,b->data_size);
    return(b);
}
