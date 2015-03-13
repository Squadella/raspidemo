all: demo

demo: main.o processing.o
	gcc -Wall -O3 main.o processing.o -o demo -lm

main.o: main.c
	gcc -Wall main.c -c -lXext

#alphabet.o: alphabet.c
#	gcc -Wall alphabet.c -c

.PHONY: clean

clean:
	rm -f *.o demo tdemo
