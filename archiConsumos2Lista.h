#ifndef ARCH2LISTA_H_INCLUDED
#define ARCH2LISTA_H_INCLUDED

#include "consumos.h"

typedef struct _nodoLista{
stConsumos dato;
struct _nodoLista* sig;
}nodoLista;

nodoLista * inicLista ();
nodoLista * crearNodo (stConsumos dato);
nodoLista * agregarAlPrincipio (nodoLista *lista, nodoLista *nuevoNodo);
void  muestraNodo (nodoLista *lista);
void  muestraLista(nodoLista *lista);
nodoLista * agregarOrdenFecha (nodoLista * lista);


#endif // ARCH2LISTA_H_INCLUDED
