# finalUniversityProject

Creamos un sistema que pueda lograr el manejo dinámico de la información y lograr la persistencia de la información a partir de archivos binarios.

Se crearon dos archivos, uno de Clientes con, por lo menos, 50 clientes ya cargados, y otro de Consumos, con, no menos de 30 consumos por cliente.

Creando estos dos CRUD de clientes y consumos por cliente, recorrimos el archivo de consumos, y por cada consumo leido buscamos el cliente al cual le pertenece el mismo. Al tener estas dos variables (consumo, cliente), buscamos en el arbol el cliente, si el cliente no existe, creamos un nodo arbol, agregamos el dato cliente, inicializamos la lista y agregamos en ella el consumo.
