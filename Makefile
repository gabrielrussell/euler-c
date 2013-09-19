TARGETS = 1 2 3 4 ht_test

all: $(TARGETS)

clean:
	rm $(TARGETS)

%: %.c ht.c
	gcc -Wall -Werror -ggdb -o $@ -lm $^
