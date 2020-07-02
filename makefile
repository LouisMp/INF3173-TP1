all: monshell

monshell:
	gcc -o monshell monshell.c tools.c

clean:
	rm -rf monshell
