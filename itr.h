#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct itr {
    void * context;
    void (* destructor)(struct itr*);
    int  (*next)(struct itr*,char **,size_t *);
} itr_t;

itr_t * string_array_itr_new( char ** array ) ;
itr_t * file_itr_new( FILE * f ) ;
