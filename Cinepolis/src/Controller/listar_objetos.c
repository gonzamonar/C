
#include "listar_objetos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DataBase/database.h"
#include "../View/user_interface.h"


static int dbCallback_listarPeliculas(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarFuncionesDePeliculas(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarCast(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarClientes(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarComprasPorClientes(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarSalas(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarRecaudacionSalas(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarRecaudacionSalasPorFuncion(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarFunciones(void *unused, int argc, char **argv, char **colName);
static int dbCallback_listarTarifas(void *unused, int argc, char **argv, char **colName);

//Peliculas
void DB_listarPeliculas(void){
	char* sql_select = {"SELECT Peliculas.id, Peliculas.titulo, Peliculas.year, Peliculas.duracion, Directores.nombre FROM Peliculas INNER JOIN Directores ON Peliculas.id_director = Directores.id;"};
	printf("\n\n  %-4s | %-50s | %-4s | %-8s | %-20s \n", "Id", "Título", "Año", "Duración", "Director");
	printf("  --------------------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarPeliculas);
	pause();
}


static int dbCallback_listarPeliculas(void *unused, int argc, char **argv, char **colName){
	printf("  %-4s | %-50s | %-4s | %-8s | %-20s \n", argv[0], argv[1], argv[2], argv[3], argv[4]);
	return 0;
}

void DB_listarFuncionesDePeliculas(void){
	char* sql_select = {"SELECT Peliculas.id, Peliculas.titulo, Peliculas.year, (SELECT COUNT() FROM Funciones WHERE Funciones.id_pelicula = Peliculas.id)[Funciones] FROM Peliculas ORDER BY id;"};
	printf("\n\n  %-4s | %-50s | %-6s | %-8s \n", "", "", "", "Cantidad de");
		printf("  %-4s | %-50s | %-6s | %-8s \n", "Id", "Película", "Año", " Funciones");
	printf("  -----------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarFuncionesDePeliculas);
	pause();
}


static int dbCallback_listarFuncionesDePeliculas(void *unused, int argc, char **argv, char **colName){
	printf("  %-4s | %-50s | %-6s | %-8s \n", argv[0], argv[1], argv[2], argv[3]);
	return 0;
}


//Cast
void DB_listarCast(void){
	char* sql_select = {"SELECT Peliculas.titulo[Pelicula], (Actores.nombre ||' '|| Actores.apellido)[Actor] FROM Cast INNER JOIN Actores ON id_actor = Actores.id INNER JOIN Peliculas ON id_pelicula = Peliculas.id ORDER BY Peliculas.titulo ASC;"};
	printf("\n\n  %-50s | %-30s\n", "Película", "Actor/Actriz");
	printf("  ---------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarCast);
	pause();
}


static int dbCallback_listarCast(void *unused, int argc, char **argv, char **colName){
	printf("  %-50s | %-25s\n", argv[0], argv[1]);
	return 0;
}


//Clientes
void DB_listarClientes(void){
	char* sql_select = {"SELECT id, (nombre ||' '|| apellido)[Nombre], dni, (CASE WHEN socio = 1 THEN \"SÍ\" ELSE \"NO\" END)[Socio] FROM Clientes;"};
	printf("\n\n  %-4s | %-50s | %-14s | %-10s \n", "Id", "Nombre", "DNI", "Socio");
	printf("  ---------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarClientes);
}

void DB_listarCliente(int id){
	char sql_select[512];
	sprintf(sql_select, "SELECT id, (nombre ||' '|| apellido)[Nombre], dni, (CASE WHEN socio = 1 THEN \"SÍ\" ELSE \"NO\" END)[Socio] FROM Clientes WHERE id = %d;", id);
	printf("\n\n  %-4s | %-50s | %-14s | %-10s \n", "Id", "Nombre", "DNI", "Socio");
	printf("  ---------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarClientes);
}


static int dbCallback_listarClientes(void *unused, int argc, char **argv, char **colName){
	printf("  %-4s | %-50s | %-14s | %-10s \n", argv[0], argv[1], argv[2], argv[3]);
	return 0;
}


void DB_listarComprasPorCliente(void){
	char* sql_select = {"SELECT id, (nombre||' '||apellido)[Cliente],(SELECT COUNT(cantidad_entradas) FROM Compras WHERE id_cliente = Clientes.id)[Compras Realizadas], (SELECT SUM(cantidad_entradas) FROM Compras WHERE id_cliente = Clientes.id)[Entradas Compradas], (SELECT SUM(precio_total) FROM Compras WHERE id_cliente = Clientes.id)[Monto Total] FROM Clientes;"};
	printf("\n\n  %-4s | %-30s | %-12s | %-12s | %-10s\n", "", "", "Compras", "Entradas", "Monto");
		printf("  %-4s | %-30s | %-12s | %-12s | %-10s\n", "Id", "Cliente", "Realizadas", "Compradas", "Total");
	printf("  ---------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarComprasPorClientes);
	pause();
}


static int dbCallback_listarComprasPorClientes(void *unused, int argc, char **argv, char **colName){
	char entradas[12];
	char monto[10];
	(argv[3]==NULL) ? strcpy(entradas,"0") : strcpy(entradas,argv[3]) ;
	(argv[4]==NULL) ? strcpy(monto,"0") : strcpy(monto,argv[4]) ;

	printf("  %-4s | %-30s | %-12s | %-12s | %-10s\n", argv[0], argv[1], argv[2], entradas, monto);
	return 0;
}


//Salas
void DB_listarSalas(void){
	char* sql_select = {"SELECT id,tipo_sala,asientos_por_fila,cantidad_filas,(CASE WHEN tiene_pasillo_central = 1 THEN \"SÍ\" ELSE \"NO\" END)[Pasillo] FROM Salas;"};
	printf("\n\n  %-4s | %-10s | %-15s | %-15s | %-15s \n", "", " Tipo ", "Asientos", "Cantidad", "    Tiene    ");
		printf("  %-4s | %-10s | %-15s | %-15s | %-15s \n", "Id", "de Sala", "por Fila", "de Filas", "Pasillo Central");
	printf("  -------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarSalas);
	pause();
}


static int dbCallback_listarSalas(void *unused, int argc, char **argv, char **colName){
	printf("  %-4s | %-10s | %-15s | %-15s | %-15s \n", argv[0], argv[1], argv[2], argv[3], argv[4]);
	return 0;
}


void DB_listarRecaudacionSalas(void){
	char* sql_select = {"SELECT Salas.id[Sala], (SELECT SUM(Entradas.precio) FROM Entradas INNER JOIN Ubicaciones ON Entradas.id_ubicacion = Ubicaciones.id INNER JOIN Funciones ON Funciones.id = Ubicaciones.id_funcion WHERE Funciones.id_sala=Salas.id)[Recaudación] FROM Salas;"};
	printf("\n\n  %-10s | %-20s\n", "Sala", "Recaudación");
	printf("  -----------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarRecaudacionSalas);
	pause();
}


static int dbCallback_listarRecaudacionSalas(void *unused, int argc, char **argv, char **colName){
	char recaudacion[20];
	(argv[1]==NULL) ? strcpy(recaudacion,"0") : strcpy(recaudacion,argv[1]) ;

	printf("  %-10s | %20s\n", argv[0], recaudacion);
	return 0;
}


void DB_listarRecaudacionSalasPorFuncion(void){
	char* sql_select = {"SELECT Funciones.id_sala,Funciones.id,Peliculas.titulo,Funciones.fecha,Funciones.hora,(SELECT SUM(Entradas.precio) FROM Entradas INNER JOIN Ubicaciones ON Entradas.id_ubicacion = Ubicaciones.id WHERE Ubicaciones.id_funcion=Funciones.id)[Recaudación] FROM Funciones INNER JOIN Peliculas ON Funciones.id_pelicula = Peliculas.id ORDER BY Funciones.id_sala,Funciones.id;"};
	printf("\n\n  %-4s | %-4s | %-50s | %-10s | %-8s | %-10s\n", "Id", "Sala", "Película", "Fecha", "Hora", "Recaudación");
	printf("  ---------------------------------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarRecaudacionSalasPorFuncion);
	pause();
}


static int dbCallback_listarRecaudacionSalasPorFuncion(void *unused, int argc, char **argv, char **colName){
	char recaudacion[15];
	(argv[5]==NULL) ? strcpy(recaudacion,"0") : strcpy(recaudacion,argv[5]) ;
	printf("  %-4s | %-4s | %-50s | %-10s | %-8s | %15s\n", argv[0], argv[1], argv[2], argv[3], argv[4], recaudacion);
	return 0;
}



//Funciones

/*
void DB_listarFuncionesPorFecha(char* fecha){
	char sql_select[1024];
	sprintf(sql_select,"SELECT Funciones.id,Peliculas.titulo,id_sala,fecha,hora,(CASE WHEN subtitulada = 1 THEN \"SÍ\" ELSE \"NO\" END)[subtitulada] FROM Funciones INNER JOIN Peliculas ON Funciones.id_pelicula = Peliculas.id WHERE fecha = \"%s\" ORDER BY id_sala, hora;", fecha);
	printf("\n\n  %-4s | %-50s | %-6s | %-12s | %-10s | %-14s \n", "Id", "Película", "Sala", "Fecha", "Hora", "Subtitulada");
	printf("  ------------------------------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarFunciones);
	pause();
}


static int dbCallback_listarFunciones(void *unused, int argc, char **argv, char **colName){
	printf("  %-4s | %-50s | %-6s | %-12s | %-10s | %-14s \n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
	return 0;
}
*/

void DB_listarFunciones(void){
	char* sql_select = {"SELECT Funciones.id[ID Función], titulo[Película], Funciones.id_sala[Sala Nº], Funciones.fecha[Fecha], Funciones.hora[Hora], (CASE WHEN subtitulada = 1 THEN \"SÍ\" ELSE \"NO\" END)[subtitulada],(SELECT COUNT() FROM Ubicaciones WHERE disponible=1 AND id_funcion=Funciones.id)[Lugares Disponibles],(SELECT COUNT() FROM Ubicaciones WHERE id_funcion=Funciones.id)[Capacidad Total] FROM Funciones INNER JOIN Peliculas ON id_pelicula = Peliculas.id  ORDER BY SUBSTRING(fecha, 4, 2), SUBSTRING(fecha, 1, 2), hora;"};
	printf("\n\n  %-4s | %-50s | %-4s | %-10s | %-8s | %-12s | %s\n", "Id", "Película", "Sala", "Fecha", "Hora", "Subtitulada", "Disponibilidad");
	printf("  ------------------------------------------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarFunciones);
}

void DB_listarFuncion(int id){
	char sql_select[512];
	sprintf(sql_select,"SELECT Funciones.id[ID Función], titulo[Película], Funciones.id_sala[Sala Nº], Funciones.fecha[Fecha], Funciones.hora[Hora], (CASE WHEN subtitulada = 1 THEN \"SÍ\" ELSE \"NO\" END)[subtitulada],(SELECT COUNT() FROM Ubicaciones WHERE disponible=1 AND id_funcion=Funciones.id)[Lugares Disponibles],(SELECT COUNT() FROM Ubicaciones WHERE id_funcion=Funciones.id)[Capacidad Total] FROM Funciones INNER JOIN Peliculas ON id_pelicula = Peliculas.id WHERE Funciones.id = %d;", id);
	printf("\n\n  %-4s | %-50s | %-4s | %-10s | %-8s | %-12s | %s\n", "Id", "Película", "Sala", "Fecha", "Hora", "Subtitulada", "Disponibilidad");
	printf("  ------------------------------------------------------------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarFunciones);
}


static int dbCallback_listarFunciones(void *unused, int argc, char **argv, char **colName){
	printf("  %-4s | %-50s | %-4s | %-10s | %-8s | %-12s | %3s / %3s \n", argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
	return 0;
}


//Tarifas
void DB_listarTarifas(void){
	char* sql_select = {"SELECT * FROM Tarifas;"};
	printf("\n\n  %-4s | %-15s | %-30s | %-10s \n", "Id", "Tipo de Sala", "Tipo de Entrada", "Precio");
	printf("  -----------------------------------------------------------------------\n");
	database_execCallback(sql_select, dbCallback_listarTarifas);
	pause();
}


static int dbCallback_listarTarifas(void *unused, int argc, char **argv, char **colName){
	char tarifa[128];

	if(strcmp(argv[2], "Lunes Martes y MiÃ©rcoles 50%")==0){
		strcpy(tarifa, "Lunes Martes y Miércoles 50%");
	}else if(strcmp(argv[2], "NiÃ±os y Mayores de 65 aÃ±os")==0){
		strcpy(tarifa, "Niños y Mayores de 65 años");
	}else{
		strcpy(tarifa, argv[2]);
	}

	printf("  %-4s | %-15s | %-30s | %-10s \n", argv[0], argv[1], tarifa, argv[3]);
	return 0;
}


