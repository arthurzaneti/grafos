#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

#define NAO_ITERANDO 0
#define ITERANDO_TODO_GRAFO 1
#define ITERANDO_POR_LINHA 2

typedef struct grafo{
    lista* lista_de_adjacencias;
    bool orientado;
    no* aresta_atual;
    no* lista_atual;
    int iteracao;
    int num_arestas;
}grafo;


Grafo g_cria(int tamanho, bool orientado){
    UNUSED(tamanho);
    grafo* novo_grafo = malloc(sizeof(grafo));
    assert(novo_grafo !=NULL);
    novo_grafo -> lista_de_adjacencias = lista_cria();
    novo_grafo -> orientado = orientado;
    novo_grafo -> num_arestas = 0;
    return(novo_grafo);
}

static void g_vertice_cria(Grafo g, int data){
    lista* nova_lista = lista_cria();
    if(nova_lista==NULL){
        printf("Erro na criação do vértice: falha no malloc");
        return;
    }
    nova_lista->elemento_de_partida = data;
    no* no_nova_lista = no_cria((void*)nova_lista);
    lista_insere(g->lista_de_adjacencias, no_nova_lista, -1);
} 

void g_destroi(Grafo g) {
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    while (no_lista_atual != NULL) {
        lista* arestas = (lista*)no_lista_atual->data;
        no* no_aresta_atual = arestas->primeiro;
        while (no_aresta_atual != NULL) {
            no* prox_aresta = no_aresta_atual->prox;
            aresta* aresta_atual = (aresta*)no_aresta_atual->data;
            assert(no_aresta_atual!=NULL);
            assert(aresta_atual!=NULL);
            free(no_aresta_atual);
            free(aresta_atual);
            no_aresta_atual = prox_aresta;
        }
        no* prox_lista = no_lista_atual->prox;
        assert(arestas!=NULL);
        assert(no_lista_atual!=NULL);
        free(arestas);
        free(no_lista_atual);
        no_lista_atual = prox_lista;
    }
    assert(g->lista_de_adjacencias !=NULL);
    assert(g != NULL);
    free(g->lista_de_adjacencias);
    free(g);
}


int g_nvertices(Grafo g){
    assert(g!=NULL);
    return(g->lista_de_adjacencias->num_elementos);
}

static void cria_vertices_insercao(Grafo g, int origem, int destino){
    bool origem_existe = false;
    bool destino_existe = false;
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    while(no_lista_atual !=NULL){
        if(((lista*)(no_lista_atual->data))->elemento_de_partida == origem) origem_existe =true;
        if(((lista*)(no_lista_atual->data))->elemento_de_partida == destino) destino_existe =true;
    }
    if(!origem_existe) g_vertice_cria(g, origem);
    if(!destino_existe) g_vertice_cria(g, destino);
}

static void g_ins_aresta_inversa(Grafo g, int origem, int destino, float peso){
    aresta* nova_aresta = aresta_cria(origem, destino, peso);
    no* no_nova_aresta = no_cria((void*)nova_aresta);
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    
    while(no_lista_atual !=NULL){
        lista* lista_atual = no_lista_atual->data;
        if(lista_atual->elemento_de_partida == origem){
            lista_insere(lista_atual, no_nova_aresta, 0);
            break;
        }
        no_lista_atual = no_lista_atual->prox;
    }
    g->num_arestas++;
}

void g_ins_aresta(Grafo g, int origem, int destino, float peso) {
    assert(g!=NULL);
    cria_vertices_insercao(g, origem, destino);
    
    aresta* nova_aresta = aresta_cria(origem, destino, peso);
    no* no_nova_aresta = no_cria((void*)nova_aresta);
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    
    while(no_lista_atual !=NULL){
        lista* lista_atual = no_lista_atual->data;
        if(lista_atual->elemento_de_partida == origem){
            lista_insere(lista_atual, no_nova_aresta, 0);
            printf("%d \n", g->num_arestas);
            break;
        }
        no_lista_atual = no_lista_atual->prox;
    }
    if(!g->orientado) g_ins_aresta_inversa (g, destino, origem, peso);
    g->num_arestas++; 
}



static void g_rem_aresta_inversa(Grafo g, int origem, int destino){
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
    g->num_arestas--;
}

void g_rem_aresta(Grafo g, int origem, int destino){
    if (g ==NULL){
        printf("Erro na remoção da aresta: grafo nulo\n");
        return;
    }
    if ( g->lista_de_adjacencias->num_elementos ==0){
        printf("Erro na remoção da aresta: grafo vazio\n");
        return;
    }
    no* no_lista_atual = g->lista_de_adjacencias->primeiro;
    bool achei = false;
    while (no_lista_atual!=NULL){
        lista* lista_atual = (no_lista_atual->data);
        if(lista_atual->elemento_de_partida == origem){
            achei = true;
            break;
        }
        no_lista_atual= no_lista_atual->prox;
    }
    if(!achei){
        printf("Erro na remoção da aresta: no de origem não existe\n");
        return;
    }
   
    lista *lista_com_aresta_remover = (lista*)no_lista_atual->data;
    no *no_atual = lista_com_aresta_remover->primeiro;
    achei = false;
    int pos = 0;
    while (no_atual!=NULL){
        aresta* aresta_atual = (no_atual->data);
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
        printf("Erro na remoção da aresta: no de destino não existe\n");
    }
    if(!g->orientado){
        g_rem_aresta_inversa(g, origem, destino);
    }
    g->num_arestas--;
}

void g_arestas(Grafo g) {
    if (g == NULL) {
        printf("Erro na inicialização de iteração de arestas: grafo não existe\n");
        return;
    }
    if(g->lista_de_adjacencias->num_elementos ==0){
        printf("Erro na inicialização de iteração de arestas: grafo vazio\n");
        return;
    }
    g->lista_atual = g->lista_de_adjacencias->primeiro;
    g->aresta_atual = ((lista*)(g->lista_atual->data))->primeiro;

    g->iteracao = ITERANDO_TODO_GRAFO;
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
        printf("Erro em arestas que partem: no de origem não existe\n");
        return;
    }
    g->lista_atual = no_lista_atual;
    g->aresta_atual = ((lista*)no_lista_atual->data)->primeiro;
    g->iteracao = ITERANDO_POR_LINHA;
    return;
}

static void para_iteracao (grafo*g){
    g->aresta_atual = NULL;
    g->lista_atual = NULL;
    g->iteracao = NAO_ITERANDO;
}
bool g_proxima_aresta(Grafo g, int* origem, int* destino, float* peso) {
    if (g == NULL) {
        printf("Erro em iteração de arestas: grafo nulo\n");
        return false;
    }

    if (g->aresta_atual == NULL || g->lista_atual == NULL) {
        printf("Erro em iteração de arestas: tentando acessar próxima aresta fora da iteração\n");
        return false;
    }

    *origem = ((aresta*)(g->aresta_atual->data))->inicio;
    *destino = ((aresta*)(g->aresta_atual->data))->fim;
    *peso = ((aresta*)(g->aresta_atual->data))->peso;

    if (g->aresta_atual->prox == NULL) {
        if (g->lista_atual->prox == NULL) {
            para_iteracao(g);
            return false;
        } else if (g->iteracao == ITERANDO_TODO_GRAFO) {
            g->lista_atual = g->lista_atual->prox;
            g->aresta_atual = ((lista*)(g->lista_atual->data))->primeiro;
            return true;
        } else {
            para_iteracao(g);
            return false;
        }
    }

    g->aresta_atual = g->aresta_atual->prox;

    return true;
}



void grafo_testa() {
    
    Grafo g = g_cria(0, false);

    assert(g->lista_de_adjacencias->num_elementos == 0);
    

    g_ins_aresta(g, 1, 1, 1.5);
    
    g_ins_aresta(g, 2, 3, 3.0);
    

    g_ins_aresta(g, 3, 3, 1.5);
    g_ins_aresta(g, 4, 4, 2.0);
    
    g_arestas(g);

    int origem = 0;
    int destino = 0;
    float peso = 0.0;

    while (g_proxima_aresta(g, &origem, &destino, &peso)) {
        printf("Aresta: %d -> %d, Peso: %.2f\n", origem, destino, peso);
    }
    printf("Aresta: %d -> %d, Peso: %.2f\n", origem, destino, peso);

    g_destroi(g);
}