a.out: bits.c
	gcc -g -Wall -Wextra -Wwrite-strings bits.c

clean:
	rm -f a.out
	rm -f tests.out
