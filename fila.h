#ifndef _FILA_H_
#define _FILA_H_
#include <stdbool.h>
#include "aresta.h"

typedef union{
    aresta aresta;
    tipo_no no;
}dado_t;

struct _fila{
    int cap;
    int num;
    dado_t *vet;
};
typedef struct _fila* fila;

fila fila_cria(int cap);
void fila_destroi(fila f);

dado_t fila_remove(fila f);
void fila_insere(fila f, dado_t d);

dado_t fila_mostra_inicio(fila f);
dado_t fila_mostra_fim(fila f);

bool fila_cheia(fila f);
bool fila_vazia(fila f);



#endif