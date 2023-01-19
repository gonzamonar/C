
#include "database.h"
#include "db_structure.h"

void DB_createEveryTable(void){
	DB_createTableActores();
	DB_createTableAdmins();
	DB_createTableCast();
	DB_createTableClientes();
	DB_createTableCompras();
	DB_createTableDirectores();
	DB_createTableEntradas();
	DB_createTableFunciones();
	DB_createTableHorarios();
	DB_createTablePeliculas();
	DB_createTableSalas();
	DB_createTableTarifas();
	DB_createTableUbicaciones();
}


int DB_createTableActores(){
	return database_execNonQuery(CREATE_TABLE_ACTORES);
}

int DB_createTableAdmins(){
	return database_execNonQuery(CREATE_TABLE_ADMINS);
}

int DB_createTableCast(){
	return database_execNonQuery(CREATE_TABLE_CAST);
}

int DB_createTableClientes(){
	return database_execNonQuery(CREATE_TABLE_CLIENTES);
}

int DB_createTableCompras(){
	return database_execNonQuery(CREATE_TABLE_COMPRAS);
}

int DB_createTableDirectores(){
	return database_execNonQuery(CREATE_TABLE_DIRECTORES);
}

int DB_createTableEntradas(){
	return database_execNonQuery(CREATE_TABLE_ENTRADAS);
}

int DB_createTableFunciones(){
	return database_execNonQuery(CREATE_TABLE_FUNCIONES);
}

int DB_createTableHorarios(){
	return database_execNonQuery(CREATE_TABLE_HORARIOS);
}

int DB_createTablePeliculas(){
	return database_execNonQuery(CREATE_TABLE_PELICULAS);
}

int DB_createTableSalas(){
	return database_execNonQuery(CREATE_TABLE_SALAS);
}

int DB_createTableTarifas(){
	return database_execNonQuery(CREATE_TABLE_TARIFAS);
}

int DB_createTableUbicaciones(){
	return database_execNonQuery(CREATE_TABLE_UBICACIONES);
}


void DB_dropEveryTable(void){
	DB_dropTableActores();
	DB_dropTableAdmins();
	DB_dropTableCast();
	DB_dropTableClientes();
	DB_dropTableCompras();
	DB_dropTableDirectores();
	DB_dropTableEntradas();
	DB_dropTableFunciones();
	DB_dropTableHorarios();
	DB_dropTablePeliculas();
	DB_dropTableSalas();
	DB_dropTableTarifas();
	DB_dropTableUbicaciones();
}


int DB_dropTableActores(){
	return database_execNonQuery("DROP TABLE Actores;");
}

int DB_dropTableAdmins(){
	return database_execNonQuery("DROP TABLE Admins;");
}

int DB_dropTableCast(){
	return database_execNonQuery("DROP TABLE Cast;");
}

int DB_dropTableClientes(){
	return database_execNonQuery("DROP TABLE Clientes;");
}

int DB_dropTableCompras(){
	return database_execNonQuery("DROP TABLE Compras;");
}

int DB_dropTableDirectores(){
	return database_execNonQuery("DROP TABLE Directores;");
}

int DB_dropTableEntradas(){
	return database_execNonQuery("DROP TABLE Entradas;");
}

int DB_dropTableFunciones(){
	return database_execNonQuery("DROP TABLE Funciones;");
}

int DB_dropTableHorarios(){
	return database_execNonQuery("DROP TABLE Horarios;");
}

int DB_dropTablePeliculas(){
	return database_execNonQuery("DROP TABLE Peliculas;");
}

int DB_dropTableSalas(){
	return database_execNonQuery("DROP TABLE Salas;");
}

int DB_dropTableTarifas(){
	return database_execNonQuery("DROP TABLE Tarifas;");
}

int DB_dropTableUbicaciones(){
	return database_execNonQuery("DROP TABLE Ubicaciones;");
}
