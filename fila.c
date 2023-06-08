#include "fila.h"
#include "aresta.h"
#include <assert.h>
#include <stdlib.h>



fila fila_cria(int cap){
    fila f = malloc(sizeof(struct _fila));
    if (f == NULL) return NULL;
    f->vet = malloc(cap * sizeof(dado_t));
    if (f->vet == NULL) {
        free(f);
        return NULL;
    }
    f->cap = cap;
    f->num = 0;
    return f;   
}

void fila_destroi(fila f){
    free(f->vet);
    free(f);
}

dado_t fila_remove(fila f){
    assert(!fila_vazia(f));
    return f->vet[--f->num];
}

void fila_insere(fila f, dado_t d){
    assert(!fila_cheia(f));
    f->vet[f->num++]= d;
}

dado_t fila_mostra_inicio(fila f){
    return f->vet[0];
}

dado_t fila_mostra_fim(fila f){
    return f->vet[(f->cap)-1];
}

bool fila_cheia(fila f){
    return(f->cap==f->num);
}

bool fila_vazia(fila f){
    return(f->num ==0);
}
void fila_testa(){
    fila f = fila_cria(5);

    // Create some data to insert into the fila
    tipo_no no1 = 'A';
    tipo_no no2 = 'B';
    tipo_no no3 = 'C';
    aresta aresta1 = aresta_cria('D', 'E');

    // Create some dado_t values and insert them into the fila
    dado_t dado1;
    dado1.no = &no1;
    fila_insere(f, dado1);

    dado_t dado2;
    dado2.aresta = aresta1;
    fila_insere(f, dado2);

    dado_t dado3;
    dado3.no = &no2;
    fila_insere(f, dado3);

    dado_t dado4;
    dado4.no = &no3;
    fila_insere(f, dado4);

    // Remove an element from the fila
    dado_t removed_data = fila_remove(f);
    if (removed_data.no != NULL){
        
    }
    if (removed_data.no != NULL) {
        printf("Removed data (no): %c\n", removed_data.no);
    } else if (removed_data.aresta != NULL) {
        printf("Removed data (aresta): %c -> %c\n", removed_data.aresta->inicio, removed_data.aresta->fim);
    }

    // Display the first element in the fila
    dado_t first_data = fila_mostra_inicio(f);
    if (first_data.no != NULL) {
        printf("First data (no): %c\n", first_data.no);
    } else if (first_data.aresta != NULL) {
        printf("First data (aresta): %c -> %c\n", first_data.aresta->inicio, first_data.aresta->fim);
    }

    // Display the last element in the fila
    dado_t last_data = fila_mostra_fim(f);
    if (last_data.no != NULL) {
        printf("Last data (no): %c\n", last_data.no);
    } else if (last_data.aresta != NULL) {
        printf("Last data (aresta): %c -> %c\n", last_data.aresta->inicio, last_data.aresta->fim);
    }

    // Clean up and destroy the fila
    fila_destroi(f);

}
int main(){
    fila_testa();
    return (0);
}






