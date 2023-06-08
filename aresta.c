# include "aresta.h"
# include <stdio.h>
# include <stdlib.h>

aresta *aresta_cria(tipo_no inicio, tipo_no fim){
    if (inicio == NULL || fim ==NULL){
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
