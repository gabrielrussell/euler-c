#include "euler.h"
#include <stdio.h>
#include <string.h>

char * ones[] = {"","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
char * tens[] = {"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
char * hundred = "hundred";
char * thousand = "thousand";
char * and = "and";

int main( int argc, char ** argv ) {
    int i;
    int t = 0;
    for (i = 1; i <= 1000; i++) {
        if (i==1000) {
            t+=strlen( ones[1] ) + strlen( thousand );
        } else {
            int h = i / 100;
            int c = i % 100;
            if ( h ) t+=strlen(ones[h])+strlen(hundred);
            if ( h && c ) t+=strlen(and);
            if ( c < 20 ) {
                t+=strlen(ones[c]);
            } else {
                t+=strlen(tens[c/10]);
                if ( c % 10 ) t+=strlen(ones[c%10]);
            }
        }
    }
    checkanswer(t,21124,"problem 17");
    return(0);
}
