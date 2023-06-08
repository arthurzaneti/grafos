#ifndef _ARESTA_H_
#define _ARESTA_H_

typedef char tipo_no; 
typedef struct _aresta{
    tipo_no inicio;
    tipo_no fim;
}aresta;
aresta *aresta_cria(tipo_no inicio, tipo_no fim);

#endif