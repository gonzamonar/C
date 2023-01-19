
#include "entrada.h"
#include "macros.h"

static eEntrada* Entrada_new(void);

//Constructor & Destructor
static eEntrada* Entrada_new(void){
	eEntrada* newEntrada = (eEntrada*) malloc(sizeof(eEntrada));
	if(newEntrada != NULL){
		newEntrada->id = 0;
		newEntrada->precio = 0;
		newEntrada->idCompra = 0;
		newEntrada->idUbicacion = 0;
	}
	return newEntrada;
}

eEntrada* Entrada_newParam(int id, float precio, int idCompra, int idUbicacion){
	eEntrada* newEntrada = Entrada_new();
	int r = 0;
	r += Entrada_setId(newEntrada, id);
	r += Entrada_setPrecio(newEntrada, precio);
	r += Entrada_setIdCompra(newEntrada, idCompra);
	r += Entrada_setIdUbicacion(newEntrada, idUbicacion);

	if(r!=4){
		Entrada_delete(newEntrada);
		newEntrada = NULL;
	}
	return newEntrada;
}

void Entrada_delete(eEntrada* this){
	free(this);
}


//Attributes
int Entrada_setId(eEntrada* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_getId(eEntrada* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_setPrecio(eEntrada* this, float precio){
	int outcome = FAILURE;
	if(this != NULL && precio > 0){
		this->precio = precio;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_getPrecio(eEntrada* this, float* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->precio;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_setIdCompra(eEntrada* this, int idCompra){
	int outcome = FAILURE;
	if(this != NULL && idCompra > 0){
		this->idCompra = idCompra;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_getIdCompra(eEntrada* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idCompra;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_setIdUbicacion(eEntrada* this, int idUbicacion){
	int outcome = FAILURE;
	if(this != NULL && idUbicacion > 0){
		this->idUbicacion = idUbicacion;
		outcome = SUCCESS;
	}
	return outcome;
}

int Entrada_getIdUbicacion(eEntrada* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idUbicacion;
		outcome = SUCCESS;
	}
	return outcome;
}



//Database Operations
static void dbReader_getEntrada(sqlite3_stmt* stmt, void* pEntrada);
static void dbReader_getListaEntradas(sqlite3_stmt* stmt, void* list);


int DB_getEntradaById(eEntrada* pEntrada, int id){
	return database_getRecordByInt((void*) pEntrada, "Entradas", "Entradas.id", id, DB_DoesEntradaExistById, dbReader_getEntrada);
}

int DB_getListaEntradas(LinkedList* pListaEntradas){
	return database_execReader("SELECT * FROM Entradas;", (void*) pListaEntradas, dbReader_getListaEntradas);
}

static void dbReader_getEntrada(sqlite3_stmt* stmt, void* pEntrada){
	int id = sqlite3_column_int(stmt, 0);
	float precio = (float) sqlite3_column_double(stmt, 1);
	int idCompra = sqlite3_column_int(stmt, 2);
	int idUbicacion = sqlite3_column_int(stmt, 3);

	Entrada_setId(pEntrada, id);
	Entrada_setPrecio(pEntrada, precio);
	Entrada_setIdCompra(pEntrada, idCompra);
	Entrada_setIdUbicacion(pEntrada, idUbicacion);
}

static void dbReader_getListaEntradas(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	float precio = (float) sqlite3_column_double(stmt, 1);
	int idCompra = sqlite3_column_int(stmt, 2);
	int idUbicacion = sqlite3_column_int(stmt, 3);

	eEntrada* buffer = Entrada_newParam(id, precio, idCompra, idUbicacion);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertEntrada(eEntrada entrada){
	char sql_insert[256];
	sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Entradas (id, precio, id_compra, id_ubicacion) VALUES(\"%d\",\"%.2f\",\"%d\",\"%d\");", entrada.id, entrada.precio, entrada.idCompra, entrada.idUbicacion);
	return database_insertRecordByInt(sql_insert, "Entradas.id_ubicacion", entrada.idUbicacion, DB_DoesEntradaExistByUbicacion);
}

int DB_updateEntrada(eEntrada entrada, int id){
	char sql_update[256];
	sprintf(sql_update, "PRAGMA foreign_keys = on; UPDATE Entradas SET precio=\"%.2f\", id_compra=\"%d\", id_ubicacion=\"%d\" WHERE Entradas.id = \"%d\";", entrada.precio, entrada.idCompra, entrada.idUbicacion, id);
	return database_updateRecordByInt(sql_update, "Entradas.id", id, DB_DoesEntradaExistById);
}

int DB_deleteEntrada(int id){
	return database_deleteRecordByInt("Entradas", "Entradas.id", id, DB_DoesEntradaExistById);
}

int DB_GetTableEntradasNextId(){
	return database_GetTableMaxId("Entradas") + 1;
}

int DB_DoesEntradaExistById(int id){
	return database_CheckRecordExistenceByInt("Entradas", "Entradas.id", id);
}

int DB_DoesEntradaExistByUbicacion(int idUbicacion){
	return database_CheckRecordExistenceByInt("Entradas", "id_ubicacion", idUbicacion);
}

