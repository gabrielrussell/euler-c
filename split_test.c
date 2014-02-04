#include "euler.h"
#include "split.h"
#include <string.h>

char * test_string = "foo bar bat";
char * test_values[] = { "foo", "bar", "bat" };

int check_value ( void * context, char * value, int len ) {
    int * counter = context;
    checkanswer(memcmp(value,test_values[*counter],len),0,"split values equal array values");
    (*counter)++;
    return 0;
}

int main ( int argc, char ** argv ) {
    int counter = 0;
    split(test_string,strlen(test_string),' ',check_value,(void *)&counter);
    return 0;
}
