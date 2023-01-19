
#ifndef MODEL_CAST_H_
#define MODEL_CAST_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int idPelicula;
	int idActor;
}eCast;

#endif /* MODEL_CAST_H_ */

eCast* Cast_newParam(int idPelicula, int idActor);
void Cast_delete(eCast* this);
int Cast_setIdPelicula(eCast* this, int id);
int Cast_getIdPelicula(eCast* this, int* dest);
int Cast_setIdActor(eCast* this, int id);
int Cast_getIdActor(eCast* this, int* dest);

int DB_getCastByIds(eCast* pCast, int idPelicula, int idActor);
int DB_getListaCast(LinkedList* pListaCast);
int DB_insertCast(eCast cast);
int DB_deleteCast(int idPelicula, int idActor);
int DB_DoesCastExistByIds(int idPelicula, int idActor);
