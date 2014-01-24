#include <stdio.h>
#include <error.h>
#include "dar.h"
#include "euler.h"

int main(int argc, char ** argv) {
    dar_t * d = dar_new(sizeof(int),10);
    int i = 37;
    int j;
    dar_push(d,&i);
    int r = dar_pop(d,&j);
    checkanswer(r,1,"dar pop succeeds");
    checkanswer(j,i,"dar pop correct value");
    r = dar_pop(d,&j);
    checkanswer(r,0,"dar pop correctly fails");
    dar_destroy(d);

    dar_t * a = dar_new_from_bytes(1,"hello",5);
    dar_t * b = dar_new_from_bytes(1,"hello",5);
    dar_t * c = dar_new_from_bytes(1,"hell",5);
    checkanswer(dar_eq(a,b),1,"dar_eq hello eq hello");
    checkanswer(dar_eq(a,c),0,"dar_eq hell ne hello");
    checkanswer(dar_eq(c,a),0,"dar_eq hello ne hell");
    dar_destroy(a);
    dar_destroy(b);


    a = dar_new_from_bytes(1,"hello",5);
    b = dar_reverse(a);
    c = dar_new_from_bytes(1,"olleh",5);
    checkanswer(dar_eq(b,c),1,"dar_reverse(hello) == olleh");
    return(0);
}
