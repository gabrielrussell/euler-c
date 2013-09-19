
typedef struct dar {
	void * data;
	int data_size; //??
	int element_count;
	int element_size;
	int element_space;
} dar_t;

dar_ready(dar_t * a, int more) {
	if (more > a->element_space) {
		a->data = realloc(a->data, ( a->element_space + more ) * element_size ); 
		a->element_space += more;
	}
}

dar_t * a dar_new(int element_size, int initial_size) {
	dar_t * a;
	a = calloc(1,sizeof(*a));
	a->data_size = element_size * initial_size;
	a->element_size = element_size;
	a->element_count = 0;
	dar_ready(a,initial_size);
}

dar_push(dar_t * a, void * e) {
	dar_ready(a,1);
	memcpy(a->data+(element_count * element_size),e);
	element_count++;
	element_space--;
}

dar_pop(dar_t * a,void *e ) {
	memcpy(e,a->data+(element_count * element_size));
	element_count--;
	element_space++;
}

