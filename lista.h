#ifndef _LISTA_H_
#define _LISTA_H_
#include <stdbool.h>
typedef struct lista{
    no* primeiro;
    no* ultimo;
    int num_elementos;
}lista;

typedef struct no{
    void* data;
    no* prox;
    no* ant;
}no;

lista* lista_cria();
void insere_inicio(lista* l, no* elem);
void insere_fim(lista*l, no* elem);
void insere_lista_vazia(lista*l, no* elem);
void insere(lista*l, no* elem, int pos);

void* lista_remove_inicio(lista*l);
void* lista_remove_fim(lista*l);
void* lista_remove(lista *l, int pos);
bool verifica_remoção(lista*l, int pos);

#endif