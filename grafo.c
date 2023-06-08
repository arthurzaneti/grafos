#include "grafo.h"
#include "aresta.h"
#include <stdlib.h>
#include <stdio.h>

grafo* grafo_cria(lista* nos, lista* arestas){
    no* no_atual = nos->primeiro; 
    for (int itera_nos=0; itera_nos< nos->num_elementos; itera_nos++){
        
    }
}
lista* grafo_itera_arestas_aux(no* no_atual, lista* arestas){
    lista* nova_lista = lista_cria();
    if (nova_lista ==NULL){
        printf("Erro de alocação no grafo: falha no malloc");
        return NULL;
    }
        nova_lista->elemento_de_partida = no_atual->data;
        no* no_que_contem_aresta_atual = arestas->primeiro;
        for (int itera_arestas=0; itera_arestas<arestas->num_elementos; itera_arestas++){
            aresta* aresta_aresta = (aresta*)no_que_contem_aresta_atual->data;
            tipo_no no_atual_data_derreferenciado = *(int*)(no_atual->data);
            tipo_no inicio_aresta_atual = aresta_aresta->inicio;
            if (no_atual_data_derreferenciado == inicio_aresta_atual){ 
                lista_insere(nova_lista, aresta_aresta,-1);
            }
        }
}