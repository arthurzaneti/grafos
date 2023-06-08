#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct lista{
    no* primeiro;
    no* ultimo;
    int num_elementos;
    int tamanho_lista;
}lista;

typedef struct no{
    void* data;
    no* prox;
    no* ant;
}no;

#endif