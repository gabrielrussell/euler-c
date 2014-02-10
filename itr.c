#include "itr.h"

typedef struct string_array_itr {
    char ** array;
    int position;
} string_array_itr_t;

typedef struct file_itr {
    FILE * file;
    int eof;
    char * line;
} file_itr_t;

int string_array_itr_next ( itr_t * i, char **lineptr, size_t *n ) ;
void string_array_itr_destroy( itr_t * i ) ;
int file_itr_next(itr_t * i, char ** lineptr, size_t *n) ;
void file_itr_destroy(itr_t * i) ;

int string_array_itr_next ( itr_t * i, char **lineptr, size_t *n ) {
    string_array_itr_t *sai = i->context;
    if (!sai->array[sai->position]) return 0;
    *lineptr = sai->array[sai->position++];
    *n = strlen( *lineptr );
    return(1);
}

void string_array_itr_destroy( itr_t * i ) {
    free(i->context);
    free(i);
}

itr_t * string_array_itr_new( char ** array ) {
    itr_t * i = calloc(sizeof(itr_t),1);
    i->destructor = string_array_itr_destroy;
    i->next = string_array_itr_next;
    string_array_itr_t * sai = calloc(sizeof(string_array_itr_t),1);
    i->context = sai;
    sai->array = array;
    return(i);
}

int file_itr_next(itr_t * i, char ** lineptr, size_t *n) {
    file_itr_t *f = i->context;
    if (f->eof) return 0;
    if (-1 == (*n = getline(&(f->line),n,f->file))) {
        f->eof = 1;
        return 0;
    }
    if (f->line[*n-1] == '\n')
        f->line[--*n]=0;
    *lineptr = f->line;
    return(1);
}

void file_itr_destroy(itr_t * i) {
    file_itr_t *f = i->context;
    if (f->line) free(f->line);
    free(f);
    free(i);
}

itr_t * file_itr_new( FILE * f ) {
    itr_t * i = calloc(sizeof(itr_t),1);
    i->destructor = file_itr_destroy;
    i->next = file_itr_next;
    file_itr_t * fi = calloc(sizeof(file_itr_t),1);
    i->context = fi;
    fi->file = f;
    fi->line = NULL;
    return i;
}

