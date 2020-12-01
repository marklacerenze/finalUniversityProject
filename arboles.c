#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Arboles.h"
#include "consumos.h"
#include "hijas.h"

#define AR_CONSUMOS "consumos.dat"
#define AR_CLIENTES "clientes.dat"


nodoArbol * inicArbol() {
    return NULL;
}

nodoArbol * crearNodoArbol(stCliente cliente) {
    nodoArbol*aux = (nodoArbol*) malloc(sizeof(nodoArbol));
    aux->dato = cliente;
    aux->consumos = inicLista();

    aux->izq = NULL;
    aux->der = NULL;
    return aux;
}

nodoArbol * insertarNodoArbol(nodoArbol*arbol, stCliente cliente)
{
    if(!arbol) {
        arbol=crearNodoArbol(cliente);
    }
    else {
        if(cliente.nroCliente > arbol->dato.nroCliente) {
            arbol->der = insertarNodoArbol(arbol->der, cliente);
        }
        else {
            arbol->izq = insertarNodoArbol(arbol->izq, cliente);
        }
    }
    return arbol;
}

void subMenuMostrarArbol(nodoArbol* arbol)
{
    system("cls");
    printf("\t\t\t*** MOSTRAR ARBOL ***\t\t\t");
    printf("\n\n\n");
    printf("\n\t 1) Mostrar en -PreOrder- \n\t");
    printf("\n\t 2) Mostrar en -InOrder- \n\t");
    printf("\n\t 3) Mostrar en -PosOrder- \n\t");
    printf("\n\n\t");
    printf("\n |ESC| para -FINALIZAR-  \n\t");

    int opt=47;
    do
    {
        scanf("%d", &opt);

        switch(opt) {
            {
            case 1:
                mostrarPreOrder(arbol);
                system("pause");
                break;
            case 2:
                mostrarInOrder(arbol);
                system("pause");
                break;
            case 3:
                mostrarPosOrder(arbol);
                system("pause");
            }
        }
        menuArbol(arbol);
    }
    while(opt != 0);
}

void mostrarNodoArbol(nodoArbol* nodo) {
    if(nodo) {
        muestraUnCliente(nodo->dato);
        muestraLista(nodo->consumos);
    }
}

void mostrarPreOrder(nodoArbol*arbol)
{
    if (arbol!=NULL)
    {
        muestraUnCliente(arbol->dato);
        mostrarPreOrder(arbol->izq);
        mostrarPreOrder(arbol->der);
    }
}

void mostrarInOrder(nodoArbol*arbol)
{
    if (arbol!=NULL)
    {
        mostrarInOrder(arbol->izq);
        muestraUnCliente(arbol->dato);
        mostrarInOrder(arbol->der);
    }
}
void mostrarPosOrder(nodoArbol*arbol)
{
    if (arbol!=NULL)
    {
        mostrarPosOrder(arbol->izq);
        mostrarPosOrder(arbol->der);
        muestraUnCliente(arbol->dato);
    }
}

nodoArbol * cliente2Arbol(nodoArbol* arbol) {
    FILE * archi = fopen(AR_CLIENTES, "rb");
    nodoArbol * aux = arbol;
    stCliente c;
    if(archi) {
        while(fread(&c, sizeof(stCliente), 1, archi) > 0) {
            aux = insertarNodoArbol(aux, c);
        }
        fclose(archi);
    }
    return aux;
}

nodoArbol * asignaConsumosArbol(nodoArbol * arbol) {
    FILE * consumos = fopen(AR_CONSUMOS, "rb");

    nodoArbol * aux = NULL;
    stConsumos c;

    if(consumos) {
        while(fread(&c,sizeof(stConsumos),1,consumos)>0) {
            aux = buscaClienteArbol(arbol, c.idCliente);
            if(aux) {
                aux->consumos = agregarAlFinal(aux->consumos, crearNodo(c));
            }
        }
        fclose(consumos);
    }
    return arbol;
}

nodoArbol * buscaClienteArbol(nodoArbol * arbol, int nroCliente) {

    nodoArbol * buscado = inicArbol();
    if(arbol) {
        if(arbol->dato.nroCliente == nroCliente) {
            buscado = arbol;
        }
        else {
            buscado = buscaClienteArbol(arbol->izq, nroCliente);
            buscado = buscaClienteArbol(arbol->der, nroCliente);
        }
    }

    return buscado;
}

nodoArbol* liquidaConsumos(nodoArbol * arbol, int nroCliente) {

    nodoArbol * aux;
    int anio;
    int mes;
    int total;
    if(arbol) {
        aux = buscaClienteArbol(arbol, nroCliente);
        if(aux) {
            printf("\nIngrese el anio: ");
            scanf("%d",&anio);
            printf("\nIngrese el mes: ");
            scanf("%d",&mes);

            total = cuentaTotal(aux->consumos, anio, mes);
            if (total > 0) {
                generarFactura(aux->dato, total, anio, mes);
                printf("\n Operacion realizada con exito.");
            }
            else {
                printf("\nNo existe un consumo registrado en esa fecha.");
            }
        }
        else {
            printf("\nEl dni no se encuentra registrado.");
        }
    }

    return arbol;
}

int cuentaTotal(nodoLista * lista, int anio, int mes) {
    nodoLista * seg = lista;
    int mbTotal;

    if(seg){
        while(seg){
            if(seg->dato.anio == anio && seg->dato.mes == mes){
                mbTotal = mbTotal + seg->dato.datosConsumidos;
            }
            seg = seg->sig;
        }
    }
    return mbTotal;
}

void generarFactura(stCliente cliente, int total,int anio, int mes) {
    printf("\n*************************************************************");
    printf("\n* Apellido     : %s", cliente.apellido);
    printf("\n* Nombre       : %s", cliente.nombre);
    printf("\n* Nro. Cliente.: %d", cliente.nroCliente);
    printf("\n* DNI          : %d", cliente.dni);
    printf("\n* Correo       : %s", cliente.email);
    printf("\n* Domicilio    : %s", cliente.domicilio);
    printf("\n* Nro. Movil   : %d", cliente.movil);
    printf("\n\n-----Factura------\n");
    printf("\n* Mes          : %d", mes);
    printf("\n* Anio         : %d", anio);
    printf("\n* Total de mb  : %d\n\n", total);
    printf("\n* TOTAL: $%d", total);
    printf("\n*************************************************************");
}

nodoArbol* borrarNodo(nodoArbol * arbol, int dato) {///por numero de nroCliente
    if(arbol) {
        if(dato < arbol->dato.nroCliente) {///si el dato a borrar es menor al dato actual del arbol
            arbol->izq = borrarNodo(arbol->izq, dato);///avanzo por la izquierda
        }
        else if(dato >  arbol->dato.nroCliente) { ///si el dato a borrar es mayor al dato actual del arbol
            arbol->der = borrarNodo(arbol->der, dato);///avanzo por la derecha
        }
        else { ///aca solo accede cuando lo encuentra
            if(!arbol->izq && !arbol->der) {///si los siguientes nodos del arbol actual son NULL:
                free(arbol);///libera el nodo de una, ya que al ser terminal no hace falta mover nada.
                arbol=NULL;
            }
            else if(!arbol->izq) { ///si el nodo actual no posee otros nodos a la izq:
                nodoArbol* aux= arbol;///guarda el nodo actual en un auxiliar
                arbol=arbol->der;///sobreescribe  el nodo actual con el nodo siguiente que si tiene (recordar que no tiene nodos a la izq)
                free(aux);///libera el espacio de memoria de aux
            }
            else if(!arbol->der) { ///si el nodo actual no posee otros nodos a la der:
                nodoArbol* aux= arbol;
                arbol=arbol->izq;///sobreescribe  el nodo actual con el nodo siguiente que si tiene (recordar que no tiene nodos a la der)
                borrarListaEntera(aux->consumos);
                free(aux);
            }
            else {
                nodoArbol* aux= arbol;///guarda el menor de los 2 nodos que le sigue al actual en una variable aux
                arbol->dato=aux->dato;///guarda el dato actual del nodo en el aux
                arbol->der = borrarNodo(arbol->der, aux->dato.nroCliente);///borra el dato auxiliar desde el nodo de la derecha.
            }
        }
    }
    return arbol;
}

void borrarListaEntera(nodoLista * lista) {
    nodoLista * proximo;
    nodoLista * seg;
    seg = lista;
    while(seg != NULL) {
        proximo = seg->sig;
        free(seg);
        seg = proximo;
    }
}
