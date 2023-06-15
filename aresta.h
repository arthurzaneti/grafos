#ifndef _ARESTA_H_
#define _ARESTA_H_

typedef struct _aresta{
    int inicio;
    int fim;
    float peso;
}aresta;

aresta *aresta_cria(int inicio, int fim, float peso);
void aresta_destroi(aresta* a);
void aresta_testa();

#endif