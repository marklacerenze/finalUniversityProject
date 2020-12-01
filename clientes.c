#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "clientes.h"
#include "archiClientes.h"
#include "arboles.h"
#include "hijas.h"

#define AR_CLIENTES "clientes.dat"
#define AR_CONSUMOS "consumos.dat"


void cicloCargaCliente(nodoArbol * arbol)
{
    long int dniaux=0;
    long int movilaux=0;
    int nroaux=0;
    int flag=0;
    stCliente cliente;

    //ID AUTOINCREMENTAL
    system("cls");
    cliente.id=cantidadClientes()+1;
    printf("\n\t REGISTRO ID: %d \n",cliente.id);
    ///### ID ELEGIDO ####
    do  //Lo hace hasta que no tire un id repetido
    {
        printf("\n CODIGO NUMERICO -NroCliente-: \n ");
        scanf("%d", &cliente.nroCliente);
        nroaux = cliente.nroCliente;
        flag=idRepetido(AR_CLIENTES,nroaux); // modularizado
        if(flag==1)
        {
            printf("\n\tYa existe un usuario registrado con el numero %d ",nroaux);
        }
    }
    while(flag==1);

    ///### NOMBRE Y APELLIDO ####
    printf("\nNOMBRE:\n ");
    scanf("%s",cliente.nombre);
    fflush(stdin);
    printf("\nAPELLIDO:\n ");
    scanf("%s",cliente.apellido);
    fflush(stdin);

    ///#### ##### #####

    ///### CORREO ELECTRONICO ####
    printf("\nCORREO ELECTRONICO:\n ");
    fflush(stdin);
    scanf("%s",cliente.email);
    ///#### ##### #####

    ///### DOMICILIO ####
    printf("\nDOMICILIO:\n ");
    fflush(stdin);
    gets(cliente.domicilio);
    ///#### ##### #####

    ///#### DNI #####
    printf("\nDNI:\n ");
    scanf("%lu",&dniaux);
    cliente.dni=datoInvalido(dniaux, 2);
    ///#### ##### #####

    ///#### TELEFONO #####
    printf("\nTELEFONO MOVIL:\n ");
    scanf("%lu", &movilaux);
    cliente.movil=datoInvalido(movilaux, 1); //verifica el correcto tipeo
    ///#### ##### #####

    ///### ID AUTOINCREMENTAL ###
    cliente.baja = 0;// automaticamente en alta
    printf("\nCONFIMAR CARGA O CANCELAR?:\n ");
    if(cajaDeTexto("Valor invalido.") == 2)
    {
        dPrincipal();
    }


    ///####### GUARDADO ARCHIVO######################
    FILE* archivo;
    archivo = fopen(AR_CLIENTES, "ab");

    fwrite(&cliente, sizeof(stCliente), 1, archivo);
    fclose(archivo);

    ///############################################
    printf("\n");
    system("pause");

}
////////////////////////////////////////////////////////////////

int existeCliente(int dni) {
    stCliente cliente;
    FILE * archi = fopen(AR_CLIENTES, "rb");
    int flag = 0;
    if(archi) {
        while(fread(&cliente, sizeof(stCliente), 1, archi)) {
            if(cliente.dni == dni) {
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

////////////////////////////////////////////////////////////////

void muestraUnCliente(stCliente cliente)
{
    printf("\n-------------------------------- \n");
    printf("\n ID CLIENTE: %d", cliente.id);
    printf("\n NRO CLIENTE: %d", cliente.nroCliente);
    printf("\n NOMBRE:  %s",cliente.nombre);
    printf("\n APELLIDO: %s", cliente.apellido);
    printf("\n DNI: %d", cliente.dni);
    printf("\n E-MAIL: %s",cliente.email);
    printf("\n DOMICILIO: %s",cliente.domicilio);
    printf("\n MOVIL: %lu",cliente.movil);

    if(cliente.baja == 1) {
        printf("\n ESTADO: |inactivo| \n");
    }
    else {
        printf("\n ESTADO: |activo| \n");
    }
    printf("\n################################# \n");
}

////////////////////////////////////////////////////////////////

stCliente buscaCliente(int dni)
{
    stCliente cliente;
    int flag =0;
    FILE * archi = fopen(AR_CLIENTES,"rb");
    if(archi)
    {
        while(flag==0 && fread(&cliente,sizeof(stCliente), 1, archi) > 0)
        {
            if(cliente.dni == dni)
            {
                flag = 1;
            }
        }
        fclose(archi);
    }
    if (flag == 0) {
        cliente.baja = -1;
    }

    return cliente;
}
















