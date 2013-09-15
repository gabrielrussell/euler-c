all: 1 2 3 4

%: %.c
	gcc -Wall -Werror -o $@ -lm $<
