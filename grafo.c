#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

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
lista* grafo_itera_arestas_aux(no* no_atual, lista* arestas){
    lista* nova_lista = lista_cria();
    if (nova_lista ==NULL){
        printf("Erro de alocação da lista de arestas: falha no malloc");
        return NULL;
    }
    nova_lista->elemento_de_partida = *(tipo_no*)no_atual->data;
    no* no_que_contem_aresta_atual = arestas->primeiro;
    while(no_que_contem_aresta_atual!=NULL){
        aresta* aresta_aresta = (aresta*)no_que_contem_aresta_atual->data;
        tipo_no inicio_aresta_atual = aresta_aresta->inicio;
        if (*(tipo_no*)no_atual->data == inicio_aresta_atual){ 
            lista_insere(nova_lista, no_que_contem_aresta_atual,-1);
        }
        no_que_contem_aresta_atual = no_que_contem_aresta_atual->prox;
    }
    return nova_lista; 
}
void grafo_printa(grafo* g){
    lista* lista_de_adjacencias = g->lista_de_adjacencias;
    no* lista_atual = (lista_de_adjacencias->primeiro); 
    while (lista_atual!=NULL){
        no* aresta_atual = ((lista*)(lista_atual->data))->primeiro;
        while(aresta_atual!=NULL){
            printf("%c -> %c \n", ((aresta*)(aresta_atual->data))->inicio, ((aresta*)(aresta_atual->data))->fim);
            aresta_atual=aresta_atual->prox;
        }
        lista_atual= lista_atual->prox;
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

    const char* dataA = "a";
    const char* dataB = "b";
    const char* dataC = "c";
    const char* dataD = "d";

    no* nodeA = no_cria((void*)dataA);
    no* nodeB = no_cria((void*)dataB);
    no* nodeC = no_cria((void*)dataC);
    no* nodeD = no_cria((void*)dataD);

    lista_insere(nos, nodeA, -1);
    lista_insere(nos, nodeB, -1);
    lista_insere(nos, nodeC, -1);
    lista_insere(nos, nodeD, -1);

    aresta* edgeAB = aresta_cria((tipo_no)dataA, (tipo_no)dataB);
    aresta* edgeAC = aresta_cria((tipo_no)dataA, (tipo_no)dataC);
    aresta* edgeBD = aresta_cria((tipo_no)dataB, (tipo_no)dataD);
    aresta* edgeCD = aresta_cria((tipo_no)dataC, (tipo_no)dataD);

    lista_insere(arestas, no_cria((void*)edgeAB), -1);
    lista_insere(arestas, no_cria((void*)edgeAC), -1);
    lista_insere(arestas, no_cria((void*)edgeBD), -1);
    lista_insere(arestas, no_cria((void*)edgeCD), -1);

    grafo* g = grafo_cria(nos, arestas);
    grafo_printa(g);

    lista_destroi(nos);  // Free the node list and its nodes
    lista_destroi(arestas);  // Free the edge list and its edges
    grafo_destroi(g);  // Free the graph and its lists
}
