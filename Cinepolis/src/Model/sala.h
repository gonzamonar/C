
#ifndef MODEL_SALA_H_
#define MODEL_SALA_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	char tipoSala[3];
	int asientosPorFila;
	int cantidadFilas;
	short tienePasilloCentral;
}eSala;

#endif /* MODEL_SALA_H_ */

eSala* Sala_newParam(int id, char* tipoSala, int asientosPorFila, int cantidadFilas, short tienePasilloCentral);
void Sala_delete(eSala* this);
int Sala_setId(eSala* this, int id);
int Sala_getId(eSala* this, int* dest);
int Sala_setTipoSala(eSala* this, char* tipoSala);
int Sala_getTipoSala(eSala* this, char* dest);
int Sala_setAsientosPorFila(eSala* this, int asientosPorFila);
int Sala_getAsientosPorFila(eSala* this, int* dest);
int Sala_setCantidadFilas(eSala* this, int cantidadFilas);
int Sala_getCantidadFilas(eSala* this, int* dest);
int Sala_setTienePasilloCentral(eSala* this, short tienePasilloCentral);
int Sala_getTienePasilloCentral(eSala* this, short* dest);


int DB_getSalaById(eSala* pSala, int id);
int DB_getListaSalas(LinkedList* pListaSalas);
int DB_insertSala(eSala sala);
int DB_updateSala(eSala sala, int id);
int DB_deleteSala(int id);
int DB_DoesSalaExistById(int id);
int DB_GetCapacidadSala(int idSala);
void DB_GetTipoSala(char* dest, int idSala);
