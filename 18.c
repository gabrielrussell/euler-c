#define _GNU_SOURCE
#include "euler.h"
#include "dar.h"
#include "itr.h"
#include "split.h"

char * example[] = {
    "3",
    "7 4",
    "2 4 6",
    "8 5 9 3",
    NULL,
};

int dar_push_atoi ( void * d, char * c, int l ) {
    int i;
    i = atoi(c);
    printf("%d\n",i);
    dar_push((dar_t *)d,&i);
    return 1;
}

void tri_max( itr_t * i ) {
    char * line=NULL;
    size_t line_size=0;
    dar_t * t = dar_new(sizeof(dar_t),8);
    while (i->next(i,&line,&line_size)) {
        dar_t * r = dar_new(4,1);
        dar_push(t,r);
        split(line,line_size,' ',dar_push_atoi,r);
        printf("%s\n",line);
    }
    i->destructor(i);
}

int main (int argc, char ** argv) {
    tri_max(string_array_itr_new( example ));
    tri_max(file_itr_new(fopen("18.txt","r")));
    return 0;
}

