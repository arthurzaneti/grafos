CC = gcc
CFLAGS = -Wall -Wextra -pedantic
BIN_DIR = bin

all: $(BIN_DIR)/programa

$(BIN_DIR)/programa: $(BIN_DIR)/lista.o $(BIN_DIR)/grafo.o $(BIN_DIR)/aresta.o $(BIN_DIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/grafo.o: grafo.c grafo.h lista.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/aresta.o: aresta.c aresta.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/main.o: main.c lista.h grafo.h aresta.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/programa
