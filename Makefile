TARGETS = 1 2 3 4 5 6 7 8 9
EXTRA_TARGETS = ht_test dar_test

OBJECTS = ht.o factor.o dar.o primes.o

all: $(TARGETS) $(EXTRA_TARGETS) test

$(OBJECTS): %.o: %.c
	gcc -Wall -Werror -ggdb -c -o $@ -lm $^

%: %.c $(OBJECTS)
	gcc -Wall -Werror -ggdb -o $@ -lm $^ 

test: $(TARGETS)
	for i in $(TARGETS); do ./$$i ; done

clean:
	rm -f $(TARGETS) $(EXTRA_TARGETS) $(OBJECTS)
