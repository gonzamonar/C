
#ifndef MODEL_HORARIO_H_
#define MODEL_HORARIO_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	int idSala;
	char hora[8];
}eHorario;

#endif /* MODEL_HORARIO_H_ */

eHorario* Horario_newParam(int id, int idSala, char* horario);
void Horario_delete(eHorario* this);

int Horario_setId(eHorario* this, int id);
int Horario_getId(eHorario* this, int* dest);
int Horario_setIdSala(eHorario* this, int idSala);
int Horario_getIdSala(eHorario* this, int* dest);
int Horario_setHora(eHorario* this, char* horario);
int Horario_getHora(eHorario* this, char* dest);

int DB_getHorarioById(eHorario* pHorario, int id);
int DB_getListaHorarios(LinkedList* pListaHorarios);
int DB_insertHorario(eHorario horario);
int DB_updateHorario(eHorario horario, int id);
int DB_deleteHorario(int id);
int DB_DoesHorarioExistById(int id);
