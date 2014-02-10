#define _GNU_SOURCE
#include "dar.h"
#include "itr.h"
#include "split.h"

int dar_push_atoi ( void * d, char * c, int l ) {
    int i;
    i = atoi(c);
    dar_push((dar_t *)d,&i);
    return 0;
}


int tri_max( itr_t * itr ) {
    char * line=NULL;
    size_t line_size=0;
    dar_t * values = dar_new(sizeof(dar_t*),8);
    while (itr->next(itr,&line,&line_size)) {
        dar_t * vr = dar_new(sizeof(int),1);
        split(line,line_size,' ',dar_push_atoi,vr);
        dar_push(values,&vr);
    }
    int i,j;
    for ( i = values->element_count - 2; i>=0; i-- ) {
        dar_t * thisrow;
        dar_t * lowerrow;
        dar_fetch(values,&thisrow,i); 
        dar_fetch(values,&lowerrow,i+1); 
        for ( j = 0; j < thisrow->element_count; j++ ) {
            int this, left, right;
            dar_fetch(thisrow,&this,j); 
            dar_fetch(lowerrow,&left,j); 
            dar_fetch(lowerrow,&right,j+1); 
            if ( left > right ) {
                this += left;
            } else {
                this += right;
            }
            dar_store(thisrow,&this,j);
        }
    }
    dar_t * toprow;
    int r;
    dar_fetch(values,&toprow,0);
    dar_fetch(toprow,&r,0);
    itr->destructor(itr);
    return r;
}
