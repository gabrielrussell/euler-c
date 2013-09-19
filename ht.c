#include <stdint.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ht.h"

void ht_insert_entry( ht_t * ht, ht_entry_t * e ) ;
void ht_grow(ht_t * ht) ;

uint32_t mdjb_hash ( char * key, int l ) {
    uint32_t h = 0;
    /* modified Bernstein hash */
    while ( --l >= 0 ) h = 33 * h ^ key[l];
    return h;
}

ht_entry_t * ht_make_entry( char * key, int key_length, char * value, int value_length ) {

    ht_entry_t * e = calloc( 1, sizeof(ht_entry_t) + key_length + 1 + value_length + 1 );
    if ( e == NULL ) error(1,errno,"failure to calloc  ht_entry_t");

    e->hash = mdjb_hash( key, key_length );

    e->key = (char *) e + sizeof(ht_entry_t);
    e->key_length = key_length;
    memcpy(e->key, key, key_length);
    e->key[key_length] = 0;
    e->value = (char *) e + sizeof(ht_entry_t) + key_length + 1;
    e->value_length = value_length;
    memcpy(e->value, value, value_length);
    e->value[value_length] = 0;

    return e;
}

void ht_grow(ht_t * ht) {
    ht_t ht_orig = *ht;
    ht->size = ht->size ? ht->size * 2 : 32;
    ht->table = calloc( 1, sizeof(ht_entry_t *) * ht->size );
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

void ht_insert( ht_t * ht, void * key, int key_length, void * value, int value_length ) {
    ht_entry_t * e = ht_make_entry( key, key_length, value, value_length ) ;
    ht_insert_entry( ht, e );
}

int ht_fetch( ht_t * ht, void * key, int key_length, void ** value, int * value_length ) {
    uint32_t hash = mdjb_hash( key, key_length );
    if (!ht->size) return(0);
    int hunt =  hash % ht->size ;
    while ( ht->table[hunt] != NULL ) {
        if (ht->table[hunt]->hash == hash && ht->table[hunt]->key_length == key_length && memcmp(ht->table[hunt]->key,key,key_length) == 0 ) {
            *value = ht->table[hunt]->value;
            *value_length = ht->table[hunt]->value_length;
            return(1);
        }
        hunt = ( hunt + 1 ) % ht->size;
    }
    return(0);
}

void ht_destroy(ht_t * ht) {
    int i;
    for ( i = 0; i < ht->size ; i++ ) {
        if (ht->table[i]) {
            free(ht->table[i]);
            ht->table[i]=0;
        }
    }
    free(ht->table);
    free(ht);
}

ht_t * ht_new(void) {
    return(calloc(1,sizeof(ht_t)));
}
