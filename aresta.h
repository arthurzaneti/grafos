#ifndef _ARESTA_H_
#define _ARESTA_H_

typedef int tipo_no; 
typedef struct _aresta{
    tipo_no inicio;
    tipo_no fim;
    float peso;
}aresta;
aresta *aresta_cria(tipo_no inicio, tipo_no fim, float peso);
void aresta_destroi(aresta* a);
void aresta_testa();

#endif