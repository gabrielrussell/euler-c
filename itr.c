#include "itr.h"

int string_array_itr_next ( itr_t * i, char **lineptr, size_t *n ) {
    string_array_itr_t *sai = i->context;
    if (!sai->array[sai->position]) return 0;
    *lineptr = sai->array[sai->position++];
    *n = strlen( *lineptr );
    return 1;
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
    return i;
}

int file_itr_next(itr_t * i, char ** lineptr, size_t *n) {
    file_itr_t *f = i->context;
    if (feof(f->file)) return 0;
    *n = getline(&(f->line),n,f->file);
    *lineptr = f->line;
    return ( *n > 1 ? 1 : 0 );
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

