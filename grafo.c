#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

grafo* grafo_cria(lista* nos, lista* arestas){
    lista* lista_de_adjacencias = lista_cria();
    if (lista_de_adjacencias == NULL){
        printf("Erro de alocação da lista de adjacências: falha no malloc");
        return NULL;
    }
    no* no_atual = nos->primeiro; 
    for (int itera_nos=0; itera_nos< nos->num_elementos; itera_nos++){
        lista* arestas_no_atual = grafo_itera_arestas_aux(no_atual, arestas);
        no* no_contendo_arestas_do_atual = no_cria((void*)arestas_no_atual);
        lista_insere(lista_de_adjacencias, no_contendo_arestas_do_atual, -1);
        no_atual = no_atual->prox;
    }
    grafo* novo_grafo = malloc(sizeof(grafo));
    if(novo_grafo ==NULL){
        printf("Erro de alocação no grafo: falha no malloc");
        return NULL;
    }
    novo_grafo->lista_de_adjacencias=lista_de_adjacencias;
    return novo_grafo;
}
lista* grafo_itera_arestas_aux(no* no_atual, lista* arestas) {
    lista* nova_lista = lista_cria();
    if (nova_lista == NULL) {
        printf("Erro de alocação da lista de arestas: falha no malloc");
        return NULL;
    }
    nova_lista->elemento_de_partida = *(tipo_no*)no_atual->data;
    no* no_que_contem_aresta_atual = arestas->primeiro;
    while (no_que_contem_aresta_atual != NULL) {
        aresta* aresta_atual = (aresta*)no_que_contem_aresta_atual->data;
        tipo_no inicio_aresta_atual = aresta_atual->inicio;
        if (*(tipo_no*)no_atual->data == inicio_aresta_atual) {
            lista_insere(nova_lista, no_cria((void*)aresta_atual), -1);
        }
        no_que_contem_aresta_atual = no_que_contem_aresta_atual->prox;
    }

    return nova_lista;
}
void grafo_printa(grafo* g) {
    lista* lista_de_adjacencias = g->lista_de_adjacencias;
    no* no_lista_atual = lista_de_adjacencias->primeiro; 
    while (no_lista_atual != NULL) {
        no* no_aresta_atual = ((lista*)no_lista_atual->data)->primeiro;
        while (no_aresta_atual != NULL) {
            aresta* aresta_atual = (aresta*)no_aresta_atual->data;
            printf("%c -> %c \n", aresta_atual->inicio, aresta_atual->fim);
            no_aresta_atual = no_aresta_atual->prox;
        }
        no_lista_atual = no_lista_atual->prox;
    }
}


void grafo_destroi(grafo* g) {
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    while (no_lista_atual != NULL) {
        lista* arestas = (lista*)no_lista_atual->data;
        no* no_aresta_atual = arestas->primeiro;
        while (no_aresta_atual != NULL) {
            no* prox_aresta = no_aresta_atual->prox;
            aresta* aresta_atual = (aresta*)no_aresta_atual->data;
            free(aresta_atual);
            free(no_aresta_atual);
            no_aresta_atual = prox_aresta;
        }
        no* prox_lista = no_lista_atual->prox;
        free(arestas);
        free(no_lista_atual);
        no_lista_atual = prox_lista;
    }
    free(g->lista_de_adjacencias);
    free(g);
}
void grafo_testa() {
    lista* nos = lista_cria();
    lista* arestas = lista_cria();

    const char* a = "a";
    const char* b = "b";
    const char* c = "c";
    const char* d = "d";

    no* no_a = no_cria((void*)a);
    no* no_b = no_cria((void*)b);
    no* no_c = no_cria((void*)c);
    no* no_d = no_cria((void*)d);

    lista_insere(nos, no_a, -1);
    lista_insere(nos, no_b, -1);
    lista_insere(nos, no_c, -1);
    lista_insere(nos, no_d, -1);

    aresta* aresta_AB = aresta_cria(*(tipo_no*)a, *(tipo_no*)b);
    aresta* aresta_AC = aresta_cria(*(tipo_no*)a, *(tipo_no*)c);
    aresta* aresta_BD = aresta_cria(*(tipo_no*)b, *(tipo_no*)d);
    aresta* aresta_CD = aresta_cria(*(tipo_no*)c, *(tipo_no*)d);
    aresta* aresta_DA = aresta_cria(*(tipo_no*)d, *(tipo_no*)a);
    aresta* aresta_BA = aresta_cria(*(tipo_no*)b, *(tipo_no*)a);
    aresta* aresta_DD= aresta_cria(*(tipo_no*)d, *(tipo_no*)d);
    aresta* aresta_BC= aresta_cria(*(tipo_no*)b, *(tipo_no*)c);

    lista_insere(arestas, no_cria((void*)aresta_AB), -1);
    lista_insere(arestas, no_cria((void*)aresta_AC), -1);
    lista_insere(arestas, no_cria((void*)aresta_BD), -1);
    lista_insere(arestas, no_cria((void*)aresta_CD), -1);
    lista_insere(arestas, no_cria((void*)aresta_DA), -1);
    lista_insere(arestas, no_cria((void*)aresta_BA), -1);
    lista_insere(arestas, no_cria((void*)aresta_DD), -1);
    lista_insere(arestas, no_cria((void*)aresta_BC), -1);

    grafo* g = grafo_cria(nos, arestas);
    grafo_printa(g);
    

    lista_destroi(nos);  
    lista_destroi(arestas);  
    grafo_destroi(g);  
}
