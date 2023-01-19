/*
 * db_structure.h
 *
 *  Created on: 12 ene. 2023
 *      Author: GM
 */

#ifndef DB_DB_STRUCTURE_H_
#define DB_DB_STRUCTURE_H_

//USUARIOS
#define CREATE_TABLE_ADMINS "CREATE TABLE IF NOT EXISTS \"Admins\" (\"username\"TEXT NOT NULL,\"password\"TEXT NOT NULL,PRIMARY KEY(\"username\"));"
#define CREATE_TABLE_CLIENTES "CREATE TABLE IF NOT EXISTS \"Clientes\" (\"id\"INTEGER NOT NULL,\"nombre\"TEXT NOT NULL,\"apellido\"TEXT NOT NULL,\"dni\"INTEGER NOT NULL,\"socio\"INTEGER NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT));"

//PELÍCULAS
#define CREATE_TABLE_DIRECTORES "CREATE TABLE IF NOT EXISTS \"Directores\" (\"id\"INTEGER NOT NULL,\"nombre\"TEXT NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT));"
#define CREATE_TABLE_PELICULAS "CREATE TABLE IF NOT EXISTS \"Peliculas\" (\"id\"INTEGER NOT NULL,\"titulo\"TEXT NOT NULL UNIQUE,\"year\"INTEGER NOT NULL,\"duracion\"INTEGER,\"id_director\"INTEGER,\"proyectandose\"INTEGER NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT),FOREIGN KEY(\"id_director\") REFERENCES \"Directores\"(\"id\"));"
#define CREATE_TABLE_ACTORES "CREATE TABLE IF NOT EXISTS \"Actores\" (\"id\"INTEGER NOT NULL,\"nombre\"TEXT NOT NULL,\"apellido\"TEXT NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT));"
#define CREATE_TABLE_CAST "CREATE TABLE IF NOT EXISTS \"Cast\" (\"id_pelicula\"INTEGER NOT NULL,\"id_actor\"INTEGER NOT NULL,PRIMARY KEY(\"id_pelicula\",\"id_actor\"),FOREIGN KEY(\"id_pelicula\") REFERENCES \"Peliculas\"(\"id\"),FOREIGN KEY(\"id_actor\") REFERENCES \"Actores\"(\"id\"));"

//SALAS Y TARIFAS
#define CREATE_TABLE_HORARIOS "CREATE TABLE IF NOT EXISTS \"Horarios\" (\"id\"INTEGER NOT NULL,\"id_sala\"INTEGER NOT NULL,\"horario\"TEXT NOT NULL,PRIMARY KEY(\"id\"),FOREIGN KEY(\"id_sala\") REFERENCES \"Salas\"(\"id\"));"
#define CREATE_TABLE_SALAS "CREATE TABLE IF NOT EXISTS \"Salas\" (\"id\"INTEGER NOT NULL,\"tipo_sala\"TEXT NOT NULL,\"asientos_por_fila\"INTEGER NOT NULL,\"cantidad_filas\"INTEGER NOT NULL,\"tiene_pasillo_central\"INTEGER NOT NULL,PRIMARY KEY(\"id\"));"
#define CREATE_TABLE_TARIFAS "CREATE TABLE IF NOT EXISTS \"Tarifas\" (\"id\"INTEGER NOT NULL,\"tipo_sala\"TEXT NOT NULL,\"tipo_entrada\"TEXT NOT NULL,\"precio\"REAL NOT NULL,PRIMARY KEY(\"id\"));"

//SISTEMA DE VENTA
#define CREATE_TABLE_FUNCIONES "CREATE TABLE IF NOT EXISTS \"Funciones\" (\"id\"INTEGER NOT NULL,\"id_pelicula\"INTEGER NOT NULL,\"id_sala\"INTEGER NOT NULL,\"fecha\"TEXT NOT NULL,\"hora\"TEXT NOT NULL,\"subtitulada\"INTEGER NOT NULL,PRIMARY KEY(\"id\"),FOREIGN KEY(\"id_pelicula\") REFERENCES \"Peliculas\"(\"id\"),FOREIGN KEY(\"id_sala\") REFERENCES \"Salas\"(\"id\"));"
#define CREATE_TABLE_UBICACIONES "CREATE TABLE IF NOT EXISTS \"Ubicaciones\" (\"id\"INTEGER NOT NULL,\"fila\"TEXT NOT NULL,\"numero\"INTEGER NOT NULL,\"disponible\"INTEGER NOT NULL,\"id_funcion\"INTEGER NOT NULL,PRIMARY KEY(\"id\" AUTOINCREMENT),FOREIGN KEY(\"id_funcion\") REFERENCES \"Funciones\"(\"id\"));"
#define CREATE_TABLE_COMPRAS "CREATE TABLE IF NOT EXISTS \"Compras\" (\"id\"INTEGER NOT NULL,\"cantidad_entradas\"INTEGER NOT NULL,\"precio_total\"REAL NOT NULL,\"id_cliente\"INTEGER NOT NULL,PRIMARY KEY(\"id\"),FOREIGN KEY(\"id_cliente\") REFERENCES \"Clientes\"(\"id\"));"
#define CREATE_TABLE_ENTRADAS "CREATE TABLE \"Entradas\" (\"id\"INTEGER NOT NULL,\"precio\"REAL NOT NULL,\"id_compra\"INTEGER NOT NULL,\"id_ubicacion\"INTEGER NOT NULL,PRIMARY KEY(\"id\"),FOREIGN KEY(\"id_compra\") REFERENCES \"Compras\"(\"id\"),FOREIGN KEY(\"id_ubicacion\") REFERENCES \"Ubicaciones\"(\"id\"));"

#endif /* DB_DB_STRUCTURE_H_ */

void DB_createEveryTable(void);
int DB_createTableActores();
int DB_createTableAdmins();
int DB_createTableCast();
int DB_createTableClientes();
int DB_createTableCompras();
int DB_createTableDirectores();
int DB_createTableEntradas();
int DB_createTableFunciones();
int DB_createTableHorarios();
int DB_createTablePeliculas();
int DB_createTableSalas();
int DB_createTableTarifas();
int DB_createTableUbicaciones();

void DB_dropEveryTable(void);
int DB_dropTableActores();
int DB_dropTableAdmins();
int DB_dropTableCast();
int DB_dropTableClientes();
int DB_dropTableCompras();
int DB_dropTableDirectores();
int DB_dropTableEntradas();
int DB_dropTableFunciones();
int DB_dropTableHorarios();
int DB_dropTablePeliculas();
int DB_dropTableSalas();
int DB_dropTableTarifas();
int DB_dropTableUbicaciones();
