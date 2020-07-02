# Compulateur et flags
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99 -lm -O1

# Cible
TARGET = monshell

default: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c tools.c

#phony cible qui ne sont pas des noms de fichier

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f *.o

