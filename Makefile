TARGETS = 1 2 3 4

all: $(TARGETS)

clean:
	rm $(TARGETS)

%: %.c ht.c
	gcc -Wall -Werror -o $@ -lm $^
