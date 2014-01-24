TARGETS = 1 2 3 4 5 6 7 8 9 10 11 12 13
EXTRA_TARGETS = ht_test dar_test bn_test
DEPENCENCIES = euler.h

OBJECTS = ht.o factor.o dar.o primes.o bn.o isqrt.o

all: $(TARGETS) $(EXTRA_TARGETS)

$(OBJECTS): %.o: %.c $(DEPENCENCIES)
	gcc -Wall -Werror -ggdb -O0 -c -o $@ $<

%: %.c $(OBJECTS)
	gcc -Wall -Werror -ggdb -O0 -o $@ $^

test: $(TARGETS) $(EXTRA_TARGETS)
	for i in $(TARGETS) $(EXTRA_TARGETS); do ./$$i ; done

clean:
	rm -f $(TARGETS) $(EXTRA_TARGETS) $(OBJECTS)
