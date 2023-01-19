
#include "sala.h"
#include "macros.h"

static eSala* Sala_new(void);

//Constructor & Destructor
static eSala* Sala_new(void){
	eSala* newSala = (eSala*) malloc(sizeof(eSala));
	if(newSala != NULL){
		newSala->id = 0;
		strcpy(newSala->tipoSala, "");
		newSala->asientosPorFila = 0;
		newSala->cantidadFilas = 0;
		newSala->tienePasilloCentral = 0;
	}
	return newSala;
}

eSala* Sala_newParam(int id, char* tipoSala, int asientosPorFila, int cantidadFilas, short tienePasilloCentral){
	eSala* newSala = Sala_new();
	int argc = 0;
	argc += Sala_setId(newSala, id);
	argc += Sala_setTipoSala(newSala, tipoSala);
	argc += Sala_setAsientosPorFila(newSala, asientosPorFila);
	argc += Sala_setCantidadFilas(newSala, cantidadFilas);
	argc += Sala_setTienePasilloCentral(newSala, tienePasilloCentral);

	if(argc!=5){
		Sala_delete(newSala);
		newSala = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eSala id=%d tipoSala=%s.", id, tipoSala);
		ErrorLog_write(errorLog);
	}
	return newSala;
}

void Sala_delete(eSala* this){
	free(this);
}


//Attributes
int Sala_setId(eSala* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_getId(eSala* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_setTipoSala(eSala* this, char* tipoSala){
	int outcome = FAILURE;
	if(this != NULL && tipoSala != NULL){
		strcpy(this->tipoSala, tipoSala);
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_getTipoSala(eSala* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->tipoSala);
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_setAsientosPorFila(eSala* this, int asientosPorFila){
	int outcome = FAILURE;
	if(this != NULL && asientosPorFila > 0){
		this->asientosPorFila = asientosPorFila;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_getAsientosPorFila(eSala* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->asientosPorFila;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_setCantidadFilas(eSala* this, int cantidadFilas){
	int outcome = FAILURE;
	if(this != NULL && cantidadFilas > 0){
		this->cantidadFilas = cantidadFilas;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_getCantidadFilas(eSala* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->cantidadFilas;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_setTienePasilloCentral(eSala* this, short tienePasilloCentral){
	int outcome = FAILURE;
	if(this != NULL && (tienePasilloCentral == 0 || tienePasilloCentral == 1)){
		this->tienePasilloCentral = tienePasilloCentral;
		outcome = SUCCESS;
	}
	return outcome;
}

int Sala_getTienePasilloCentral(eSala* this, short* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->tienePasilloCentral;
		outcome = SUCCESS;
	}
	return outcome;
}



//Database Operations
static void dbReader_getSala(sqlite3_stmt* stmt, void* pSala);
static void dbReader_getListaSalas(sqlite3_stmt* stmt, void* list);

int DB_getSalaById(eSala* pSala, int id){
	return database_getRecordByInt((void*) pSala, "Salas", "Salas.id", id, DB_DoesSalaExistById, dbReader_getSala);
}

int DB_getListaSalas(LinkedList* pListaSalas){
	return database_execReader("SELECT * FROM Salas;", (void*)pListaSalas, dbReader_getListaSalas);
}

static void dbReader_getSala(sqlite3_stmt* stmt, void* pSala){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* tipoSala = sqlite3_column_text(stmt, 1);
	int asientosPorFila = sqlite3_column_int(stmt, 2);
	int cantidadFilas = sqlite3_column_int(stmt, 3);
	short tienePasilloCentral = (short)sqlite3_column_int(stmt, 4);

	Sala_setId(pSala, id);
	Sala_setTipoSala(pSala, (char*)tipoSala);
	Sala_setAsientosPorFila(pSala, asientosPorFila);
	Sala_setCantidadFilas(pSala, cantidadFilas);
	Sala_setTienePasilloCentral(pSala, tienePasilloCentral);
}

static void dbReader_getListaSalas(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* tipoSala = sqlite3_column_text(stmt, 1);
	int asientosPorFila = sqlite3_column_int(stmt, 2);
	int cantidadFilas = sqlite3_column_int(stmt, 3);
	short tienePasilloCentral = (short)sqlite3_column_int(stmt, 4);

	eSala* buffer = Sala_newParam(id, (char*) tipoSala, asientosPorFila, cantidadFilas, (short) tienePasilloCentral);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}


int DB_insertSala(eSala sala){
	char sql_insert[256];
	sprintf(sql_insert, "INSERT INTO Salas (id, tipo_sala, asientos_por_fila, cantidad_filas, tiene_pasillo_central) VALUES(\"%d\",\"%s\",\"%d\",\"%d\",\"%d\");", sala.id, sala.tipoSala, sala.asientosPorFila, sala.cantidadFilas, sala.tienePasilloCentral);
	return database_insertRecordByInt(sql_insert, "Salas.id", sala.id, DB_DoesSalaExistById);
}

int DB_updateSala(eSala sala, int id){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Salas SET tipo_sala=\"%s\", asientos_por_fila=\"%d\", cantidad_filas=\"%d\", tiene_pasillo_central=\"%d\" WHERE Salas.id = \"%d\";", sala.tipoSala, sala.asientosPorFila, sala.cantidadFilas, sala.tienePasilloCentral, id);
	return database_updateRecordByInt(sql_update, "Salas.id", id, DB_DoesSalaExistById);
}

int DB_deleteSala(int id){
	return database_deleteRecordByInt("Salas", "Salas.id", id, DB_DoesSalaExistById);
}

int DB_DoesSalaExistById(int id){
	return database_CheckRecordExistenceByInt("Salas", "Salas.id", id);
}

int DB_GetCapacidadSala(int idSala){
	char sql_query[256];
	sprintf(sql_query, "SELECT asientos_por_fila*cantidad_filas FROM Salas WHERE id = %d;", idSala);
	return database_GetSingleInt(sql_query);
}

void DB_GetTipoSala(char* dest, int idSala){
	char sql_query[256];
	sprintf(sql_query, "SELECT tipo_sala FROM Salas WHERE id = %d;", idSala);
	database_GetSingleStr(sql_query, dest);
}
