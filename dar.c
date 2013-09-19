#include <stdlib.h>
#include <string.h>

#include "dar.h"

void dar_ready(dar_t * a, int more) {
	if (more > a->element_space) {
		a->data = realloc(a->data, ( a->element_space + more ) * a->element_size ); 
		a->element_space += more;
	}
}

dar_t * dar_new(int element_size, int initial_size) {
	dar_t * a;
	a = calloc(1,sizeof(*a));
	a->data_size = element_size * initial_size;
	a->element_size = element_size;
	a->element_count = 0;
	dar_ready(a,initial_size);
        return(a);
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

void dar_fetch(dar_t * a, int i, void ** e) {
    *e = ((char *)a->data) + (i * a->element_size);
}
