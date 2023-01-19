
#ifndef MODEL_ENTRADA_H_
#define MODEL_ENTRADA_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	float precio;
	int idCompra;
	int idUbicacion;
}eEntrada;

#endif /* MODEL_ENTRADA_H_ */

eEntrada* Entrada_newParam(int id, float precio, int idCompra, int idUbicacion);
void Entrada_delete(eEntrada* this);
int Entrada_setId(eEntrada* this, int id);
int Entrada_getId(eEntrada* this, int* dest);
int Entrada_setPrecio(eEntrada* this, float precio);
int Entrada_getPrecio(eEntrada* this, float* dest);
int Entrada_setIdCompra(eEntrada* this, int idCompra);
int Entrada_getIdCompra(eEntrada* this, int* dest);
int Entrada_setIdUbicacion(eEntrada* this, int idUbicacion);
int Entrada_getIdUbicacion(eEntrada* this, int* dest);

int DB_getEntradaById(eEntrada* pEntrada, int id);
int DB_getListaEntradas(LinkedList* pListaEntradas);
int DB_insertEntrada(eEntrada entrada);
int DB_updateEntrada(eEntrada entrada, int id);
int DB_deleteEntrada(int id);
int DB_GetTableEntradasNextId();
int DB_DoesEntradaExistById(int id);
int DB_DoesEntradaExistByUbicacion(int idUbicacion);
