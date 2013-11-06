#ifndef DAR_H
#define DAR_H
typedef struct dar {
	void * data;
	int data_size; //??
	int element_count;
	int element_size;
	int element_space;
} dar_t ;

void dar_push(dar_t * a, void * e) ;
int dar_pop(dar_t * a,void *e ) ;
void dar_fetch(dar_t * a, int i, void ** e) ;
dar_t * dar_new(int element_size, int initial_size) ;
void dar_init(dar_t *, int element_size, int initial_size) ;
dar_t * dar_copy(dar_t * a) ;
#endif
