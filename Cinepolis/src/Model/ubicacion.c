
#include "ubicacion.h"
#include "macros.h"
#include "sala.h"

static eUbicacion* Ubicacion_new(void);

//Constructor & Destructor
static eUbicacion* Ubicacion_new(void){
	eUbicacion* newUbicacion = (eUbicacion*) malloc(sizeof(eUbicacion));
	if(newUbicacion != NULL){
		newUbicacion->id = 0;
		newUbicacion->fila = ' ';
		newUbicacion->numero = 0;
		newUbicacion->disponible = 1;
		newUbicacion->idFuncion = 0;
	}
	return newUbicacion;
}

eUbicacion* Ubicacion_newParam(int id, char fila, int numero, short disponible, int idFuncion){
	eUbicacion* newUbicacion = Ubicacion_new();
	int argc = 0;
	argc += Ubicacion_setId(newUbicacion, id);
	argc += Ubicacion_setFila(newUbicacion, fila);
	argc += Ubicacion_setNumero(newUbicacion, numero);
	argc += Ubicacion_setDisponible(newUbicacion, disponible);
	argc += Ubicacion_setFuncion(newUbicacion, idFuncion);

	if(argc!=5){
		Ubicacion_delete(newUbicacion);
		newUbicacion = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eUbicacion ID=%d Fila=%c Nro=%d.", id, fila, numero);
		ErrorLog_write(errorLog);
	}
	return newUbicacion;
}

void Ubicacion_delete(eUbicacion* this){
	free(this);
}


//Attributes
int Ubicacion_setId(eUbicacion* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_getId(eUbicacion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_setFila(eUbicacion* this, char fila){
	int outcome = FAILURE;
	fila = toupper(fila);
	if(this != NULL && fila >= 'A'){
		this->fila = fila;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_getFila(eUbicacion* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->fila;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_setNumero(eUbicacion* this, int numero){
	int outcome = FAILURE;
	if(this != NULL && numero > 0){
		this->numero = numero;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_getNumero(eUbicacion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->numero;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_setDisponible(eUbicacion* this, int disponible){
	int outcome = FAILURE;
	if(this != NULL && (disponible == 0 || disponible == 1 || disponible == 2)){
		this->disponible = disponible;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_getDisponible(eUbicacion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->disponible;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_setFuncion(eUbicacion* this, int idFuncion){
	int outcome = FAILURE;
	if(this != NULL && idFuncion > 0){
		this->idFuncion = idFuncion;
		outcome = SUCCESS;
	}
	return outcome;
}

int Ubicacion_getFuncion(eUbicacion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idFuncion;
		outcome = SUCCESS;
	}
	return outcome;
}


//List Operations
int UbicacionLL_getId(LinkedList* listaUbicaciones, char fila, int numero){
	int id = 0;
	if(listaUbicaciones != NULL){
		int len = ll_len(listaUbicaciones);

		for(int i=0; i<len; i++){
			eUbicacion* ubicacion = (eUbicacion*) ll_get(listaUbicaciones, i);
			if(ubicacion->fila == fila && ubicacion->numero==numero){
				id = ubicacion->id;
				break;
			}
		}
	}
	return id;
}

int UbicacionLL_getDisponibilidad(LinkedList* listaUbicaciones, char fila, int numero){
	int available = -1;
	if(listaUbicaciones != NULL){
		int len = ll_len(listaUbicaciones);

		for(int i=0; i<len; i++){
			eUbicacion *ubicacion = (eUbicacion*) ll_get(listaUbicaciones, i);
			if(ubicacion->fila == fila && ubicacion->numero==numero){
				available = ubicacion->disponible;
				break;
			}
		}
	}
	return available;
}

int UbicacionLL_cambiarDisponibilidad(LinkedList* listaUbicaciones, char fila, int numero, short disponibilidad){
	int outcome = 0;
	if(listaUbicaciones != NULL){
		int len = ll_len(listaUbicaciones);

		for(int i=0; i<len; i++){
			eUbicacion *ubicacion = (eUbicacion*) ll_get(listaUbicaciones, i);
			if(ubicacion->fila == fila && ubicacion->numero==numero){
				Ubicacion_setDisponible(ubicacion, disponibilidad);
				outcome = 1;
				break;
			}
		}
	}
	return outcome;
}


int Ubicacion_parser(char* ubicacion, char* pFila, int* pNumero){
	int outcome = 0;
	char nro[3];
	int len = strlen(ubicacion);
	if(ubicacion != NULL && pFila != NULL && pNumero != NULL && len == 3){
		strncpy(nro, ubicacion+1, 2);
		*pFila = ubicacion[0];
		*pNumero = atoi(nro);
		outcome = 1;
	}
	return outcome;
}


//Database Operations
static void dbReader_getUbicacion(sqlite3_stmt* stmt, void* pFuncion);
static void dbReader_getListaUbicaciones(sqlite3_stmt* stmt, void* list);

int DB_getUbicacion(eUbicacion* pUbicacion, int id){
	return database_getRecordByInt((void*) pUbicacion, "Ubicaciones", "Ubicaciones.id", id, DB_DoesUbicacionExistById, dbReader_getUbicacion);
}


int DB_getListaUbicaciones(LinkedList* pListaUbicaciones){
	return database_execReader("SELECT * FROM Ubicaciones;", (void*) pListaUbicaciones, dbReader_getListaUbicaciones);
}

int DB_getListaUbicacionesPorFuncion(LinkedList* pListaUbicaciones, int idFuncion){
	char sql_select[256];
	sprintf(sql_select, "SELECT * FROM Ubicaciones WHERE Ubicaciones.id_funcion = %d ORDER BY fila,numero;", idFuncion);
	return database_execReader(sql_select, (void*) pListaUbicaciones, dbReader_getListaUbicaciones);
}

int DB_getListaUbicacionesDisponiblesPorFuncion(LinkedList* pListaUbicaciones, int idFuncion){
	char sql[256];
	sprintf(sql, "SELECT * FROM Ubicaciones WHERE id_funcion = %d AND disponible = 1;", idFuncion);
	return database_execReader(sql, (void*) pListaUbicaciones, dbReader_getListaUbicaciones);
}

static void dbReader_getUbicacion(sqlite3_stmt* stmt, void* pUbicacion){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* fila = sqlite3_column_text(stmt, 1);
	int numero = sqlite3_column_int(stmt, 2);
	short disponible = (short) sqlite3_column_int(stmt, 3);
	int idFuncion = sqlite3_column_int(stmt, 4);

	Ubicacion_setId(pUbicacion, id);
	Ubicacion_setFila(pUbicacion, fila[0]);
	Ubicacion_setNumero(pUbicacion, numero);
	Ubicacion_setDisponible(pUbicacion, disponible);
	Ubicacion_setFuncion(pUbicacion, idFuncion);
}

static void dbReader_getListaUbicaciones(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* fila = sqlite3_column_text(stmt, 1);
	int numero = sqlite3_column_int(stmt, 2);
	short disponible = (short) sqlite3_column_int(stmt, 3);
	int idFuncion = sqlite3_column_int(stmt, 4);

	eUbicacion* buffer = Ubicacion_newParam(id, fila[0], numero, disponible, idFuncion);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertUbicacion(eUbicacion ubicacion){
	char sql_insert[256];
	sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Ubicaciones (fila,numero,disponible,id_funcion) VALUES(\"%c\", \"%d\", \"%d\", \"%d\");",
										ubicacion.fila, ubicacion.numero, ubicacion.disponible, ubicacion.idFuncion);
	return database_execNonQuery(sql_insert);
}

int DB_updateUbicacion(eUbicacion ubicacion, int id){
	char sql_update[256];
	sprintf(sql_update, "PRAGMA foreign_keys = on; UPDATE Ubicaciones SET fila=\"%c\", numero=\"%d\", disponible=\"%d\", id_funcion=\"%d\" WHERE Ubicaciones.id = \"%d\";", ubicacion.fila, ubicacion.numero, ubicacion.disponible, ubicacion.idFuncion, id);
	return database_updateRecordByInt(sql_update, "Ubicaciones.id", ubicacion.id, DB_DoesUbicacionExistById);
}

int DB_updateDisponibilidadUbicacion(int idUbicacion, int disponible){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Ubicaciones SET disponible=\"%d\" WHERE Ubicaciones.id = \"%d\";", disponible, idUbicacion);
	return database_updateRecordByInt(sql_update, "Ubicaciones.id", idUbicacion, DB_DoesUbicacionExistById);
}

int DB_deleteUbicacion(int id){
	return database_deleteRecordByInt("Ubicaciones", "Ubicaciones.id", id, DB_DoesUbicacionExistById);
}

int DB_DoesUbicacionExistById(int id){
	return database_CheckRecordExistenceByInt("Ubicaciones", "Ubicaciones.id", id);
}

int DB_GetCantidadUbicacionesLibres(){
	return database_GetSingleInt("SELECT COUNT() FROM Ubicaciones WHERE disponible = 1;");
}

int DB_GetCantidadUbicacionesLibresPorFuncion(int idFuncion){
	char sql[256];
	sprintf(sql, "SELECT COUNT() FROM Ubicaciones WHERE id_funcion = %d AND disponible = 1;", idFuncion);
	return database_GetSingleInt(sql);
}


int DB_GenerarUbicacionesPorFuncion(eFuncion funcion){
	eSala sala;
	DB_getSalaById(&sala, funcion.idSala);

	int ubicacionesCreadas = 0;

	eUbicacion ubicacion;
	ubicacion.id = 0;
	ubicacion.fila = 'A';
	ubicacion.numero = 0;
	ubicacion.disponible = 1;
	ubicacion.idFuncion = funcion.id;

	for(int i=0;i<sala.cantidadFilas;i++){
		for(int j=0; j<sala.asientosPorFila;j++){
			ubicacion.numero = j+1;
			if(DB_insertUbicacion(ubicacion)==0){
				ubicacionesCreadas++;
			}
		}
		ubicacion.fila++;
	}

	return ubicacionesCreadas;
}

