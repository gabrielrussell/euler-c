#ifndef DAR_H
#define DAR_H
typedef struct dar {
	void * data;
	int data_size; //??
	int element_count;
	int element_size;
	int element_free;
} dar_t ;

void dar_push(dar_t * a, void * e) ;
int dar_pop(dar_t * a,void *e ) ;
int dar_fetch(dar_t * a, void * e, int i) ;
dar_t * dar_new(int element_size, int initial_size) ;
void dar_init(dar_t *, int element_size, int initial_size) ;
dar_t * dar_copy(dar_t * a) ;
void dar_destroy( dar_t * a ) ;
void dar_store(dar_t * a, void * e, int i) ;
void * dar_index( dar_t * a, int i ) ;
dar_t * dar_reverse( dar_t * a ) ;
void dar_readyplus(dar_t * a, int more) ;
int dar_eq(dar_t * a, dar_t * b) ;
dar_t * dar_new_from_bytes(int element_size, void * b, int len) ;
int dar_eq(dar_t * a, dar_t * b) ;
dar_t * dar_reverse( dar_t * a ) ;
void dar_trim( dar_t * a, int i ) ;
#endif
