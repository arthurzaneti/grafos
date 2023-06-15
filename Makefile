CC = gcc
CFLAGS = -Wall -Wextra -pedantic

all: programa

programa: lista.o grafo.o aresta.o main.o
	$(CC) $(CFLAGS) -o programa lista.o grafo.o aresta.o main.o

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c

grafo.o: grafo.c grafo.h lista.h
	$(CC) $(CFLAGS) -c grafo.c

aresta.o: aresta.c aresta.h
	$(CC) $(CFLAGS) -c aresta.c

main.o: main.c lista.h grafo.h aresta.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f programa *.o
