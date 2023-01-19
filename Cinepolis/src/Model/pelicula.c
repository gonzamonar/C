
#include "pelicula.h"
#include "director.h"
#include "macros.h"

static ePelicula* Pelicula_new(void);

//Constructor & Destructor
static ePelicula* Pelicula_new(void){
	ePelicula* newPelicula = (ePelicula*) malloc(sizeof(ePelicula));
	if(newPelicula != NULL){
		newPelicula->id = 0;
		strcpy(newPelicula->titulo,"");
		newPelicula->year = 0;
		newPelicula->duracion = 0;
		newPelicula->idDirector = 0;
		newPelicula->proyectandose = 0;
	}
	return newPelicula;
}

ePelicula* Pelicula_newParam(int id, char* titulo, int year, int duracion, int idDirector, short proyectandose){
	ePelicula* newPelicula = Pelicula_new();
	int argc = 0;
	argc += Pelicula_setId(newPelicula, id);
	argc += Pelicula_setTitulo(newPelicula, titulo);
	argc += Pelicula_setYear(newPelicula, year);
	argc += Pelicula_setDuracion(newPelicula, duracion);
	argc += Pelicula_setIdDirector(newPelicula, idDirector);
	argc += Pelicula_setProyectandose(newPelicula, proyectandose);

	if(argc!=6){
		Pelicula_delete(newPelicula);
		newPelicula = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto ePelicula %d %s.", id, titulo);
		ErrorLog_write(errorLog);
	}
	return newPelicula;
}

void Pelicula_delete(ePelicula* this){
	free(this);
}


//Attributes
int Pelicula_setId(ePelicula* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id > 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_getId(ePelicula* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_setTitulo(ePelicula* this, char* titulo){
	int outcome = FAILURE;
	if(this != NULL && titulo != NULL){
		strcpy(this->titulo, titulo);
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_getTitulo(ePelicula* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->titulo);
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_setYear(ePelicula* this, int year){
	int outcome = FAILURE;
	if(this != NULL && year > 0){
		this->year = year;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_getYear(ePelicula* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->year;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_setDuracion(ePelicula* this, int duracion){
	int outcome = FAILURE;
	if(this != NULL && duracion >= 0){
		this->duracion = duracion;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_getDuracion(ePelicula* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->duracion;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_setIdDirector(ePelicula* this, int idDirector){
	int outcome = FAILURE;
	if(this != NULL && idDirector > 0){
		this->idDirector = idDirector;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_getIdDirector(ePelicula* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idDirector;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_setProyectandose(ePelicula* this, short proyectandose){
	int outcome = FAILURE;
	if(this != NULL && (proyectandose == 0 || proyectandose == 1)){
		this->proyectandose = proyectandose;
		outcome = SUCCESS;
	}
	return outcome;
}

int Pelicula_getProyectandose(ePelicula* this, short* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->proyectandose;
		outcome = SUCCESS;
	}
	return outcome;
}




//Database Operations
static void dbReader_getPelicula(sqlite3_stmt* stmt, void* pPelicula);
static void dbReader_getListaPeliculas(sqlite3_stmt* stmt, void* list);

int DB_getPeliculaById(ePelicula* pPelicula, int id){
	return database_getRecordByInt((void*) pPelicula, "Peliculas", "Peliculas.id", id, DB_DoesPeliculaExistById, dbReader_getPelicula);
}

int DB_getPeliculaByTitle(ePelicula* pPelicula, char* title){
	return database_getRecordByStr((void*) pPelicula, "Peliculas", "Peliculas.titulo", title, DB_DoesPeliculaExistByTitle, dbReader_getPelicula);
}

void DB_getTituloDePeliculaById(char* dest, int id){
	char sql_query[256];
	sprintf(sql_query, "SELECT titulo FROM Peliculas WHERE id = %d;", id);
	database_GetSingleStr(sql_query, dest);
}

int DB_getListaPeliculas(LinkedList* pListaPeliculas){
	return database_execReader("SELECT * FROM Peliculas;", (void*) pListaPeliculas, dbReader_getListaPeliculas);
}

static void dbReader_getPelicula(sqlite3_stmt* stmt, void* pPelicula){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* titulo = sqlite3_column_text(stmt, 1);
	int year = sqlite3_column_int(stmt, 2);
	int duracion = sqlite3_column_int(stmt, 3);
	int idDirector = sqlite3_column_int(stmt, 4);
	short proyectandose = (short) sqlite3_column_int(stmt, 5);

	Pelicula_setId(pPelicula, id);
	Pelicula_setTitulo(pPelicula, (char*)titulo);
	Pelicula_setYear(pPelicula, year);
	Pelicula_setDuracion(pPelicula, duracion);
	Pelicula_setIdDirector(pPelicula, idDirector);
	Pelicula_setProyectandose(pPelicula, proyectandose);
}

static void dbReader_getListaPeliculas(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* titulo = sqlite3_column_text(stmt, 1);
	int year = sqlite3_column_int(stmt, 2);
	int duracion = sqlite3_column_int(stmt, 3);
	int idDirector = sqlite3_column_int(stmt, 4);
	short proyectandose = (short) sqlite3_column_int(stmt, 5);

	ePelicula* buffer = Pelicula_newParam(id, (char*)titulo, year, duracion, idDirector, proyectandose);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}


int DB_insertPelicula(ePelicula pelicula){
	int outcome = FAILURE;
	if(DB_DoesDirectorExistById(pelicula.idDirector)){
		char sql_insert[256];
		sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Peliculas (titulo,year,duracion,id_director,proyectandose) VALUES(\"%s\", \"%d\", \"%d\", \"%d\", \"%d\");",
								pelicula.titulo, pelicula.year, pelicula.duracion, pelicula.idDirector, pelicula.proyectandose);
		outcome = database_insertRecordByStr(sql_insert, "Pelicula.titulo", pelicula.titulo, DB_DoesPeliculaExistByTitle);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - La película \"%s\" no cumple el FK Constraint al insertar un registro con IdDirector = \"%d\"", pelicula.titulo, pelicula.idDirector);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int DB_updatePelicula(ePelicula pelicula, int id){
	int outcome = FAILURE;
	if(DB_DoesDirectorExistById(pelicula.idDirector)){
		char sql_update[256];
		sprintf(sql_update, "PRAGMA foreign_keys = on; UPDATE Peliculas SET titulo=\"%s\", year=\"%d\", duracion=\"%d\", id_director=\"%d\", proyectandose=\"%d\" WHERE Peliculas.id = \"%d\";",
											pelicula.titulo, pelicula.year, pelicula.duracion, pelicula.idDirector, pelicula.proyectandose, id);
		outcome = database_updateRecordByInt(sql_update, "Peliculas.id", id, DB_DoesPeliculaExistById);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Update Error - La película \"%s\" no cumple el FK Constraint al actualizar un registro con IdDirector = \"%d\"", pelicula.titulo, pelicula.idDirector);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int DB_deletePelicula(int id){
	return database_deleteRecordByInt("Peliculas", "Peliculas.id", id, DB_DoesPeliculaExistById);
}

int DB_DoesPeliculaExistById(int id){
	return database_CheckRecordExistenceByInt("Peliculas", "Peliculas.id", id);
}

int DB_DoesPeliculaExistByTitle(char* title){
	return database_CheckRecordExistenceByStr("Peliculas", "Peliculas.titulo", title);
}


//Automation
static void* mapPelicula_randomizarDuracion(void* element);
static void* mapPelicula_randomizarProyectandose(void* element);
static void automatizacion_mapearPeliculas(void*(*pFuncMapear)(void*));

void automatizacion_Peliculas_randomizarDuracion(){
	automatizacion_mapearPeliculas(mapPelicula_randomizarDuracion);
}

void automatizacion_Peliculas_randomizarProyectandose(){
	automatizacion_mapearPeliculas(mapPelicula_randomizarProyectandose);
}

static void automatizacion_mapearPeliculas(void*(*pFuncMapear)(void*)){
	LinkedList* listaPeliculas = ll_newLinkedList();

	if(listaPeliculas!=NULL){
		DB_getListaPeliculas(listaPeliculas);
		listaPeliculas = ll_map(listaPeliculas, pFuncMapear);

		int len = ll_len(listaPeliculas);
		for(int i=0; i<len; i++)
		{
			ePelicula* pPelicula = ll_get(listaPeliculas, i);
			if(pPelicula != NULL){
				DB_updatePelicula(*pPelicula, (*pPelicula).id);
			}
		}
		ll_delete(listaPeliculas);
	}
}

static void* mapPelicula_randomizarDuracion(void* element){
	int duration;
	int min = 90;
	int max = 200;
	int id;
	int idDirector;

	ePelicula* new_element = (ePelicula*) element;
	Pelicula_getId(new_element, &id);
	Pelicula_getIdDirector(new_element, &idDirector);
	int i = (idDirector+1)*(id+1);
	duration = randomize_Integer(i, min, max);

	Pelicula_setDuracion(new_element, duration);
	return (void*) new_element;
}

static void* mapPelicula_randomizarProyectandose(void* element){
	int proyectandose;
	int idDirector;
	int duracion;

	ePelicula* new_element = (ePelicula*) element;
	Pelicula_getIdDirector(new_element, &idDirector);
	Pelicula_getDuracion(new_element, &duracion);
	int i = (idDirector+1)*(duracion+1);
	proyectandose = randomize_Boolean(i);

	Pelicula_setProyectandose(new_element, proyectandose);
	return (void*) new_element;
}
