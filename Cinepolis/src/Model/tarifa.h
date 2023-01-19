

#ifndef MODEL_TARIFA_H_
#define MODEL_TARIFA_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	char tipoSala[3];
	char tipoEntrada[64];
	float precio;
}eTarifa;

#endif /* MODEL_TARIFA_H_ */


eTarifa* Tarifa_newParam(int id, char* tipoSala, char* tipoEntrada, float precio);
void Tarifa_delete(eTarifa* this);
int Tarifa_setId(eTarifa* this, int id);
int Tarifa_getId(eTarifa* this, int* dest);
int Tarifa_setTipoSala(eTarifa* this, char* tipoSala);
int Tarifa_getTipoSala(eTarifa* this, char* dest);
int Tarifa_setTipoEntrada(eTarifa* this, char* tipoEntrada);
int Tarifa_getTipoEntrada(eTarifa* this, char* dest);
int Tarifa_setPrecio(eTarifa* this, float precio);
int Tarifa_getPrecio(eTarifa* this, float* dest);

int DB_getTarifaById(eTarifa* pTarifa, int id);
int DB_getListaTarifas(LinkedList* pListaTarifas);
int DB_insertTarifa(eTarifa tarifa);
int DB_updateTarifa(eTarifa tarifa, int id);
int DB_deleteTarifa(int id);
int DB_DoesTarifaExistById(int id);
int DB_GetPrecioTarifa(int idTarifa);
float DB_SelectTarifa(int idSala, char* fechaFuncion, int esNinoOAdultoMayor, int esSocio);
