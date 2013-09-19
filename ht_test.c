#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

#include "ht.h"

int main(int argc, char ** argv) {
    ht_t * ht = ht_new();
    char * value;
    int len;
    ht_insert(ht,"foo",3,"bar",3);
    ht_insert(ht,"bing",3,"bang",3);
    if (ht_fetch(ht,"foo",3,(void **)&value,&len)) {
        if (memcmp(value,"bar",3)) error(1,0,"value of foo doesn't match bar");
    } else {
        error(1,0,"foo not found");
    }

    int i;
    for (i=0;i<1000;i++) {
        ht_insert(ht,&i,sizeof(i),&i,sizeof(i));
    }
    int * j;
    int j_len;
    for (i=0;i<1000;i++) {
        if (ht_fetch(ht,&i,sizeof(i),(void **)&j,&j_len)) {
            if (i != *j) error(1,0,"value of %d doesn't match %d",i,*j);
        } else {
            error(1,0,"%d not found",i);
        }
    }
    ht_destroy(ht);
    return(0);
}
