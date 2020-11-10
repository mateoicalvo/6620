CFLAGS=-Wall -g

CFLAGS_NO_DEBUG=-Wall -Werror -pedantic

all: regressions
	:

regressions: regressions.c hash.c hash.S
	$(CC) $(CFLAGS) -o regressions regressions.c hash.c hash.S

tp1: main.c hash.c hash.S hasheador.c
	$(CC) $(CFLAGS_NO_DEBUG) -o tp1 main.c hash.c hash.S hasheador.c

tp1_debug: main.c hash.c hash.S hasheador.c
	$(CC) $(CFLAGS) -o tp1 main.c hash.c hash.S hasheador.c

test: regressions
	./regressions

clean:
	rm -f regressions
