
#include "cliente.h"
#include "macros.h"

#include <ctype.h>


static eCliente* Cliente_new(void);

//Constructor & Destructor
static eCliente* Cliente_new(void){
	eCliente* newCliente = (eCliente*) malloc(sizeof(eCliente));
	if(newCliente != NULL){
		newCliente->dni = 0;
		strcpy(newCliente->nombre,"");
		strcpy(newCliente->apellido,"");
		newCliente->socio = 0;
	}
	return newCliente;
}

eCliente* Cliente_newParam(int id, char* nombre, char* apellido, int dni, short socio){
	eCliente* newCliente = Cliente_new();
	int argc = 0;
	argc += Cliente_setId(newCliente, id);
	argc += Cliente_setNombre(newCliente, nombre);
	argc += Cliente_setApellido(newCliente, apellido);
	argc += Cliente_setDni(newCliente, dni);
	argc += Cliente_setSocio(newCliente, socio);

	if(argc!=5){
		Cliente_delete(newCliente);
		newCliente = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eCliente %s %s (DNI: %d).", nombre, apellido, dni);
		ErrorLog_write(errorLog);
	}
	return newCliente;
}

void Cliente_delete(eCliente* this){
	free(this);
}


//Attributes
int Cliente_setId(eCliente* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id >= 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_getId(eCliente* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_setNombre(eCliente* this, char* nombre){
	int outcome = FAILURE;
	if(this != NULL && nombre != NULL){
		strcpy(this->nombre, nombre);
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_getNombre(eCliente* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->nombre);
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_setApellido(eCliente* this, char* apellido){
	int outcome = FAILURE;
	if(this != NULL && apellido != NULL){
		strcpy(this->apellido, apellido);
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_getApellido(eCliente* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->apellido);
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_setDni(eCliente* this, int dni){
	int outcome = FAILURE;
	if(this != NULL && dni > 0){
		this->dni = dni;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_getDni(eCliente* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->dni;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_setSocio(eCliente* this, short socio){
	int outcome = FAILURE;
	if(this != NULL && (socio == 0 || socio == 1)){
		this->socio = socio;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_getSocio(eCliente* this, short* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->socio;
		outcome = SUCCESS;
	}
	return outcome;
}

int Cliente_esNinoOMayorDe65(int dni){
	return Cliente_esNino(dni) || Cliente_esMayorDe65(dni);
}

int Cliente_esNino(int dni){
	return (dni > 70000000 && dni <80000000);
}

int Cliente_esMayorDe65(int dni){
	return (dni < 15000000);
}

//Database Operations
static void dbReader_getCliente(sqlite3_stmt* stmt, void* pCliente);
static void dbReader_getListaClientes(sqlite3_stmt* stmt, void* list);

int DB_getClienteById(eCliente* pCliente, int id){
	return database_getRecordByInt((void*) pCliente, "Clientes", "Clientes.id", id, DB_DoesClienteExistById, dbReader_getCliente);
}

int DB_getClienteByDni(eCliente* pCliente, int dni){
	return database_getRecordByInt((void*) pCliente, "Clientes", "Clientes.dni", dni, DB_DoesClienteExistByDni, dbReader_getCliente);
}

int DB_getClienteSocioValue(int id){
	char sql_query[256];
	sprintf(sql_query, "SELECT socio FROM Clientes WHERE id = %d;", id);
	return database_GetSingleInt(sql_query);
}

int DB_getListaClientes(LinkedList* pListaClientes){
	return database_execReader("SELECT * FROM Clientes;", (void*) pListaClientes, dbReader_getListaClientes);
}

static void dbReader_getCliente(sqlite3_stmt* stmt, void* pCliente){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* nombre = sqlite3_column_text(stmt, 1);
	const unsigned char* apellido = sqlite3_column_text(stmt, 2);
	int dni = sqlite3_column_int(stmt, 3);
	int socio = sqlite3_column_int(stmt, 4);

	Cliente_setId(pCliente, id);
	Cliente_setNombre(pCliente, (char*)nombre);
	Cliente_setApellido(pCliente, (char*)apellido);
	Cliente_setDni(pCliente, dni);
	Cliente_setSocio(pCliente, (short)socio);
}

static void dbReader_getListaClientes(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	const unsigned char* nombre = sqlite3_column_text(stmt, 1);
	const unsigned char* apellido = sqlite3_column_text(stmt, 2);
	int dni = sqlite3_column_int(stmt, 3);
	int socio = sqlite3_column_int(stmt, 4);

	eCliente* buffer = Cliente_newParam(id, (char*)nombre, (char*)apellido, dni, (short)socio);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertCliente(eCliente cliente){
	char sql_insert[256];
	sprintf(sql_insert, "INSERT INTO Clientes (nombre, apellido, dni, socio) VALUES(\"%s\",\"%s\",\"%d\",\"%d\");", cliente.nombre, cliente.apellido, cliente.dni, cliente.socio);
	return database_insertRecordByInt(sql_insert, "Clientes.dni", cliente.dni, DB_DoesClienteExistByDni);
}

int DB_updateCliente(eCliente cliente){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Clientes SET nombre=\"%s\", apellido=\"%s\", dni=\"%d\", socio=\"%d\" WHERE Clientes.id = \"%d\";", cliente.nombre, cliente.apellido, cliente.dni, cliente.socio, cliente.id);
	return database_updateRecordByInt(sql_update, "Clientes.id", cliente.id, DB_DoesClienteExistById);
}

int DB_updateClienteSocioValue(int id, short socio){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Clientes SET socio=\"%d\" WHERE Clientes.id = \"%d\";", socio, id);
	return database_updateRecordByInt(sql_update, "Clientes.id",id, DB_DoesClienteExistById);
}

int DB_deleteClienteById(int id){
	return database_deleteRecordByInt("Clientes", "Clientes.id", id, DB_DoesClienteExistById);
}

int DB_deleteClienteByDni(int dni){
	return database_deleteRecordByInt("Clientes", "Clientes.dni", dni, DB_DoesClienteExistByDni);
}

int DB_ClienteEsSocio(int id){
	char sql[256];
	sprintf(sql, "SELECT socio FROM Clientes WHERE id = \"%d\";", id);
	return database_GetSingleInt(sql);
}

int DB_DoesClienteExistById(int id){
	return database_CheckRecordExistenceByInt("Clientes", "Clientes.id", id);
}

int DB_DoesClienteExistByDni(int dni){
	return database_CheckRecordExistenceByInt("Clientes", "Clientes.dni", dni);
}

int DB_DoesClienteExistByFullName(char* name, char* surname){
	return database_CheckRecordExistenceByStrAndStr("Clientes", "Clientes.nombre", name, "Clientes.apellido", surname);
}


static void automatizacion_mapearPeliculas(void*(*pFuncMapear)(void*));
static void* mapCliente_randomizarSocio(void* element);

void automatizacion_Clientes_randomizarSocio(){
	automatizacion_mapearPeliculas(mapCliente_randomizarSocio);
}

static void automatizacion_mapearPeliculas(void*(*pFuncMapear)(void*)){
	LinkedList* listaClientes = ll_newLinkedList();

	if(listaClientes!=NULL){
		DB_getListaClientes(listaClientes);
		listaClientes = ll_map(listaClientes, pFuncMapear);

		int len = ll_len(listaClientes);
		for(int i=0; i<len; i++)
		{
			eCliente* pCliente = ll_get(listaClientes, i);
			if(pCliente != NULL){
				DB_updateCliente(*pCliente);
			}
		}
		ll_delete(listaClientes);
	}
}

static void* mapCliente_randomizarSocio(void* element){
	int id;
	int dni;
	int socio;

	eCliente* new_element = (eCliente*) element;
	Cliente_getId(new_element, &id);
	Cliente_getDni(new_element, &dni);
	int i = (dni+1)*(id+1);
	socio = randomize_Boolean(i);

	Cliente_setSocio(new_element, socio);
	return (void*) new_element;
}
