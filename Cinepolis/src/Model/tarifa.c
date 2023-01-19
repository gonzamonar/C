
#include "tarifa.h"
#include "macros.h"

#include "sala.h"
#include "../My_Libraries/date.h"

static eTarifa* Tarifa_new(void);

//Constructor & Destructor
static eTarifa* Tarifa_new(void){
	eTarifa* newTarifa = (eTarifa*) malloc(sizeof(eTarifa));
	if(newTarifa != NULL){
		newTarifa->id = 0;
		strcpy(newTarifa->tipoSala,"");
		strcpy(newTarifa->tipoEntrada,"");
		newTarifa->precio = 0;
	}
	return newTarifa;
}

eTarifa* Tarifa_newParam(int id, char* tipoSala, char* tipoEntrada, float precio){
	eTarifa* newTarifa = Tarifa_new();
	int argc = 0;
	argc += Tarifa_setId(newTarifa, id);
	argc += Tarifa_setTipoSala(newTarifa, tipoSala);
	argc += Tarifa_setTipoEntrada(newTarifa, tipoEntrada);
	argc += Tarifa_setPrecio(newTarifa, precio);

	if(argc!=4){
		Tarifa_delete(newTarifa);
		newTarifa = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eTarifa id %d, sala %s, entrada %s, precio %.2f.", id, tipoSala, tipoEntrada, precio);
		ErrorLog_write(errorLog);
	}
	return newTarifa;
}

void Tarifa_delete(eTarifa* this){
	free(this);
}


//Attributes
int Tarifa_setId(eTarifa* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_getId(eTarifa* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_setTipoSala(eTarifa* this, char* tipoSala){
	int outcome = FAILURE;
	if(this != NULL && tipoSala != NULL){
		strcpy(this->tipoSala, tipoSala);
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_getTipoSala(eTarifa* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->tipoSala);
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_setTipoEntrada(eTarifa* this, char* tipoEntrada){
	int outcome = FAILURE;
	if(this != NULL && tipoEntrada != NULL){
		strcpy(this->tipoEntrada, tipoEntrada);
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_getTipoEntrada(eTarifa* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->tipoEntrada);
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_setPrecio(eTarifa* this, float precio){
	int outcome = FAILURE;
	if(this != NULL && precio > 0){
		this->precio = precio;
		outcome = SUCCESS;
	}
	return outcome;
}

int Tarifa_getPrecio(eTarifa* this, float* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->precio;
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getTarifa(sqlite3_stmt* stmt, void* pTarifa);
static void dbReader_getListaTarifas(sqlite3_stmt* stmt, void* list);

int DB_getTarifaById(eTarifa* pTarifa, int id){
	return database_getRecordByInt((void*) pTarifa, "Tarifas", "Tarifas.id", id, DB_DoesTarifaExistById, dbReader_getTarifa);
}

int DB_getListaTarifas(LinkedList* pListaTarifas){
	return database_execReader("SELECT * FROM Tarifas;", (void*) pListaTarifas, dbReader_getListaTarifas);
}

static void dbReader_getTarifa(sqlite3_stmt* stmt, void* pTarifa){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* tipoSala = sqlite3_column_text(stmt, 1);
	const unsigned char* tipoEntrada = sqlite3_column_text(stmt, 2);
	float precio = (float) sqlite3_column_double(stmt, 3);

	Tarifa_setId(pTarifa, id);
	Tarifa_setTipoSala(pTarifa, (char*)tipoSala);
	Tarifa_setTipoEntrada(pTarifa, (char*)tipoEntrada);
	Tarifa_setPrecio(pTarifa, precio);
}

static void dbReader_getListaTarifas(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* tipoSala = sqlite3_column_text(stmt, 1);
	const unsigned char* tipoEntrada = sqlite3_column_text(stmt, 2);
	float precio = (float) sqlite3_column_double(stmt, 3);

	eTarifa* buffer = Tarifa_newParam(id, (char*) tipoSala, (char*) tipoEntrada, precio);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertTarifa(eTarifa tarifa){
	char sql_insert[256];
	sprintf(sql_insert, "INSERT INTO Tarifas (id, tipo_sala, tipo_entrada, precio) VALUES(\"%d\",\"%s\",\"%s\",\"%.2f\");", tarifa.id, tarifa.tipoSala, tarifa.tipoEntrada, tarifa.precio);
	return database_insertRecordByInt(sql_insert, "Tarifas.id", tarifa.id, DB_DoesTarifaExistById);
}

int DB_updateTarifa(eTarifa tarifa, int id){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Tarifas SET tipo_sala=\"%s\", tipo_entrada=\"%s\", precio=\"%f\" WHERE Tarifas.id = \"%d\";", tarifa.tipoSala, tarifa.tipoEntrada, tarifa.precio, id);
	return database_updateRecordByInt(sql_update, "Tarifas.id", id, DB_DoesTarifaExistById);
}

int DB_deleteTarifa(int id){
	return database_deleteRecordByInt("Tarifas", "Tarifas.id", id, DB_DoesTarifaExistById);
}

int DB_DoesTarifaExistById(int id){
	return database_CheckRecordExistenceByInt("Tarifas", "Tarifas.id", id);
}

int DB_GetPrecioTarifa(int idTarifa){
	char sql_query[256];
	sprintf(sql_query, "SELECT precio FROM Tarifas WHERE id = %d;", idTarifa);
	return database_GetSingleInt(sql_query);
}


float DB_SelectTarifa(int idSala, char* fechaFuncion, int esNinoOAdultoMayor, int esSocio){
	float cargoServicio;
	float precioEntrada;
	char tipoSala[3];

	int esSala2D = strcmp(tipoSala, "2D") ? 1 : 0;
	int dayofweek = dayofweek_str(fechaFuncion);

	//CARGO DE SERVICIO
	cargoServicio = (esSala2D) ? DB_GetPrecioTarifa(102) : DB_GetPrecioTarifa(103) ;

	//ENTRADA
	if(dayofweek==1 || dayofweek==2 || dayofweek==3)
	{
		precioEntrada = (esSala2D) ? DB_GetPrecioTarifa(250) : DB_GetPrecioTarifa(350) ; //Entrada 50%
	}
	else if(esSala2D && esNinoOAdultoMayor)
	{
		precioEntrada = DB_GetPrecioTarifa(265);	 									 //Entrada 2D para Niño o Mayor de 65
	}
	else
	{
		precioEntrada = (esSala2D) ? DB_GetPrecioTarifa(200) : DB_GetPrecioTarifa(300) ; //Entrada General
	}

	//DESCUENTO DE SOCIO
	if(esSocio)
	{
		precioEntrada *= 0.9;
	}

	return precioEntrada + cargoServicio;
}

