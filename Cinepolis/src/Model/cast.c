

#include "cast.h"
#include "actor.h"
#include "pelicula.h"
#include "macros.h"

static eCast* Cast_new(void);

//Constructor & Destructor
static eCast* Cast_new(void){
	eCast* newCast = (eCast*) malloc(sizeof(eCast));
	if(newCast != NULL){
		newCast->idPelicula = 0;
		newCast->idActor = 0;
	}
	return newCast;
}

eCast* Cast_newParam(int idPelicula, int idActor){
	eCast* newCast = Cast_new();
	int argc = 0;
	argc += Cast_setIdPelicula(newCast, idPelicula);
	argc += Cast_setIdActor(newCast, idActor);

	if(argc!=2){
		Cast_delete(newCast);
		newCast = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eCast idPelicula=%d idActor=%d.", idPelicula, idActor);
		ErrorLog_write(errorLog);
	}
	return newCast;
}

void Cast_delete(eCast* this){
	free(this);
}


//Attributes
int Cast_setIdPelicula(eCast* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->idPelicula = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cast_getIdPelicula(eCast* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idPelicula;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cast_setIdActor(eCast* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->idActor = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cast_getIdActor(eCast* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idActor;
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getCast(sqlite3_stmt* stmt, void* pCast);
static void dbReader_getCastList(sqlite3_stmt* stmt, void* list);

int DB_getCastByIds(eCast* pCast, int idPelicula, int idActor){
	return database_getRecordByIntAndInt((void*) pCast, "Cast", "Cast.id_pelicula", idPelicula, "Cast.id_actor", idActor, DB_DoesCastExistByIds, dbReader_getCast);
}

int DB_getListaCast(LinkedList* pListaCast){
	return database_execReader("SELECT * FROM Cast;", (void*) pListaCast, dbReader_getCastList);
}

static void dbReader_getCast(sqlite3_stmt* stmt, void* pCast){
	int idPelicula = sqlite3_column_int(stmt, 0);
	int idActor = sqlite3_column_int(stmt, 1);

	Cast_setIdPelicula(pCast, idPelicula);
	Cast_setIdActor(pCast, idActor);
}


static void dbReader_getCastList(sqlite3_stmt* stmt, void* list){
	int idPelicula = sqlite3_column_int(stmt, 0);
	int idActor = sqlite3_column_int(stmt, 1);

	eCast* buffer = Cast_newParam(idPelicula, idActor);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertCast(eCast cast){
	int outcome = FAILURE;
	if(DB_DoesPeliculaExistById(cast.idPelicula) && DB_DoesActorExistById(cast.idActor)){
		char sql_insert[256];
		sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Cast (id_pelicula, id_actor) VALUES(\"%d\",\"%d\");", cast.idPelicula, cast.idActor);
		outcome = database_insertRecordByIntAndInt(sql_insert, "Cast.id_pelicula", cast.idPelicula, "Cast.id_actor", cast.idActor, DB_DoesCastExistByIds);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - El cast {id_pelicula = \"%d\", id_actor = \"%d\"} no cumple el FK Constraint.", cast.idPelicula, cast.idActor);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int DB_deleteCast(int idPelicula, int idActor){
	return database_deleteRecordByIntAndInt("Cast", "id_pelicula", idPelicula, "id_actor", idActor, DB_DoesCastExistByIds);
}

int DB_DoesCastExistByIds(int idPelicula, int idActor){
	return database_CheckRecordExistenceByIntAndInt("Cast", "id_pelicula", idPelicula, "id_actor", idActor);
}
