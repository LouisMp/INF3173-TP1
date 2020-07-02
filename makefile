all: monshell

monshell: monshell.o 
	gcc -o monshell monshell.o

monshell.o: monshell.c
	gcc -o monshell.o -c monshell.c tools.c
