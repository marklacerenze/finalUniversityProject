#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "arch2lista.h"
#include "archiConsumos.h"

#define AR_CONSUMOS "consumos.dat"

/// Inicializa una lista en NULL
nodoLista * inicLista ()
{
 return  NULL ;
}
////////////////////////////////////////

/// Crea un nodo de tipo stConsumos (parametro) y lo retorna
nodoLista * crearNodo (stConsumos datos)
{
    nodoLista * nuevo = (nodoLista*) malloc ( sizeof (nodoLista));
    nuevo->dato = datos;
    nuevo-> siguiente = NULL ;

return nuevo;
}
///////////////////////////////////////////////////////////////////

/// Parametros: lista de origen y nodo a agregar al principio --> retorna la lista
nodoLista * agregarAlPrincipio (nodoLista * lista, nodoLista * nuevoNodo)
{
    if (lista == NULL ) {
        lista = nuevoNodo; } else { nuevoNodo-> siguiente = lista;
                                    lista = nuevoNodo; }
return lista;
}

////////////////////////////////////////////////////////////////////////////////////

/// Parametro nodo consumo a mostrar
void  muestraNodo (nodoLista *lista)
{
    printf ( " \n nodo: %p - nodo-> siguiente: %p " , lista, lista->siguiente );
    muestraNodo(lista->dato);
}
/////////////////////////////////////////////////////////////////////////////////////


/// Parametro lista consumos a mostrar
void  muestraLista (nodoLista * lista)
{
    nodo * seg = lista;
    while (seg) {
        muestraNodo() (seg);
        seg = seg-> siguiente ;}
}
///////////////////////////////////////////////////

/// Parametro lista a cargar con los CONSUMOS del propio archivo ORDENADOS por FECHA -> la retorna
nodoLista * agregarOrdenFecha (nodoLista * lista)
{
stConsumos con [1000];
stConsumos c;
stConsumos aux;
int vConsumos = 0;
int dimen = 1000;

       FILE *archivo = fopen(AR_CONSUMOS, "rb");

     while (fread(&c,sizeof(stConsumos),1,archivo)> 0 && vConsumos<dimen){
                      con [vConsumos] = c;
                      vConsumos++; }

    /// Ordenación por año.
    for(int i = 0; i < vConsumos; i++)
    {
        for(int j = i+1; j < vConsumos; j++)
        {
            if(con[i].anio > con[j].anio)
            {
                aux = con[i];
                con[i] = con[j];
                con[j] = aux; }}}

    /// Ordenación por mes
    for(int i = 0; i < vConsumos; i++)
    {
        for(int j = i+1; j < vConsumos; j++)
        {
            if(con[i].anio == con[j].anio && con[i].mes > con[j].mes)
            {
                aux = con[i];
                con[i] = con[j];
                con[j] = aux; }}}

    /// Ordenación por día
    for(int i = 0; i < vConsumos; i++)
    {
        for(int j = i+1; j < vConsumos; j++)
        {
            if(con[i].anio == con[j].anio && con[i].mes == con[j].mes && con[i].dia > con[j].dia)
            {
                aux = con[i];
                con[i] = con[j];
                con[j] = aux; }}}

                for (int k=0; k<vConsumos; k++){
                    lista = con[k];
                    k++;}
}
