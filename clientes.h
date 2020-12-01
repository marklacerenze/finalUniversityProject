#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include <time.h>

typedef struct
{
    int  id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    int dni;
    char email[30];
    char domicilio[45];
    long int movil; //lo ncesito como long o no funciona con codigo d caracteristica - UPDATE: IGUAL NO FUNCIONO
    int baja;/// 0 si está activo - 1 si está eliminado
} stCliente;


void cicloCargaCliente();
void muestraUnCliente(stCliente cliente);
stCliente buscaCliente(int dni);
int existeCliente(int dni);

#endif // CLIENTES_H_INCLUDED
