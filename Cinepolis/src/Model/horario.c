
#include "horario.h"
#include "macros.h"

static eHorario* Horario_new(void);

//Constructor & Destructor
static eHorario* Horario_new(void){
	eHorario* newHorario = (eHorario*) malloc(sizeof(eHorario));
	if(newHorario != NULL){
		newHorario->id = 0;
		newHorario->idSala = 0;
		strcpy(newHorario->hora,"");
	}
	return newHorario;
}

eHorario* Horario_newParam(int id, int idSala, char* hora){
	eHorario* newHorario = Horario_new();
	int argc = 0;
	argc += Horario_setId(newHorario, id);
	argc += Horario_setIdSala(newHorario, idSala);
	argc += Horario_setHora(newHorario, hora);

	if(argc!=3){
		Horario_delete(newHorario);
		newHorario = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eHorario %d %s.", id, hora);
		ErrorLog_write(errorLog);
	}
	return newHorario;
}

void Horario_delete(eHorario* this){
	free(this);
}


//Attributes
int Horario_setId(eHorario* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Horario_getId(eHorario* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Horario_setIdSala(eHorario* this, int idSala){
	int outcome = FAILURE;
	if(this != NULL && idSala > 0){
		this->idSala = idSala;
		outcome = SUCCESS;
	}
	return outcome;
}

int Horario_getIdSala(eHorario* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idSala;
		outcome = SUCCESS;
	}
	return outcome;
}

int Horario_setHora(eHorario* this, char* hora){
	int outcome = FAILURE;
	if(this != NULL && hora != NULL){
		strcpy(this->hora, hora);
		outcome = SUCCESS;
	}
	return outcome;
}

int Horario_getHora(eHorario* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->hora);
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getHorario(sqlite3_stmt* stmt, void* pHorario);
static void dbReader_getListaHorarios(sqlite3_stmt* stmt, void* list);

int DB_getHorarioById(eHorario* pHorario, int id){
	return database_getRecordByInt((void*) pHorario, "Horarios", "Horarios.id", id, DB_DoesHorarioExistById, dbReader_getHorario);
}

int DB_getListaHorarios(LinkedList* pListaHorarios){
	return database_execReader("SELECT * FROM Horarios;", (void*) pListaHorarios, dbReader_getListaHorarios);
}

static void dbReader_getHorario(sqlite3_stmt* stmt, void* pHorario){
	int id = sqlite3_column_int(stmt, 0);
	int idSala = sqlite3_column_int(stmt, 1);
	const unsigned char* hora = sqlite3_column_text(stmt, 2);

	Horario_setId(pHorario, id);
	Horario_setIdSala(pHorario, idSala);
	Horario_setHora(pHorario, (char*)hora);
}

static void dbReader_getListaHorarios(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	int idSala = sqlite3_column_int(stmt, 1);
	const unsigned char* hora = sqlite3_column_text(stmt, 2);

	eHorario* buffer = Horario_newParam(id, idSala, (char*) hora);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertHorario(eHorario horario){
	char sql_insert[256];
	sprintf(sql_insert, "INSERT INTO Horarios (id, id_sala, horario) VALUES(\"%d\",\"%d\",\"%s\");", horario.id, horario.idSala, horario.hora);
	return database_insertRecordByInt(sql_insert, "Horarios.id", horario.id, DB_DoesHorarioExistById);
}

int DB_updateHorario(eHorario horario, int id){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Horarios SET id_sala=\"%d\", horario=\"%s\" WHERE Horarios.id = \"%d\";", horario.idSala, horario.hora, id);
	return database_updateRecordByInt(sql_update, "Horarios.id", id, DB_DoesHorarioExistById);
}

int DB_deleteHorario(int id){
	return database_deleteRecordByInt("Horarios", "Horarios.id", id, DB_DoesHorarioExistById);
}

int DB_DoesHorarioExistById(int id){
	return database_CheckRecordExistenceByInt("Horarios", "Horarios.id", id);
}
