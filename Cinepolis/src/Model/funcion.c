
#include "funcion.h"
#include "macros.h"

#include "pelicula.h"
#include "horario.h"
#include "ubicacion.h"
#include "sala.h"

static eFuncion* Funcion_new(void);

//Constructor & Destructor
static eFuncion* Funcion_new(void){
	eFuncion* newFuncion = (eFuncion*) malloc(sizeof(eFuncion));
	if(newFuncion != NULL){
		newFuncion->id = 0;
		newFuncion->idPelicula = 0;
		newFuncion->idSala = 0;
		strcpy(newFuncion->fecha,"");
		strcpy(newFuncion->hora,"");
		newFuncion->subtitulada = 1;
	}
	return newFuncion;
}

eFuncion* Funcion_newParam(int id, int idPelicula, int idSala, char* fecha, char* hora, short subtitulada){
	eFuncion* newFuncion = Funcion_new();
	int argc = 0;
	argc += Funcion_setId(newFuncion, id);
	argc += Funcion_setIdPelicula(newFuncion, idPelicula);
	argc += Funcion_setIdSala(newFuncion, idSala);
	argc += Funcion_setFecha(newFuncion, fecha);
	argc += Funcion_setHora(newFuncion, hora);
	argc += Funcion_setSubtitulada(newFuncion, subtitulada);

	if(argc!=6){
		Funcion_delete(newFuncion);
		newFuncion = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eFuncion película %d, sala %d, fecha %s, hora %s.", idPelicula, idSala, fecha, hora);
		ErrorLog_write(errorLog);
	}
	return newFuncion;
}

void Funcion_delete(eFuncion* this){
	free(this);
}


//Attributes
int Funcion_setId(eFuncion* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_getId(eFuncion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_setIdPelicula(eFuncion* this, int idPelicula){
	int outcome = FAILURE;
	if(this != NULL && idPelicula > 0){
		this->idPelicula = idPelicula;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_getIdPelicula(eFuncion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idPelicula;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_setIdSala(eFuncion* this, int idSala){
	int outcome = FAILURE;
	if(this != NULL && idSala > 0){
		this->idSala = idSala;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_getIdSala(eFuncion* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idSala;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_setFecha(eFuncion* this, char* fecha){
	int outcome = FAILURE;
	if(this != NULL && fecha != NULL){
		strcpy(this->fecha, fecha);
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_getFecha(eFuncion* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->fecha);
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_setHora(eFuncion* this, char* hora){
	int outcome = FAILURE;
	if(this != NULL && hora != NULL){
		strcpy(this->hora, hora);
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_getHora(eFuncion* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->hora);
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_setSubtitulada(eFuncion* this, short subtitulada){
	int outcome = FAILURE;
	if(this != NULL && (subtitulada == 0 || subtitulada == 1)){
		this->subtitulada = subtitulada;
		outcome = SUCCESS;
	}
	return outcome;
}

int Funcion_getSubtitulada(eFuncion* this, short* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->subtitulada;
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getFuncion(sqlite3_stmt* stmt, void* pFuncion);
static void dbReader_getListaFunciones(sqlite3_stmt* stmt, void* list);


int DB_getFuncionById(eFuncion* pFuncion, int id){
	return database_getRecordByInt((void*) pFuncion, "Funciones", "Funciones.id", id, DB_DoesFuncionExistById, dbReader_getFuncion);
}

int DB_getFuncionByFechaSalaHora(eFuncion* pFuncion, char* fecha, int idSala, char* hora){
	int outcome = FAILURE;
	if(DB_DoesFuncionExistByFechaSalaHora(fecha, idSala, hora)){
		outcome = SUCCESS;
		char sql[256];
		sprintf(sql, "SELECT * FROM Funciones WHERE (fecha = \"%s\" AND id_sala = \"%d\" AND hora = \"%s\");", fecha, idSala, hora);
		database_execReader(sql, pFuncion, dbReader_getFuncion);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Select Error - La Funcion con fecha %s, sala Nº%d y hora %s no existe.", fecha, idSala, hora);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int DB_getListaFunciones(LinkedList* pListaFunciones){
	return database_execReader("SELECT * FROM Funciones;", (void*) pListaFunciones, dbReader_getListaFunciones);
}

static void dbReader_getFuncion(sqlite3_stmt* stmt, void* pFuncion){
	int id = sqlite3_column_int(stmt, 0);
	int idPelicula = sqlite3_column_int(stmt, 1);
	int idSala = sqlite3_column_int(stmt, 2);
	const unsigned char* fecha = sqlite3_column_text(stmt, 3);
	const unsigned char* hora = sqlite3_column_text(stmt, 4);
	short subtitulada = (short) sqlite3_column_int(stmt, 5);

	Funcion_setId(pFuncion, id);
	Funcion_setIdPelicula(pFuncion, idPelicula);
	Funcion_setIdSala(pFuncion, idSala);
	Funcion_setFecha(pFuncion, (char*)fecha);
	Funcion_setHora(pFuncion, (char*)hora);
	Funcion_setSubtitulada(pFuncion, subtitulada);
}

static void dbReader_getListaFunciones(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	int idPelicula = sqlite3_column_int(stmt, 1);
	int idSala = sqlite3_column_int(stmt, 2);
	const unsigned char* fecha = sqlite3_column_text(stmt, 3);
	const unsigned char* hora = sqlite3_column_text(stmt, 4);
	short subtitulada = (short) sqlite3_column_int(stmt, 5);

	eFuncion* buffer = Funcion_newParam(id, idPelicula, idSala, (char*)fecha, (char*)hora, subtitulada);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertFuncion(eFuncion funcion){
	int outcome = FAILURE;
	char sql_insert[256];
	sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Funciones (id, id_pelicula,id_sala,fecha,hora,subtitulada) VALUES(\"%d\", \"%d\", \"%d\", \"%s\", \"%s\", \"%d\");",
											funcion.id, funcion.idPelicula, funcion.idSala, funcion.fecha, funcion.hora, funcion.subtitulada);
	if(!DB_DoesFuncionExistByFechaSalaHora(funcion.fecha, funcion.idSala, funcion.hora)){
		database_execNonQuery(sql_insert);
		if(DB_DoesFuncionExistByFechaSalaHora(funcion.fecha, funcion.idSala, funcion.hora)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - Ya existe una Funcion en fecha %s, sala Nº%d y hora %s.", funcion.fecha, funcion.idSala, funcion.hora);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int DB_updateFuncion(eFuncion funcion, int id){
	char sql_update[256];
	sprintf(sql_update, "PRAGMA foreign_keys = on; UPDATE Funciones SET id_pelicula=\"%d\", id_sala=\"%d\", fecha=\"%s\", hora=\"%s\", subtitulada=\"%d\" WHERE Funciones.id = \"%d\";",
									funcion.idPelicula, funcion.idSala, funcion.fecha, funcion.hora, funcion.subtitulada, id);
	return database_updateRecordByInt(sql_update, "Funciones.id", id, DB_DoesFuncionExistById);
}


int DB_deleteFuncion(int id){
	return database_deleteRecordByInt("Funciones", "Funciones.id", id, DB_DoesFuncionExistById);
}


int DB_GetTableFuncionesNextId(){
	return database_GetTableMaxId("Funciones") + 1;
}


int DB_DoesFuncionExistById(int id){
	return database_CheckRecordExistenceByInt("Funciones", "Funciones.id", id);
}


int DB_DoesFuncionExistByFechaSalaHora(char* fecha, int idSala, char* hora){
	char sql[256];
	sprintf(sql, "SELECT 1 FROM Funciones WHERE (fecha = \"%s\" AND id_sala = \"%d\" AND hora = \"%s\");", fecha, idSala, hora);
	return database_GetSingleInt(sql);
}


//Automation

//Proceso de Creación de Funciones
	//1. Seleccionar una Fecha, una Sala y un Horario correspondiente a esa sala.
	//2. Verificar que ese espacio de Función no esté en uso (ocupado con otra Función).
	//3. Seleccionar una Película (Id) y verificar que exista.
	//4. Seleccionar si la Función será subtitulada o no.
	//5. Realizar un Insert a la DB con la Función nueva.
	//6. Crear (DB Insert) las Ubicaciones correspondientes a dicha Función.
	//7. Verificar que se crearon la cantidad correcta de Ubicaciones o crear un Error Log.
void Automatizacion_generarFunciones(int cantidad){
	eFuncion funcion;
	int multiseed = 7*cantidad;

	LinkedList* listaHorarios = ll_newLinkedList();
	DB_getListaHorarios(listaHorarios);
	int maxIndexHorarios = ll_len(listaHorarios)-1;
	int minIdPelicula = database_GetTableMinId("Peliculas");
	int maxIdPelicula = database_GetTableMaxId("Peliculas");


	for(int i=0; i<cantidad;i++){
		system("cls");
		printf("\n\nCreando funcion Nº %4d / %d.\n", i+1, cantidad);
		int retry = 1;
		int conclusion = 0;

		//LOOP HORA, FECHA, SALA
		do{
			int seed = (i+1)*retry*multiseed;

			//1A. FECHA
			randomize_Date(seed, funcion.fecha);

			//1B. HORA + SALA
			int indexHorario = randomize_Integer(seed, 0, maxIndexHorarios);
			eHorario* horario = (eHorario*) ll_get(listaHorarios, indexHorario);
			Funcion_setHora(&funcion, (*horario).hora);
			Funcion_setIdSala(&funcion, (*horario).idSala);

			//2. VERIFICACIÓN
			if(!DB_DoesFuncionExistByFechaSalaHora(funcion.fecha, funcion.idSala, funcion.hora) || retry>50){
				conclusion = 1;
			}
			retry++;
			multiseed += retry;
		}while(conclusion!=1);

		if(retry>50){
			ErrorLog_write("Automation Error (FUNCIONES) - Fecha/Hora Loop Continued: No se encontró una fecha libre para generar una función.");
			continue;
		}

		//RESTART FLAGS
		conclusion = 0;
		retry = 1;

		//LOOP ID PELICULA
		int idPelicula;
		do{
			int seed = (i+1)*retry*multiseed;
			//3A.
			idPelicula = randomize_Integer(seed, minIdPelicula, maxIdPelicula);
			if(DB_DoesPeliculaExistById(idPelicula) || retry > 50){
				conclusion = 1;
			}

			retry++;
			multiseed += retry;
		}while(conclusion!=1);

		if(retry>50){
			ErrorLog_write("Automation Error (FUNCIONES) - ID Pelicula Loop Continued: No se encontró un id de película válido.");
			continue;
		}

		//3B.
		Funcion_setIdPelicula(&funcion, idPelicula);
		//4.
		Funcion_setSubtitulada(&funcion, randomize_Boolean(multiseed*funcion.idPelicula));
		Funcion_setId(&funcion, DB_GetTableFuncionesNextId());
		//5.
		DB_insertFuncion(funcion);

		if(DB_DoesFuncionExistById(funcion.id)){
			//6
			int ubicaciones = DB_GenerarUbicacionesPorFuncion(funcion);
			//7.
			if(ubicaciones != DB_GetCapacidadSala(funcion.idSala)){
				char log[256];
				sprintf(log, "Automation Error (FUNCIONES) - Cantidad de ubicaciones incorrectas (%d) creadas para la Funcion %s, %s, Sala %d.", ubicaciones, funcion.fecha, funcion.hora, funcion.idSala);
				ErrorLog_write(log);
			}
		}else{
			char log[256];
			sprintf(log, "Automation Error (FUNCIONES) - No se pudieron crear las ubicaciones para la Funcion Nº%d - %s, %s, Sala %d.", funcion.id, funcion.fecha, funcion.hora, funcion.idSala);
			ErrorLog_write(log);
		}
	}
	//8
	ll_delete(listaHorarios);
}
