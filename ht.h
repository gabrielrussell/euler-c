#include <stdint.h>

#ifndef HT_H
#define HT_H

typedef struct ht_entry {
    uint32_t hash;
    char * key;
    int key_length;
    char * value;
    int value_length;
} ht_entry_t;

typedef struct ht {
    ht_entry_t ** table;
    int size;
    int num;
    int free;
} ht_t;

void ht_insert( ht_t * ht, void * key, int key_length, void * value, int value_length ) ;
int ht_fetch( ht_t * ht, void * key, int key_length, void ** value, int * value_length ) ;
void ht_destroy(ht_t * ht) ;
ht_t * ht_new(void);

#endif
