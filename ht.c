#include <stdint.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ht.h"

void ht_insert_entry( ht_t * ht, ht_entry_t * e ) ;
void ht_grow(ht_t * ht) ;

uint32_t mdjb_hash ( uint8_t * key, int l ) {
    uint32_t h = 0;
    /* modified Bernstein hash */
    while ( --l >= 0 ) h = 33 * h ^ key[l];
    return h;
}

ht_entry_t * ht_make_entry( uint8_t * key, int key_length, uint8_t * value, int value_length ) {

    ht_entry_t * e = malloc( sizeof(ht_entry_t) + key_length + 1 + value_length + 1 );
    if ( e == NULL ) error(1,errno,"failure to malloc ht_entry_t");

    e->hash = mdjb_hash( key, key_length );

    e->key = (uint8_t *) e + sizeof(ht_entry_t);
    e->key_length = key_length;
    memcpy(e->key, key, key_length);
    e->value = (uint8_t *) e + sizeof(ht_entry_t) + key_length + 1;
    e->value_length = value_length;
    memcpy(e->value, value, value_length);

    return e;
}

void ht_grow(ht_t * ht) {
    ht_t ht_orig = *ht;
    ht->size = ht->size ? ht->size * 2 : 32;
    ht->table = malloc( sizeof(ht_entry_t *) * ht->size );
    ht->num = 0;
    ht->free = ht->size / 2;

    int i;
    for ( i=0; i < ht_orig.size; i++ ) {
        if ( ht_orig.table[i] ) {
            ht_insert_entry(ht,ht_orig.table[i]);
        }
    }
    free(ht_orig.table);
}

void ht_insert_entry( ht_t * ht, ht_entry_t * e ) {
    if (ht->free == 0) ht_grow(ht);
    int hunt =  e->hash % ht->size ;
    while ( ht->table[hunt] != NULL ) hunt = ( hunt + 1 ) % ht->size;
    ht->table[hunt] = e;
    ht->free --;
    ht->num ++;
}

void ht_insert( ht_t * ht, uint8_t * key, int key_length, uint8_t * value, int value_length ) {
    ht_entry_t * e = ht_make_entry( key, key_length, value, value_length ) ;
    ht_insert_entry( ht, e );
}
