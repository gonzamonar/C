
#include "actor.h"
#include "macros.h"

static eActor* Actor_new(void);

//Constructor & Destructor
static eActor* Actor_new(void){
	eActor* newActor = (eActor*) malloc(sizeof(eActor));
	if(newActor != NULL){
		newActor->id = 0;
		strcpy(newActor->nombre,"");
		strcpy(newActor->apellido,"");
	}
	return newActor;
}

eActor* Actor_newParam(int id, char* nombre, char* apellido){
	eActor* newActor = Actor_new();
	int argc = 0;
	argc += Actor_setId(newActor, id);
	argc += Actor_setNombre(newActor, nombre);
	argc += Actor_setApellido(newActor, apellido);

	if(argc!=3){
		Actor_delete(newActor);
		newActor = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eActor %d %s %s.", id, nombre, apellido);
		ErrorLog_write(errorLog);
	}
	return newActor;
}

void Actor_delete(eActor* this){
	free(this);
}


//Attributes
int Actor_setId(eActor* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id >= 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Actor_getId(eActor* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Actor_setNombre(eActor* this, char* nombre){
	int outcome = FAILURE;
	if(this != NULL && nombre != NULL){
		strcpy(this->nombre, nombre);
		outcome = SUCCESS;
	}
	return outcome;
}

int Actor_getNombre(eActor* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->nombre);
		outcome = SUCCESS;
	}
	return outcome;
}


int Actor_setApellido(eActor* this, char* apellido){
	int outcome = FAILURE;
	if(this != NULL && apellido != NULL){
		strcpy(this->apellido, apellido);
		outcome = SUCCESS;
	}
	return outcome;
}

int Actor_getApellido(eActor* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->apellido);
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getActor(sqlite3_stmt* stmt, void* pActor);
static void dbReader_getActorList(sqlite3_stmt* stmt, void* list);

int DB_getActorById(eActor* pActor, int id){
	return database_getRecordByInt((void*) pActor, "Actores", "Actores.id", id, DB_DoesActorExistById, dbReader_getActor);
}

int DB_getListaActores(LinkedList* pListaActores){
	return database_execReader("SELECT * FROM Actores;", (void*) pListaActores, dbReader_getActorList);
}

static void dbReader_getActor(sqlite3_stmt* stmt, void* pActor){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* nombre = sqlite3_column_text(stmt, 1);
	const unsigned char* apellido = sqlite3_column_text(stmt, 2);

	Actor_setId(pActor, id);
	Actor_setNombre(pActor, (char*) nombre);
	Actor_setApellido(pActor, (char*) apellido);
}

static void dbReader_getActorList(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* nombre = sqlite3_column_text(stmt, 1);
	const unsigned char* apellido = sqlite3_column_text(stmt, 2);

	eActor* buffer = Actor_newParam(id, (char*)nombre, (char*)apellido);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertActor(eActor actor){
	char sql_insert[256];
	sprintf(sql_insert, "INSERT INTO Actores (nombre, apellido) VALUES(\"%s\",\"%s\");", actor.nombre, actor.apellido);
	return database_insertRecordByStrAndStr(sql_insert, "Actores.nombre", actor.nombre, "Actores.apellido", actor.apellido, DB_DoesActorExistByFullName);
}

int DB_updateActor(eActor actor, int id){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Actores SET nombre=\"%s\", apellido=\"%s\" WHERE Actores.id = \"%d\";", actor.nombre, actor.apellido, id);
	return database_updateRecordByInt(sql_update, "Actores.id", id, DB_DoesActorExistById);
}

int DB_deleteActor(int id){
	return database_deleteRecordByInt("Actores", "Actores.id", id, DB_DoesActorExistById);
}

int DB_DoesActorExistById(int id){
	return database_CheckRecordExistenceByInt("Actores", "Actores.id", id);
}

int DB_DoesActorExistByFullName(char* name, char* surname){
	return database_CheckRecordExistenceByStrAndStr("Actores", "Actores.nombre", name, "Actores.apellido", surname);
}
