# include "aresta.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

#define NULL_CHAR '\0'
// se tipo_no mudar talvez precise definir outro valor para comparar com NULL

aresta *aresta_cria(tipo_no inicio, tipo_no fim, float peso){
    if (inicio == NULL_CHAR || fim ==NULL_CHAR){
        printf("Erro na criação da aresta: inicio ou fim nulos");
        return NULL;
    }
    aresta* a = malloc(sizeof(aresta));
    if (a==NULL){
        printf("Erro de alocação da aresta: falha no maloc");
        return NULL;
    }
    a->inicio = inicio;
    a->fim = fim;
    a->peso = peso;
    return a;
}
void aresta_destroi(aresta* a){
    if (a==NULL){
        printf("Erro na destruição da aresta: aresta nula");
        return;
    }
    free(a);
    return;
}
void aresta_testa(){
    int c = 1;
    int  a = 1;
    float peso = 10;
    aresta* aresta_teste = aresta_cria(c, a, peso);
    assert(aresta_teste->inicio ==1);
    assert(aresta_teste->fim ==1);
    aresta_destroi(aresta_teste);
}
