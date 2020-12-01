#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "archiClientes.h"
#include "clientes.h"
#include "hijas.h"

#define AR_CLIENTES "clientes.dat"
#define AR_CLI_ACTIVOS "clientesa.dat"
#define AR_CLI_BAJA "clientesb.dat"


void bajaCliente()
{
    system("cls");

    stCliente cliente;
    FILE * archivo = fopen (AR_CLIENTES, "r + b");
    if(cantidadClientes() == 0)
    {
        printf("\n NO HAY CLIENTES\n");

    }

    if (archivo){
        int id=0;
        int flag=0;
        printf("\n Ingrese ID Cliente \n");
        scanf("%d", &id);

        flag= compruebaIDC(AR_CLIENTES, id);

        if (flag == 0){
            printf("\n |INEXISTENTE| \n");
        } else {
            fseek (archivo, (id-1) * sizeof (stCliente), SEEK_SET);
            fread(&cliente, sizeof(stCliente), 1, archivo);
            muestraUnCliente(cliente);

            cliente.baja == 0 ? printf("\n Esta seguro que quiere dar de BAJA el cliente? \n") : printf("\n Esta seguro que quiere dar de ALTA el cliente? \n");

            if(cajaDeTexto("\n ERROR \n") == 2)
            {
                printf("\n No se ha modificado el cliente. \n");
                system("pause");
                dPrincipal();
            }
            else
            {
                if(cliente.baja == 0)
                {
                    cliente.baja = 1;
                }
                else
                {
                    cliente.baja = 0;
                }
            }

            //ARCHIVOS
            fseek(archivo, (-1)*sizeof(stCliente), SEEK_CUR);
            fwrite(&cliente, sizeof(stCliente), 1, archivo);
            fclose(archivo);

            system("cls");

            cliente.baja == 0 ? printf("\nEL CLIENTE PASA A ESTAR DE ALTA \n") : printf("\nEL CLIENTE PASA A ESTAR DE BAJA\n");
        }
    }
    system("pause");
}
////////////////////////////////////////////////////////////////

int compruebaIDC(char archivo[], int dato)
{
    int flag=0;
    stCliente aux;
    FILE *archi = fopen(AR_CLIENTES,"rb");
    if(archi)
    {
        while(fread(&aux,sizeof(stCliente),1,archi)>0 && flag==0)
        {
            if(aux.id == dato)
            {
                flag=1;
                printf("\n -CLIENTE |EXISTENTE|- \n");
            }
            else
            {
                flag=0;
            }
        }
        fclose(archi);}

    return flag;
}
/////////////////////////////////////////////////////////////////////////

int cantidadClientes()
{
    int id = 0;
    stCliente clientes;
    FILE *archivo = fopen(AR_CLIENTES, "rb");
    if(archivo != NULL)
    {
        while (fread(&clientes, sizeof(clientes), 1, archivo) > 0)
        {
            id++;
        }
        fclose(archivo);
    }

    return id;
}
//////////////////////////

void reparteAeI()
{
stCliente c;
    FILE *clientes = fopen (AR_CLIENTES, "rb" );
    FILE *ClientesActivos = fopen (AR_CLI_ACTIVOS, "wb" );
    FILE *ClientesBaja = fopen (AR_CLI_BAJA,  "wb" );

    if (clientes) {
        while ( fread (&c, sizeof (stCliente), 1 , clientes)> 0 ) {
            if (c.baja == 0) {
                fwrite (&c, sizeof (stCliente), 1 , ClientesActivos);
            }
            else {
                fwrite (&c, sizeof (stCliente), 1 , ClientesBaja);
            }
        }
        fclose (clientes);
        fclose (ClientesActivos);
        fclose (ClientesBaja);
    }
}
///////////////////////////////////////////////////////////////////////

void listarClientesActivos()
{
    FILE *archivo = fopen(AR_CLI_ACTIVOS, "rb");

    if(cantidadClientes() == 0)
    {
        printf("\n NO HAY CLIENTES \n");
    }

    if(archivo){

        stCliente c;

        fseek(archivo, 0, SEEK_SET);
        while (fread(&c, sizeof(stCliente), 1, archivo) > 0){
            muestraUnCliente(c);
        }
        fclose(archivo);
    }
    system("pause");
}
////////////////////////////////////////////////////////////////////////////////////

void listarClientesInactivos()
{

    FILE *archivo = fopen(AR_CLI_BAJA, "rb");

    if(cantidadClientes() == 0)
    {
        printf("\n NO HAY CLIENTES \n");
    }

if(archivo){
    stCliente c;
    fseek(archivo, 0, SEEK_SET);

    while (fread(&c, sizeof(stCliente), 1, archivo) > 0){
        muestraUnCliente(c);
    }
}
else
{
    printf("\n NO HAY CLIENTES INACTIVOS \n");
}
fclose(archivo);
system("pause");


}
////////////////////////////////////////////////////////////////////////////////////////////

void modificarCliente()
{
    system("cls");
    int nroaux = 0;
    long int movilaux = 0;
    long int dniaux = 0;

    stCliente superCliente;
    FILE * archivo = fopen (AR_CLIENTES, "r + b");

    if(cantidadClientes() == 0)
    {
        printf("\n NO HAY CLIENTES \n");
    }

    if (archivo)
    {
        int id=0;
        int flag=0;
        printf ("Ingrese |ID CLIENTE| \n");
        scanf("%d",&id);
        flag=compruebaIDC(AR_CLIENTES, id);
        if (flag == 0){
        printf("\n |INEXISTENTE| \n");
        } else {
            fseek (archivo, (id - 1) * sizeof (stCliente), SEEK_SET);
            fread(&superCliente, sizeof(stCliente), 1, archivo);

            int opt;
            int parar = 0;
            int flag=0;
            while ((opt < 7 || opt > 0) && parar != 1)
            {
                system("cls");
                muestraUnCliente(superCliente);
                printf("\t\t\t\t");
                printf("\n\t Que parte desea modificar? \n");
                menuModificarClienteDisplay();
                scanf("%d", &opt);
                switch(opt)
                {
                ///#### NRO CLIENTE #####
                case 1:
                        printf("\n Ingrese el numero del cliente: ");
                        fflush(stdin);
                        scanf("%d", &superCliente.nroCliente);
                        nroaux=superCliente.nroCliente;
                        flag=idRepetido(AR_CLIENTES,nroaux); // modularizado
                        if(flag==1)
                        {
                            printf("\n\tYa existe un usuario registrado con el numero %d ",nroaux);
                            menuModificarClienteDisplay();
                        }
                    break;
                case 2:
                    system("cls");
                    printf("\nIngrese el DNI:\n ");
                    scanf("%lu",&dniaux);
                    superCliente.dni=datoInvalido(dniaux, 2);
                    break;
                case 3:
                    system("cls");
                    printf("\nIngrese el telefono movil:\n ");
                    scanf("%lu", &movilaux);
                    superCliente.movil=datoInvalido(movilaux, 1); //verifica el correcto tipeo
                    break;
                case 4:
                    system("cls");
                    printf("\nIngrese el nombre: \n");
                    scanf("%s", superCliente.nombre);
                    break;
                case 5:system("cls");
                    printf("\nIngrese el apellido: \n");
                    scanf("%s", superCliente.apellido);
                    break;
                case 6: system("cls");
                    printf("\nIngrese el correo electronico: \n");
                    scanf("%s", superCliente.email);
                    break;
                case 7: system("cls");
                    printf("\nIngrese el domicilio: \n");
                    scanf("%s",superCliente.domicilio);
                    break;
                }

                system("cls");
                muestraUnCliente(superCliente);
                printf("\n\t\t ###################################\n\t\t");
                printf("Quiere continuar modificando?\n");
                if(cajaDeTexto("Ingrese una opcion valida") == 2)
                {
                    parar = 1;
                }
            }

        //ARCHIVOS
        fseek(archivo, (-1)*sizeof(superCliente), SEEK_CUR);
        fwrite(&superCliente, sizeof(superCliente), 1, archivo);
        fclose (archivo);
        system("cls");
        printf("\nSe ha modificado el cliente correctamente.\n");
        }
    }
        system("pause");

}
////////////////////////////////////////////////////////////////////

void menuModificarClienteDisplay()
{
    printf("\n 1) NUMERO CLIENTE \n");
    printf("\n 2) DNI \n");
    printf("\n 3) TELEFONO MOVIL \n");
    printf("\n 4) NOMBRE \n");
    printf("\n 5) APELLIDO \n");
    printf("\n 6) CORREO ELECTRONICO \n");
    printf("\n 7) DOMICILIO \n");
    printf("\n |0| SALIR \n");
}
