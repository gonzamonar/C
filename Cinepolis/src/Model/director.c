
#include "director.h"
#include "macros.h"

static eDirector* Director_new(void);

//Constructor & Destructor
static eDirector* Director_new(void){
	eDirector* newDirector = (eDirector*) malloc(sizeof(eDirector));
	if(newDirector != NULL){
		newDirector->id = 0;
		strcpy(newDirector->nombre,"");
	}
	return newDirector;
}

eDirector* Director_newParam(int id, char* nombre){
	eDirector* newDirector = Director_new();
	int argc = 0;
	argc += Director_setId(newDirector, id);
	argc += Director_setNombre(newDirector, nombre);

	if(argc!=2){
		Director_delete(newDirector);
		newDirector = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eDirector %d %s.", id, nombre);
		ErrorLog_write(errorLog);
	}
	return newDirector;
}

void Director_delete(eDirector* this){
	free(this);
}


//Attributes
int Director_setId(eDirector* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id >= 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Director_getId(eDirector* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Director_setNombre(eDirector* this, char* nombre){
	int outcome = FAILURE;
	if(this != NULL && nombre != NULL){
		strcpy(this->nombre, nombre);
		outcome = SUCCESS;
	}
	return outcome;
}

int Director_getNombre(eDirector* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->nombre);
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getDirector(sqlite3_stmt* stmt, void* pDirector);
static void dbReader_getListaDirectores(sqlite3_stmt* stmt, void* list);

int DB_getDirectorById(eDirector* pDirector, int id){
	return database_getRecordByInt((void*) pDirector, "Directores", "Directores.id", id, DB_DoesDirectorExistById, dbReader_getDirector);
}

int DB_getDirectorByName(eDirector* pDirector, char* nombre){
	return database_getRecordByStr((void*) pDirector, "Directores", "Directores.nombre", nombre, DB_DoesDirectorExistByName, dbReader_getDirector);
}

int DB_getListaDirectores(LinkedList* pListaDirectores){
	return database_execReader("SELECT * FROM Directores;", (void*) pListaDirectores, dbReader_getListaDirectores);
}

static void dbReader_getDirector(sqlite3_stmt* stmt, void* pDirector){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* nombre = sqlite3_column_text(stmt, 1);

	Director_setId(pDirector, id);
	Director_setNombre(pDirector, (char*)nombre);
}

static void dbReader_getListaDirectores(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* nombre = sqlite3_column_text(stmt, 1);

	eDirector* buffer = Director_newParam(id, (char*) nombre);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertDirector(eDirector director){
	char sql_insert[256];
	sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Directores (nombre) VALUES(\"%s\");", director.nombre);
	return database_insertRecordByStr(sql_insert, "Directores.nombre", director.nombre, DB_DoesDirectorExistByName);
}

int DB_updateDirector(eDirector director, int id){
	char sql_update[256];
	sprintf(sql_update, "PRAGMA foreign_keys = on; UPDATE Directores SET nombre=\"%s\" WHERE Directores.id = \"%d\";", director.nombre, id);
	return database_updateRecordByInt(sql_update, "Directores.id", id, DB_DoesDirectorExistById);
}

int DB_deleteDirector(int id){
	return database_deleteRecordByInt("Directores", "Directores.id", id, DB_DoesDirectorExistById);
}

int DB_DoesDirectorExistById(int id){
	return database_CheckRecordExistenceByInt("Directores", "Directores.id", id);
}

int DB_DoesDirectorExistByName(char* name){
	return database_CheckRecordExistenceByStr("Directores", "Directores.nombre", name);
}
