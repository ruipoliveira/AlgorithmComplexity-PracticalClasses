CC = gcc
CFLAGS = -ansi -Wall

all: $(SCHRODER)
	$(CC) $(CFLAGS) teste.c schroder.c -o teste


SCHRODER:
	$(CC) $(CFLAGS) -c schroder.c

clean:
	rm -f schroder.o
