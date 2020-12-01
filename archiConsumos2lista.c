#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "archiConsumos2Lista.h"
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
    nuevo-> sig = NULL ;

return nuevo;
}
///////////////////////////////////////////////////////////////////

/// Parametros: lista de origen y nodo a agregar al principio --> retorna la lista
nodoLista * agregarAlPrincipio (nodoLista * lista, nodoLista * nuevoNodo)
{
    if (lista == NULL ) {
        lista = nuevoNodo; } else { nuevoNodo-> sig = lista;
                                    lista = nuevoNodo; }
return lista;
}

////////////////////////////////////////////////////////////////////////////////////

/// Parametro nodo consumo a mostrar
void  muestraNodo (nodoLista *lista)
{
    muestraUnConsumo(lista->dato);
}
/////////////////////////////////////////////////////////////////////////////////////


/// Parametro lista consumos a mostrar
void  muestraLista (nodoLista * lista)
{
    nodoLista *seg = lista;
    while (seg) {
        muestraNodo (seg);
        seg = seg-> sig ;}
        system("pause");
}
///////////////////////////////////////////////////

/// Parametro lista a cargar con los CONSUMOS del propio archivo ORDENADOS por FECHA -> la retorna
nodoLista * agregarOrdenFecha (nodoLista * lista)
{
stConsumos con [100];
stConsumos c;
stConsumos aux;
int vConsumos = 0;
int dimen = 100;

       FILE *archivo = fopen(AR_CONSUMOS, "rb");

        if(cantidadConsumos() == 0)
    {
        printf("\n NO HAY CONSUMOS \n");
    }

    if (archivo){

     while (fread(&c,sizeof(stConsumos),1,archivo)> 0 && vConsumos<dimen){
                      con [vConsumos] = c;}
                      vConsumos++;}
        fclose (archivo);


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
                    lista = crearNodo(con[k]);}

return lista;
}
