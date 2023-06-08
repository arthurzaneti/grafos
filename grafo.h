#ifndef _GRAFO_H_
#define _GRAFO_H_
#include "lista.h"

typedef struct grafo{
    lista* lista_de_adjacencias;
}grafo;

grafo* grafo_cria(lista* nos, lista* arestas);
lista* grafo_itera_arestas_aux(no* no_atual, lista* arestas);
void grafo_printa(grafo* g);

void grafo_testa();

#endif