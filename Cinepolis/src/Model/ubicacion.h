/*
 * asiento.h
 *
 *  Created on: 3 ene. 2023
 *      Author: GM
 */

#ifndef MODEL_ASIENTO_H_
#define MODEL_ASIENTO_H_

#include "../My_Libraries/LinkedList.h"
#include "funcion.h"

typedef struct{
	int id;
	char fila;
	int numero;
	short disponible;
	int idFuncion;
}eUbicacion;

#endif /* MODEL_ASIENTO_H_ */


eUbicacion* Ubicacion_newParam(int id, char fila, int numero, short disponible, int idFuncion);
void Ubicacion_delete(eUbicacion* this);
int Ubicacion_setId(eUbicacion* this, int id);
int Ubicacion_getId(eUbicacion* this, int* dest);
int Ubicacion_setFila(eUbicacion* this, char fila);
int Ubicacion_getFila(eUbicacion* this, char* dest);
int Ubicacion_setNumero(eUbicacion* this, int numero);
int Ubicacion_getNumero(eUbicacion* this, int* dest);
int Ubicacion_setDisponible(eUbicacion* this, int disponible);
int Ubicacion_getDisponible(eUbicacion* this, int* dest);
int Ubicacion_setFuncion(eUbicacion* this, int idFuncion);
int Ubicacion_getFuncion(eUbicacion* this, int* dest);

int UbicacionLL_getId(LinkedList* listaUbicaciones, char fila, int numero);
int UbicacionLL_getDisponibilidad(LinkedList* listaUbicaciones, char fila, int numero);
int UbicacionLL_cambiarDisponibilidad(LinkedList* listaUbicaciones, char fila, int numero, short disponibilidad);
int Ubicacion_parser(char* ubicacion, char* pFila, int* pNumero);

int DB_getUbicacion(eUbicacion* pUbicacion, int id);
int DB_getListaUbicaciones(LinkedList* pListaUbicaciones);
int DB_getListaUbicacionesPorFuncion(LinkedList* pListaUbicaciones, int idFuncion);
int DB_getListaUbicacionesDisponiblesPorFuncion(LinkedList* pListaUbicaciones, int idFuncion);
int DB_insertUbicacion(eUbicacion ubicacion);
int DB_updateUbicacion(eUbicacion ubicacion, int id);
int DB_updateDisponibilidadUbicacion(int idUbicacion, int disponible);
int DB_deleteUbicacion(int id);
int DB_DoesUbicacionExistById(int id);
int DB_GetCantidadUbicacionesLibres();
int DB_GetCantidadUbicacionesLibresPorFuncion(int idFuncion);
int DB_GenerarUbicacionesPorFuncion(eFuncion funcion);
