# include "aresta.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

#define NULL_CHAR '\0'
// se tipo_no mudar talvez precise definir outro valor para comparar com NULL

aresta *aresta_cria(tipo_no inicio, tipo_no fim){
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
    tipo_no c = 'c';
    tipo_no a = 'a';
    aresta* aresta_teste = aresta_cria(c,a);
    assert(aresta_teste->inicio =='c');
    assert(aresta_teste->fim =='a');
    aresta_destroi(aresta_teste);
}
