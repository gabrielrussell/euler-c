TARGETS = 1 2 3 4 5 6 7
EXTRA_TARGETS = ht_test dar_test

OBJECTS = ht.o factor.o dar.o

all: $(TARGETS) $(EXTRA_TARGETS)

$(OBJECTS): %.o: %.c
	gcc -Wall -Werror -ggdb -c -o $@ -lm $^

%: %.c $(OBJECTS)
	gcc -Wall -Werror -ggdb -o $@ -lm $^ 

test: $(TARGETS)
	for i in $(TARGETS); do ./$$i ; done

clean:
	rm $(TARGETS) $(EXTRA_TARGETS) $(OBJECTS)
