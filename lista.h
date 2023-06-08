#ifndef _LISTA_H_
#define _LISTA_H_
#include aresta.h

#include <stdbool.h>
typedef struct no no;
typedef struct lista{
    no* primeiro;
    no* ultimo;
    int num_elementos;
    tipo_no elemento_de_partida;
}lista;

typedef struct no{
    void* data;
    no* prox;
    no* ant;
}no;

lista* lista_cria();
void lista_insere_inicio(lista* l, no* elem);
void lista_insere_fim(lista*l, no* elem);
void lista_insere_vazia(lista*l, no* elem);
void lista_insere(lista*l, no* elem, int pos);

void* lista_remove_inicio(lista*l);
void* lista_remove_fim(lista*l);
void* lista_remove(lista *l, int pos);
bool verifica_remoção(lista*l, int pos);
void lista_testa();

#endif