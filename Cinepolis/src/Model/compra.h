
#ifndef MODEL_COMPRA_H_
#define MODEL_COMPRA_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	int cantidadEntradas;
	float precioTotal;
	int idCliente;
}eCompra;

#endif /* MODEL_COMPRA_H_ */


eCompra* Compra_newParam(int id, int cantidadEntradas, float precioTotal, int idCliente);
void Compra_delete(eCompra* this);
int Compra_setId(eCompra* this, int id);
int Compra_getId(eCompra* this, int* dest);
int Compra_setCantidadEntradas(eCompra* this, int cantidadEntradas);
int Compra_getCantidadEntradas(eCompra* this, int* dest);
int Compra_setPrecioTotal(eCompra* this, float precioTotal);
int Compra_getPrecioTotal(eCompra* this, float* dest);
int Compra_setIdCliente(eCompra* this, int idCliente);
int Compra_getIdCliente(eCompra* this, int* dest);


int DB_getCompraById(eCompra* pCompra, int id);
int DB_getListaCompras(LinkedList* pListaCompras);
int DB_insertCompra(eCompra compra);
int DB_updateCompra(eCompra compra, int id);
int DB_deleteCompra(int id);
int DB_DoesCompraExistById(int id);
int DB_GetTableComprasNextId();

void Automatizacion_generarCompras(int cantidad);
