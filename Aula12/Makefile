# makefile para a fila com prioridade
CC = gcc
CFLAGS = -ansi -Wall

OBJM = pqueue_dijkstra.o
HEADERS = pqueue_dijkstra.h

OBJECTS = $(OBJM) teste1.o teste2.o
EXES = test1 test2

all:	$(EXES)

test1:	teste1.o $(OBJM)
	$(CC) $(CFLAGS) teste1.o $(OBJM) -o test1

test2:	teste2.o $(OBJM)
	$(CC) $(CFLAGS) teste2.o $(OBJM) -o test2

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
