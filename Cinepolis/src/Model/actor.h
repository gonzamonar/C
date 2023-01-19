
#ifndef MODEL_ACTOR_H_
#define MODEL_ACTOR_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	char nombre[50];
	char apellido[50];
}eActor;

#endif /* MODEL_ACTOR_H_ */

eActor* Actor_newParam(int id, char* nombre, char* apellido);
void Actor_delete(eActor* this);
int Actor_setId(eActor* this, int id);
int Actor_getId(eActor* this, int* dest);
int Actor_setNombre(eActor* this, char* nombre);
int Actor_getNombre(eActor* this, char* dest);
int Actor_setApellido(eActor* this, char* apellido);
int Actor_getApellido(eActor* this, char* dest);

int DB_getActorById(eActor* pActor, int id);
int DB_getListaActores(LinkedList* pListaPeliculas);
int DB_insertActor(eActor actor);
int DB_updateActor(eActor actor, int id);
int DB_deleteActor(int id);
int DB_DoesActorExistById(int id);
int DB_DoesActorExistByFullName(char* name, char* surname);
