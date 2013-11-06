#include <stdio.h>
#include <error.h>
#include "dar.h"
#include "euler.h"

int main(int argc, char ** argv) {
    dar_t * d = dar_new(sizeof(int),10);
    int i = 37;
    int j;
    dar_push(d,&i);
    if (dar_pop(d,&j)) {
        checkanswer(j,i);
    }
    if (dar_pop(d,&j)) {
        error(1,0,"extra value popped");
    }
    return(0);
}
