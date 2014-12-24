all: test demo

test: test.o processing.o libgmini.o alphabet.o
	gcc -Wall -O3 test.o processing.o libgmini.o alphabet.o -o tdemo -lXext -lX11 -lm

demo: main.o processing.o libgmini.o
	gcc -Wall -O3 main.o processing.o libgmini.o -o demo -lXext -lX11 -lm

test.o: test.c
	gcc -Wall test.c -c -lXext

main.o: main.c
	gcc -Wall main.c -c -lXext

processing.o: processing.c
	gcc -Wall processing.c -c -lm

alphabet.o: alphabet.c
	gcc -Wall alphabet.c -c

libgmini.o: libgmini.c
	gcc -Wall libgmini.c -c -lXext

.PHONY: clean

clean:
	rm -f *.o demo tdemo
