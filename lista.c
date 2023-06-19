#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

lista* lista_cria(){
    lista* l = malloc(sizeof(lista));
    if (l==NULL){
        printf("Erro de alocação da lista: falha no malloc");
        return NULL;
    };
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->num_elementos = 0;
    return (l);
}

no* no_cria(void*data){
    no* n = malloc(sizeof(no));
    if (n==NULL){
        printf("Erro de alocação do no: falha no malloc");
        return NULL;
    }
    n->data = data;
    n->prox = NULL;
    n->ant = NULL;
    return n;
}

void lista_insere_inicio_aux(lista* l, no* elem){
    if(l->primeiro ==NULL) lista_insere_vazia_aux(l, elem);
    else{
        elem->ant = NULL;
        elem->prox= l->primeiro;
        elem->prox->ant = elem;
        l->primeiro = elem;
    }
}

void lista_insere_fim_aux(lista*l, no* elem){
    if(l->primeiro ==NULL) lista_insere_vazia_aux(l, elem);
    else{

        elem->ant = l->ultimo;
        elem->prox= NULL;
        elem->ant->prox = elem;
        l->ultimo = elem;
    }
}

void lista_insere_vazia_aux(lista*l, no* elem){
    l->ultimo = elem;
    l->primeiro = elem;
    elem->prox = NULL;
    elem->ant =NULL;
}

void lista_insere(lista*l, no* elem, int pos){
    if (l==NULL){
        printf("Erro de inserção: Lista nula");
        return;
    }else if(elem==NULL){
        printf("Erro de inserção: Nó nulo");
        return;
    }
    if (pos<0)pos+= l->num_elementos+1;
    if (pos<0){
        printf("Erro de inserção: Posição muito pequena");
        return;
    }else if(pos > l->num_elementos){
        printf("Erro de inserção: Posição muito grande");
        return;
    }
    else{
        if (pos==0) {
            printf("Inserindo no inicio\n");
            lista_insere_inicio_aux(l, elem);
        }
        else if (pos==l->num_elementos) {
            printf("Inserindo no final\n");
            lista_insere_fim_aux(l, elem);
        }
        else{
            printf("Inserção normal\n");
            no *no_atual = l->primeiro;
            int contador = 0;
            while(contador < pos-1){
                no_atual = no_atual->prox;
                contador++;
            }
            assert(no_atual->prox !=NULL);
            elem->prox = no_atual->prox;
            elem->ant = no_atual;
            no_atual->prox = elem;
            elem->prox->ant = elem;
            
        }
    }
    l->num_elementos++;
}
void* lista_remove_inicio_aux(lista*l){
    no* no_remover = l->primeiro;
    no_remover->prox->ant = NULL;
    l->primeiro = no_remover->prox;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    l->num_elementos--;
    return (valor_do_no);
}

void* lista_remove_fim_aux(lista*l){
    no* no_remover = l->ultimo;
    no_remover->ant->prox = NULL;
    l->ultimo = no_remover->ant;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    l->num_elementos--;
    return (valor_do_no);
}

void* lista_remove(lista *l, int pos){
    if(!verifica_remoção_aux(l,pos)) return NULL;
    if (pos <0) pos += l->num_elementos;
    if (pos==0)return lista_remove_inicio_aux(l);
    if (pos==l->num_elementos) return lista_remove_fim_aux(l);
    int contador = 0;
    no* no_atual = l->primeiro;
    while (contador<pos){
        no_atual = no_atual->prox;
        contador++;
    } 
    no_atual->ant->prox = no_atual->prox;
    no_atual->prox->ant = no_atual->ant;
    void* valor_do_no = no_atual->data;
    free(no_atual);
    l->num_elementos--;   
    return (valor_do_no);
}

bool verifica_remoção_aux(lista*l, int pos){
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

void lista_testa() {
    lista* l = lista_cria();
    
    int a = 10;
    void* ptra = &a;
    no* no_int = no_cria(ptra);
    lista_insere(l, no_int, 0);
    assert(l->num_elementos == 1);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_int);
    
    char b = 'b';
    void* ptrb = &b;
    no* no_char = no_cria(ptrb);
    lista_insere(l, no_char, l->num_elementos);
    assert(l->num_elementos == 2);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_char);
    
    float c = 3.14;
    void* ptrc = &c;
    no* no_float = no_cria(ptrc);
    
    lista_insere(l, no_float, 1);
    assert(l->num_elementos == 3);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_char);
    

    int d = 20;
    void* ptrd = &d;
    no* no_negative = no_cria(ptrd);
    lista_insere(l, no_negative, -1);
    assert(l->num_elementos == 4);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_negative);

    int e = 30;
    void* ptre = &e;
    no* no_beyond = no_cria(ptre);
    lista_insere(l, no_beyond, -1);
    assert(l->num_elementos == 5);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_beyond);
    void* removed_data = lista_remove(l, 0);
    // ERRO NO PTRA, por algum motivo assert(removed_data == ptra) falha..
    assert(removed_data == ptra);
    assert(l->num_elementos == 4);
    assert(l->primeiro == no_float);

    removed_data = lista_remove(l, 2);
    assert(removed_data == ptrc);
    assert(l->num_elementos == 3);
    assert(l->ultimo == no_beyond);

    removed_data = lista_remove(l, l->num_elementos - 1);
    assert(removed_data == ptre);
    assert(l->num_elementos == 2);
    assert(l->ultimo == no_char);

    removed_data = lista_remove(l, -1);
    assert(removed_data == ptrd);
    assert(l->num_elementos == 1);
    assert(l->primeiro == no_float);

    removed_data = lista_remove(l, 10);
    assert(removed_data == NULL);
    assert(l->num_elementos == 1);
    assert(l->ultimo == no_float);

    lista_destroi(l);

    printf("Sucesso nos testes!\n");
}
