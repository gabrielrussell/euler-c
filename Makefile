TARGETS = 1 2 3 4 5 6
EXTRA_TARGETS = ht_test

all: $(TARGETS) $(EXTRA_TARGETS)

clean:
	rm $(TARGETS) $(EXTRA_TARGETS)

%: %.c ht.c factor.c euler.h
	gcc -Wall -Werror -ggdb -o $@ -lm $^

test: $(TARGETS)
	for i in $(TARGETS); do ./$$i ; done
