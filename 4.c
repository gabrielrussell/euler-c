#include <stdio.h>
#include <string.h>
#include <error.h>

#include "euler.h"

int is_palindrome(char * s) {
	int l = strlen(s);
	int i;
	for (i = 0;i<l/2;i++) {
		if (s[i] != s[l - 1 - i]) return 0;
	}
	return 1;
}


char * test_is_palindrome(void) {
	if (!is_palindrome("aba")) return "aba is a palindrome";
	if (is_palindrome("abb")) return "abb is not a palindrome";
	if (!is_palindrome("")) return "\"\" is a palindrome";
	if (!is_palindrome("a")) return "a is a palindrome";
	if (is_palindrome("ab")) return "an is not a palindrome";
	if (!is_palindrome("ababa")) return "ababa is a palindrome";
	if (is_palindrome("abaca")) return "abaca is not a palindrome";
	return(NULL);
}

int main (int argc, char ** argv) {
	char * err;
	char buf[255];
	if ((err = test_is_palindrome())) error(1,0,"test failed: %s",err);
	int i,j,n,largest=0;
	for (i=100;i<=999;i++) {
		for (j=100;j<=999;j++) {
			n = i*j;
			sprintf(buf,"%d",n);
			if (is_palindrome(buf)) {
				if (n>largest) largest = n;
			}
		}
	}
	checkanswer(largest,906609);
	return(0);
}
