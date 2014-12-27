demo: main.o processing.o libgmini.o
	gcc -Wall -O3 main.o processing.o libgmini.o -o demo -lXext -lX11 -lm

main.o: main.c
	gcc -Wall main.c -c -lXext

processing.o: processing.c
	gcc -Wall processing.c -c

libgmini.o: libgmini.c
	gcc -Wall libgmini.c -c -lXext

.PHONY: clean

clean:
	rm -f *.o demo
