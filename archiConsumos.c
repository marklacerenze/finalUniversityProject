#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "clientes.h"
#include "consumos.h"
#include "archiConsumos.h"
#include "archiClientes.h"
#include "hijas.h"

#define AR_CONSUMOS "consumos.dat"
#define AR_CLIENTES "clientes.dat"

void bajaConsumo()
{
    system("cls");

    stConsumos consumo;
    FILE * archivo = fopen (AR_CONSUMOS, "r + b");
    if(cantidadConsumos() == 0)
    {
        printf("\n NO HAY CONSUMOS\n"); }

    if (archivo)
    {
        int id=0;
        int flag=0;
        printf ("Ingrese ID del consumo: \n");
        scanf("%d", &id);
        flag=comprueba(AR_CONSUMOS, id);

    if (flag==0){ printf("\n |INEXISTENTE| \n");} else{

        fseek (archivo, (id-1) * sizeof (stConsumos), SEEK_SET);
        fread(&consumo, sizeof(stConsumos), 1, archivo);
        muestraUnConsumo(consumo);

        if(consumo.baja == 0)
        {
            printf("\n Esta seguro que quiere dar de baja el consumo?\n");
        }
        else
        {
            printf("\n Esta seguro que quiere dar de alta el consumo?\n");
        }

        if(cajaDeTexto("ERROR") == 2)
        {
            printf("\n No se ha modificado el consumo. \n");
            system("pause");
            dPrincipal();
        }
        else
        {
            if(consumo.baja == 0)
            {
                consumo.baja = 1;
            }
            else
            {
                consumo.baja = 0;
            }
        }

        //ARCHIVOS
        fseek(archivo, (-1)*sizeof(consumo), SEEK_CUR);
        fwrite(&consumo, sizeof(consumo), 1, archivo);
        fclose (archivo);

        system("cls");

        if(consumo.baja == 0)
        {
            printf("\n EL CONSUMO PASA A ESTAR DE ALTA\n");
        }
        else
        {
            printf("\n EL CONSUMO PASA A ESTAR DE BAJA\n");
        }}}
        system("pause");

}
////////////////////////////////////////////////////////

void buscarConsumoPorFecha()
{
    if(cantidadConsumos() == 0)
    {
        printf("\n NO HAY CONSUMOS \n");
    }

    stConsumos consumo;
    stConsumos aux;
    FILE *archivo = fopen(AR_CONSUMOS, "rb");

    if (archivo){
        system("cls");

        printf(" \n |FECHA| \n");
        printf("\n Ingrese mes:\n");
        aux.mes = validarFecha(12);
        printf("\n Ingrese dia:\n");
        aux.dia = validarFecha(maximoDiaDelMes(consumo.mes));
        printf("\n Ingrese anio:\n");
        aux.anio = validarFecha(2020);

        while (fread(&consumo, sizeof(stConsumos),1, archivo) > 0) {
            if(consumo.dia == aux.dia && consumo.mes == aux.mes && consumo.anio == aux.anio)
            {
                printf("\nSe ha encontrado el/los siguentes consumos:\n");
                muestraUnConsumo(consumo);
            }
        }
        fclose(archivo);
    }

    system("pause");
     dPrincipal();
}
//////////////////////////////////////////////////////////////////////////////////////////////

int cantidadConsumos()
{
    int c = 0;
    stConsumos consumos;
    FILE *archivo = fopen(AR_CONSUMOS, "rb");
    if(archivo != NULL)
    {
        while (fread(&consumos, sizeof(consumos), 1, archivo) > 0)
        {
            c++;
        }
        fclose(archivo);
    }

    return c;
}
//////////////////////////////////////////////////////////////

void modificarConsumo()
{
    system("cls");

    FILE * archivo = fopen (AR_CONSUMOS, "r + b");

    if(!archivo){
        printf("\n NO HAY CONSUMOS \n");
    }
    else {
        stConsumos aux;
        int id=0;
        int flag=0;
        printf("\n Ingrese |ID CONSUMO| \n");
        scanf("%d", &id);
        flag=comprueba(AR_CONSUMOS,id); // modularizado

        if(flag==0){
            printf("\n |INEXISTENTE| \n");
        }
        else {
            fseek (archivo, (id-1) * sizeof (stConsumos), SEEK_SET);
            fread(&aux, sizeof(stConsumos), 1, archivo);

            int opt;
            int parar = 0;
            while ((opt < 5 || opt > 0) && parar != 1)
            {
                system("cls");
                muestraUnConsumo(aux);
                printf("\n\t Que parte desea modificar? \n");
                menuModificarConsumoDisplay ();
                scanf("%d", &opt);
                switch(opt)
                {
                case 1:
                    printf("Ingrese a%co:\n", 165);
                    aux.anio = validarFecha(2020);
                    break;
                case 2:
                    printf("Ingrese mes:\n");
                    aux.mes = validarFecha(12);
                    break;
                case 3:
                    printf("Ingrese dia:\n");
                    aux.dia = validarFecha(maximoDiaDelMes(aux.mes));
                    break;
                case 4:
                    printf("Ingrese nuevos datos consumidos (%d mb):\n", aux.datosConsumidos);
                    int suma = 0;
                    scanf("%d", &suma);
                    aux.datosConsumidos = aux.datosConsumidos + suma;
                    break;
                case 5:
                    printf("Ingrese datos consumidos (%d mb):\n", aux.datosConsumidos);
                    scanf("%d", &aux.datosConsumidos);
                }

                system("cls");
                muestraUnConsumo(aux);
                printf("\n\t ########################### \n\t");
                printf("\n Quiere continuar modificando?\n");
                if(cajaDeTexto("Ingrese una opcion valida") == 2) {
                    parar = 1;
                }
            }

            //ARCHIVOS
            fseek(archivo, (-1)*sizeof(stConsumos), SEEK_CUR);
            fwrite(&aux, sizeof(stConsumos), 1, archivo);
            fclose (archivo);

            system("cls");
            printf("\nSe ha modificado el consumo correctamente.\n");
            }
        }
        system("pause");
}
//////////////////////////////////////////////////////////////////

int comprueba(char archivo[], int dato)
{
  int flag=0;
    stConsumos aux;
    FILE *archi = fopen(AR_CONSUMOS,"rb");
    if(archi)
    {
        while(fread(&aux,sizeof(stConsumos),1,archi)>0 && flag==0)
        {
            if(aux.id == dato)
            {
                flag=1;
                printf("\n -CONSUMO EXISTENTE- \n");
            }
            else
            {
                flag=0;
            }
        }
        fclose(archi);
    }
    return flag;
}
///////////////////////////////////////////////////////////////////////7

void listarConsumos()
{
    FILE *archivo = fopen(AR_CONSUMOS, "rb");

    if(cantidadConsumos() == 0)
    {
        printf("\n NO HAY CONSUMOS \n");
    }
    else
    {

        stConsumos consumo;
        fseek(archivo,0,SEEK_SET);
        while (fread(&consumo, sizeof(stConsumos), 1, archivo) > 0)
        {
            muestraUnConsumo(consumo);
        }
    }

    fclose(archivo);
    system("pause");
}
//////////////////////////////////////////////////

void menuModificarConsumoDisplay()
{
    printf("\n 1) A%cO \n", 165);
    printf("\n 2) MES \n");
    printf("\n 3) DIA \n");
    printf("\n 4) SUMAR DATOS CONSUMIDOS \n");
    printf("\n 5) AJUSTAR DATOS CONSUMIDOS \n");
    printf("\n |0| SALIR \n");
}




