#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

lista* lista_cria(){
    lista* l = malloc(sizeof(struct lista));
    if (l==NULL){
        printf("Erro de alocação: falha no malloc");
        return NULL;
    };
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->num_elementos = 0;
    return (l);
};
void insere_inicio(lista* l, no* elem){
    if(l->primeiro ==NULL) insere_lista_vazia(l, elem);
    else{
        elem->ant = NULL;
        elem->prox= l->primeiro;
        l->primeiro = elem;
    }
};
void insere_fim(lista*l, no* elem){
    if(l->primeiro ==NULL) insere_lista_vazia(l, elem);
    else{
        elem->ant = l->ultimo;
        elem->prox= NULL;
        l->ultimo = elem;
    }
}
void insere_lista_vazia(lista*l, no* elem){
    l->ultimo = elem;
    l->primeiro = elem;
    elem->prox = NULL;
    elem->ant =NULL;
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
            elem->prox = no_atual->prox;
            elem->ant = no_atual;
            no_atual->prox = elem;
            elem->prox->ant = elem;
            
        }
    }
    l->num_elementos++;
}
void* lista_remove_inicio(lista*l){
    no* no_remover = l->primeiro;
    no_remover->prox->ant = NULL;
    l->primeiro = no_remover->prox;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    return (valor_do_no);
}
void* lista_remove_fim(lista*l){
    no* no_remover = l->ultimo;
    no_remover->ant->prox = NULL;
    l->ultimo = no_remover->ant;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    return (valor_do_no);
}

void* lista_remove(lista *l, int pos){
    if(!verifica_remoção(l,pos)) return;
    if (pos <0) pos += l->num_elementos;
    if (pos==0)return lista_remove_inicio(l);
    if (pos==l->num_elementos) return lista_remove_fim(l);
    int contador = 0;
    no* no_atual = l->primeiro;
    while (contador<=pos){
        no_atual = no_atual->prox;
        contador++;
    } 
    no_atual->ant->prox = no_atual->prox;
    no_atual->prox->ant = no_atual->ant;
    void* valor_do_no = no_atual->data;
    free(no_atual);   
    return (valor_do_no);
}
bool verifica_remoção(lista*l, int pos){
    if(l==NULL){
        printf("Erro de remoção: Lista nula");
        return false;
    }
    if(l->primeiro ==NULL){
        printf("Erro de remoção: Lista sem nenhum elemento");
        return false;
    }
    if (pos <0) pos += l->num_elementos;
    if (pos <0){
        printf("Erro de remoção: Posição muito pequena");
        return false;
    }
    if(pos>l->num_elementos){
        printf("Erro de remoção: Posição muito grande");
        return false;
    }
    return true;
}
void lista_destroi(lista*l){
    if(l->primeiro==NULL) {
        free(l);
        return;
    }
    no* no_atual = l->primeiro;
    while(no_atual!=NULL){
        no* prox_do_atual = no_atual->prox;
        free(no_atual);
        no_atual = prox_do_atual;
    }
    free(l);
}
