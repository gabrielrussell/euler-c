#include <stdint.h>

typedef struct ht_entry {
    uint32_t hash;
    uint8_t * key;
    int key_length;
    uint8_t * value;
    int value_length;
} ht_entry_t;

typedef struct ht {
    ht_entry_t ** table;
    int size;
    int num;
    int free;
} ht_t;

void ht_insert( ht_t * ht, uint8_t * key, int key_length, uint8_t * value, int value_length ) ;
