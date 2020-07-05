all: monshell

monshell: monshell.o tools.o
	gcc -o monshell monshell.o tools.o

monshell.o: monshell.c
	gcc -c monshell.c -o monshell.o

tools.o: tools.c
	gcc -c tools.c -o tools.o

clean:
	rm -rf monshell
