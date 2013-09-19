#include <stdio.h>
#include <error.h>
#include "dar.h"

int main(int argc, char ** argv) {
    dar_t * d = dar_new(sizeof(int),10);
    int i = 37;
    int j;
    dar_push(d,&i);
    if (dar_pop(d,&j)) {
        if (j!=i) error(1,0,"popped value not the same as the pushed value");
    }
    if (dar_pop(d,&j)) {
        error(1,0,"extra value popped");
    }
    return(0);
}
