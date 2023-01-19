
#ifndef MODEL_CLIENTE_H_
#define MODEL_CLIENTE_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	char nombre[64];
	char apellido[64];
	int dni;
	short socio;
}eCliente;

#endif /* MODEL_CLIENTE_H_ */

eCliente* Cliente_newParam(int id, char* nombre, char* apellido, int dni, short socio);
void Cliente_delete(eCliente* this);
int Cliente_setId(eCliente* this, int id);
int Cliente_getId(eCliente* this, int* dest);
int Cliente_setNombre(eCliente* this, char* nombre);
int Cliente_getNombre(eCliente* this, char* dest);
int Cliente_setApellido(eCliente* this, char* apellido);
int Cliente_getApellido(eCliente* this, char* dest);
int Cliente_setDni(eCliente* this, int dni);
int Cliente_getDni(eCliente* this, int* dest);
int Cliente_setSocio(eCliente* this, short socio);
int Cliente_getSocio(eCliente* this, short* dest);
int Cliente_esNinoOMayorDe65(int dni);
int Cliente_esNino(int dni);
int Cliente_esMayorDe65(int dni);

int DB_getClienteById(eCliente* pCliente, int id);
int DB_getClienteByDni(eCliente* pCliente, int dni);
int DB_getClienteSocioValue(int id);
int DB_getListaClientes(LinkedList* pListaClientes);
int DB_insertCliente(eCliente cliente);
int DB_updateCliente(eCliente cliente);
int DB_updateClienteSocioValue(int id, short socio);
int DB_deleteClienteById(int id);
int DB_deleteClienteByDni(int dni);
int DB_DoesClienteExistById(int id);
int DB_DoesClienteExistByDni(int dni);
int DB_DoesClienteExistByFullName(char* name, char* surname);

void automatizacion_Clientes_randomizarSocio();
