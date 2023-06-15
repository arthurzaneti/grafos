# include "aresta.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>


aresta *aresta_cria(int inicio, int fim, float peso){
    if (inicio <0|| fim <0){
        printf("Erro na criação da aresta: inicio ou fim menores que 0");
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
