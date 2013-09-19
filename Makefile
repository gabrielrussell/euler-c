TARGETS = 1 2 3 4 5 ht_test

all: $(TARGETS)

clean:
	rm $(TARGETS)

%: %.c ht.c factor.c
	gcc -Wall -Werror -ggdb -o $@ -lm $^
