TARGETS = 1 2 3 4 5 6 7 8 9 10 11 12
EXTRA_TARGETS = ht_test dar_test bn_test
DEPENCENCIES = euler.h

OBJECTS = ht.o factor.o dar.o primes.o bn.o

all: $(TARGETS) $(EXTRA_TARGETS)

$(OBJECTS): %.o: %.c $(DEPENCENCIES)
	gcc -Wall -Werror -ggdb -O0 -c -o $@ -lm $<

%: %.c $(OBJECTS)
	gcc -Wall -Werror -ggdb -O0 -o $@ -lm -lprofiler $^

test: $(TARGETS)
	for i in $(TARGETS); do ./$$i ; done

clean:
	rm -f $(TARGETS) $(EXTRA_TARGETS) $(OBJECTS)
