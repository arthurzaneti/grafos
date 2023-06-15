#ifndef _LISTA_H_
#define _LISTA_H_
#include "aresta.h"

#include <stdbool.h>
typedef struct no no;
typedef struct lista{
    no* primeiro;
    no* ultimo;
    int num_elementos;
    int elemento_de_partida;
}lista;

typedef struct no{
    void* data;
    no* prox;
    no* ant;
}no;

lista* lista_cria();
no* no_cria(void*data);
void lista_insere_inicio_aux(lista* l, no* elem);
void lista_insere_fim_aux(lista*l, no* elem);
void lista_insere_vazia_aux(lista*l, no* elem);
void lista_insere(lista*l, no* elem, int pos);

void* lista_remove_inicio_aux(lista*l);
void* lista_remove_fim_aux(lista*l);
void* lista_remove(lista *l, int pos);
void lista_destroi(lista *l);
bool verifica_remoção_aux(lista*l, int pos);
void lista_testa();

#endif