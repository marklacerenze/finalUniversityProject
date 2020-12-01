#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include "clientes.h"
#include "consumos.h"
#include "lista.h"

typedef struct _nodoArbol{
stCliente dato;
nodoLista* consumos;
struct _nodoArbol* izq;
struct _nodoArbol* der;
}nodoArbol;

nodoArbol*inicArbol();
nodoArbol*crearNodoArbol(stCliente cliente);
nodoArbol * insertarNodoArbol(nodoArbol*arbol, stCliente cliente);
void subMenuMostrarArbol(nodoArbol* arbol);
void mostrarNodoArbol(nodoArbol* nodo);
void mostrarPreOrder(nodoArbol*arbol);
void mostrarInOrder(nodoArbol*arbol);
void mostrarPosOrder(nodoArbol*arbol);
nodoArbol * cliente2Arbol(nodoArbol* arbol);
nodoArbol * asignaConsumosArbol(nodoArbol * arbol);
nodoArbol * buscaClienteArbol(nodoArbol * arbol, int nroCliente);
nodoArbol* liquidaConsumos(nodoArbol * arbol, int nroCliente);
int cuentaTotal(nodoLista * lista, int anio, int mes);
void generarFactura(stCliente cliente, int total,int anio, int mes);
nodoArbol* borrarNodo(nodoArbol * arbol, int dato);
void borrarListaEntera(nodoLista * lista);

#endif // ARBOLES_H_INCLUDED
