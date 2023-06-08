#include "grafo.h"
#include "aresta.h"

grafo* grafo_cria(lista* nos, lista* arestas){
    no* no_atual = nos->primeiro; 
    for (int itera_nos=0; itera_nos< nos->num_elementos; itera_nos++){
        lista* nova_lista = lista_cria();
        nova_lista->elemento_de_partida = no_atual->data;
        no* aresta_atual = arestas->primeiro;
        for (int itera_arestas=0; itera_arestas<arestas->num_elementos; itera_arestas++){
            if (*(int*)(no_atual->data) == *((int*)((aresta*)(aresta_atual->data))->inicio)){ 
            }
        }
    }
}