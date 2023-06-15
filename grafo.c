#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

typedef struct grafo{
    lista* lista_de_adjacencias;
    bool orientado;
    no* aresta_atual;
    no* lista_atual;
}grafo;


Grafo g_cria(int tamanho, bool orientado){
    UNUSED(tamanho);
    grafo* novo_grafo = malloc(sizeof(grafo));
    assert(novo_grafo !=NULL);
    novo_grafo -> lista_de_adjacencias = lista_cria();
    novo_grafo -> orientado = orientado;
    return(novo_grafo);
}
static void vertice_cria(Grafo g, int data){
    lista* nova_lista = lista_cria();
    if(nova_lista==NULL){
        printf("Erro na criação do vértice: falha no malloc");
    }
    nova_lista->elemento_de_partida = no_cria((void*)data);
} 
void g_destroi(Grafo g) {
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

int g_nvertices(Grafo g){
    assert(g!=NULL);
    return(g->lista_de_adjacencias->num_elementos);
}

static void g_ins_aresta_inversa_orientado (Grafo g, int origem, int destino, float peso){
    no* novo_no = no_cria((void*)(aresta_cria(origem, destino, peso)));
    no* no_atual = g->lista_de_adjacencias->primeiro;
    while (no_atual!=NULL){
        lista* lista_do_no_atual =  (lista*)(no_atual->data);
        if(lista_do_no_atual->elemento_de_partida == origem){
            lista_insere(lista_do_no_atual, novo_no, -1);
        }
        if (lista_do_no_atual->elemento_de_partida == destino){
        }
        no_atual = no_atual->prox;
    }
}

void g_ins_aresta(Grafo g, int origem, int destino, float peso){
    no* novo_no = no_cria((void*)(aresta_cria(origem, destino, peso)));
    no* no_atual = g->lista_de_adjacencias->primeiro;
    bool origem_existe = false;
    bool destino_existe = false;
    while (no_atual!=NULL){
        lista* lista_do_no_atual =  (lista*)(no_atual->data);
        if(lista_do_no_atual->elemento_de_partida == origem){
            lista_insere(lista_do_no_atual, novo_no, -1);
            origem_existe = true;
        }
        if (lista_do_no_atual->elemento_de_partida == destino){
            destino_existe = true;
        }
        no_atual = no_atual->prox;
    }
    if(!origem_existe){
        printf("Erro de inserção de aresta: no de origem não existe");
        free(novo_no);
    }
    if(!destino_existe){
        printf("Erro de inserção de aresta: no de destino não existe");
        free(novo_no);
    }
    if (!g->orientado){
        g_ins_aresta_inversa_orientado(g, destino, origem, peso);
    }
}

static void g_rem_aresta_inversa_orientado(Grafo g, int origem, int destino){
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    while (no_lista_atual!=NULL){
        lista* lista_atual = no_lista_atual->data;
        if(lista_atual->elemento_de_partida == origem){
            break;
        }
        no_lista_atual= no_lista_atual->prox;
    }

    lista *lista_com_aresta_remover = no_lista_atual->data;
    no *no_atual = lista_com_aresta_remover->primeiro;
    int pos = 0;
    while (no_atual!=NULL){
        aresta* aresta_atual = no_atual->data;
        if(aresta_atual->fim == destino){
            aresta_destroi(aresta_atual);
            lista_remove(lista_com_aresta_remover, pos);
            break;
        }
        pos++;
        no_atual = no_atual->prox;
    }
}

void g_rem_aresta(Grafo g, int origem, int destino){
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    bool achei = false;
    while (no_lista_atual!=NULL){
        lista* lista_atual = no_lista_atual->data;
        if(lista_atual->elemento_de_partida == origem){
            achei = true;
            break;
        }
        no_lista_atual= no_lista_atual->prox;
    }
    if(!achei){
        printf("Erro na remoção da aresta: no de origem não existe");
        return;
    }
   
    lista *lista_com_aresta_remover = no_lista_atual->data;
    no *no_atual = lista_com_aresta_remover->primeiro;
    achei = false;
    int pos = 0;
    while (no_atual!=NULL){
        aresta* aresta_atual = no_atual->data;
        if(aresta_atual->fim == destino){
            aresta_destroi(aresta_atual);
            lista_remove(lista_com_aresta_remover, pos);
            achei = true;
            break;
        }
        pos++;
        no_atual = no_atual->prox;
    }
    if (!achei){
        printf("Erro na remoção da aresta: no de destino não existe");
    }
    if(!g->orientado){
        g_rem_aresta_inversa_orientado(g, origem, destino);
    }
}

void g_arestas(Grafo g){
    if(g==NULL){
        printf("Erro em iteração de arestas: grafo nulo");
        return;
    }
    g->lista_atual = g->lista_de_adjacencias->primeiro;
    g->aresta_atual = ((lista*)(g->lista_atual->data))->primeiro;
}

void g_arestas_que_partem(Grafo g, int origem){
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    bool achei = false;
    while (no_lista_atual!=NULL){
        lista* lista_atual = no_lista_atual->data;
        if(lista_atual->elemento_de_partida == origem){
            achei = true;
            break;
        }
        no_lista_atual= no_lista_atual->prox;
    }
    if(!achei){
        printf("Erro na remoção da aresta: no de origem não existe");
        return;
    }
    g->lista_atual = no_lista_atual;
    g->aresta_atual = ((lista*)no_lista_atual->data)->primeiro;
    return;
}

bool g_proxima_aresta(Grafo g, int* origem, int* destino, float* peso) {
    if (g == NULL) {
        printf("Erro em iteração de arestas: grafo nulo");
        return false;
    }

    if (g->aresta_atual == NULL || g->lista_atual == NULL) {
        printf("Erro em iteração de arestas: tentando acessar próxima aresta fora da iteração");
        return false;
    }

    *origem = ((aresta*)(g->aresta_atual))->inicio;
    *destino = ((aresta*)(g->aresta_atual))->fim;
    *peso = ((aresta*)(g->aresta_atual))->peso;

    if (g->aresta_atual->prox == NULL) {
        if (g->lista_atual->prox == NULL) {
            g->lista_atual = NULL;
            g->aresta_atual = NULL;
            return false;
        } else {
            g->lista_atual = g->lista_atual->prox;
            g->aresta_atual = ((lista*)(g->lista_atual->data))->primeiro;
            return true;
        }
    }

    g->aresta_atual = g->aresta_atual->prox;
    return true;
}

void grafo_testa() {
    Grafo g = g_cria(1, false);
    // Test ins_aresta
    g_ins_aresta(g, 0, 1, 1.5);
    g_ins_aresta(g, 1, 2, 2.5);
    g_ins_aresta(g, 2, 3, 3.5);
    g_ins_aresta(g, 3, 4, 4.5);
    g_ins_aresta(g, 4, 0, 5.5);

    // Test g_arestas
    g_arestas(g);
    int origem, destino;
    float peso;
    while (g_proxima_aresta(g, &origem, &destino, &peso)) {
        printf("Aresta: %d -> %d, Peso: %.2f\n", origem, destino, peso);
    }
    // Expected output:
    // Aresta: 0 -> 1, Peso: 1.50
    // Aresta: 1 -> 2, Peso: 2.50
    // Aresta: 2 -> 3, Peso: 3.50
    // Aresta: 3 -> 4, Peso: 4.50
    // Aresta: 4 -> 0, Peso: 5.50

    // Test g_arestas_que_partem
    g_arestas_que_partem(g, 2);
    while (g_proxima_aresta(g, &origem, &destino, &peso)) {
        printf("Aresta que parte de 2: %d -> %d, Peso: %.2f\n", origem, destino, peso);
    }
    // Expected output:
    // Aresta que parte de 2: 2 -> 3, Peso: 3.50

    // Test g_rem_aresta
    g_rem_aresta(g, 3, 4);

    // Test g_arestas after removing an edge
    g_arestas(g);
    while (g_proxima_aresta(g, &origem, &destino, &peso)) {
        printf("Aresta: %d -> %d, Peso: %.2f\n", origem, destino, peso);
    }
    // Expected output:
    // Aresta: 0 -> 1, Peso: 1.50
    // Aresta: 1 -> 2, Peso: 2.50
    // Aresta: 2 -> 3, Peso: 3.50
    // Aresta: 4 -> 0, Peso: 5.50

    // Test g_destroi
    g_destroi(g);
}
