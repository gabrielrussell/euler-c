#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct itr {
    void * context;
    void (* destructor)(struct itr*);
    int  (*next)(struct itr*,char **,size_t *);
} itr_t;

typedef struct string_array_itr {
    char ** array;
    int position;
} string_array_itr_t;

typedef struct file_itr {
    FILE * file;
    char * line;
} file_itr_t;

int string_array_itr_next ( itr_t * i, char **lineptr, size_t *n ) ;
void string_array_itr_destroy( itr_t * i ) ;
itr_t * string_array_itr_new( char ** array ) ;
int file_itr_next(itr_t * i, char ** lineptr, size_t *n) ;
void file_itr_destroy(itr_t * i) ;
itr_t * file_itr_new( FILE * f ) ;
