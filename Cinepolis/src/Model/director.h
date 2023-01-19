
#ifndef MODEL_DIRECTOR_H_
#define MODEL_DIRECTOR_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	char nombre[50];
}eDirector;

#endif /* MODEL_DIRECTOR_H_ */

eDirector* Director_newParam(int id, char* nombre);
void Director_delete(eDirector* this);
int Director_setId(eDirector* this, int id);
int Director_getId(eDirector* this, int* dest);
int Director_setNombre(eDirector* this, char* nombre);
int Director_getNombre(eDirector* this, char* dest);

int DB_getDirectorById(eDirector* pDirector, int id);
int DB_getDirectorByName(eDirector* pDirector, char* nombre);
int DB_getListaDirectores(LinkedList* pListaPeliculas);
int DB_insertDirector(eDirector director);
int DB_updateDirector(eDirector director, int id);
int DB_deleteDirector(int id);
int DB_DoesDirectorExistById(int id);
int DB_DoesDirectorExistByName(char* name);
