#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define FATOR_DE_REALOCAÇAO 2
lista* lista_cria(int tam){
    lista* l = malloc(sizeof(struct lista));
    if (l==NULL){
        printf("Erro de alocação: falha no malloc");
        return NULL;
    };
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tamanho_lista = tam;
    l->num_elementos = 0;
    return (l);
};
void insere_inicio(lista* l, no* elem){
    if(l->primeiro ==NULL) insere_lista_vazia(l, elem);
    else{
        elem->prox= l->primeiro;
        l->primeiro = elem;
    }
};
void insere_fim(lista*l, no* elem){
    if(l->primeiro ==NULL) insere_lista_vazia(l, elem);
    else{
        elem->prox= l->primeiro;
        l->primeiro = elem;
    }
}
void insere_lista_vazia(lista*l, no* elem){
    l->ultimo = elem;
    l->primeiro = elem;
    elem->prox = NULL;
}
void insere(lista*l, no* elem, int pos){
    if (l==NULL){
        printf("Erro de inserção: Lista nula");
        return;
    }else if(elem==NULL){
        printf("Erro de inserção: Nó nulo");
        return;
    }
    if (pos<0)pos+= l->num_elementos;
    if (pos<0){
        printf("Erro de inserção: Posição muito pequena");
        return;
    }else if(pos > l->num_elementos){
        printf("Erro de inserção: Posição muito grande");
        return;
    }
    else{
        if (pos==0) insere_inicio(l, elem);
        else if (pos==l->num_elementos) insere_fim(l, elem);
        else{
            no *no_atual = l->primeiro;
            int contador = 0;
            while(contador < pos){
                no_atual = no_atual->prox;
                contador++;
            }
            no* prox_do_atual = no_atual->prox;
            no_atual->prox = elem;
            elem->prox = prox_do_atual;
        }
    }
    l->num_elementos++;
}
no* lista_remove_inicio(lista*l){
    no* no_remover = l->primeiro;
    l->primeiro = no_remover->prox;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    return (valor_do_no);
}
no* lista_remove_fim(lista*l){
    int contador = 0;
    no* no_atual = l->primeiro;
    while (contador<l->num_elementos-1){
        no_atual = no_atual->prox;
        contador++;
    } 
    no* no_remover = no_atual->prox;
    no_atual->prox = NULL;
    void* valor_do_no = no_remover->data;
    free(no_remover); 
    l->u  
    return (valor_do_no);

}
void* lista_remove(lista *l, int pos){
    if (pos <0) pos += l->num_elementos;
    if (pos <0){
        printf("Erro de remoção: Posição muito pequena");
        return NULL;
    }
    if(pos>l->num_elementos){
        printf("Erro de remoção: Posição muito grande");
        return NULL;
    }
    if (pos==0)return lista_remove_inicio(l);
    if (pos==l->num_elementos) return lista_remove_fim(l);
    int contador = 0;
    no* no_atual = l->primeiro;
    while (contador<pos){
        no_atual = no_atual->prox;
        contador++;
    } 
    no* no_remover = no_atual->prox;
    no_atual->prox = no_remover->prox;
    void* valor_do_no = no_remover->data;
    free(no_remover);   
    return (valor_do_no);
}