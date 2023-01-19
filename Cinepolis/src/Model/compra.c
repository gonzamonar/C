
#include "compra.h"
#include "macros.h"

#include "ubicacion.h"
#include "funcion.h"
#include "cliente.h"
#include "entrada.h"
#include "tarifa.h"


static eCompra* Compra_new(void);

//Constructor & Destructor
static eCompra* Compra_new(void){
	eCompra* newCompra = (eCompra*) malloc(sizeof(eCompra));
	if(newCompra != NULL){
		newCompra->id = 0;
		newCompra->cantidadEntradas = 0;
		newCompra->precioTotal = 0;
		newCompra->idCliente = 0;
	}
	return newCompra;
}

eCompra* Compra_newParam(int id, int cantidadEntradas, float precioTotal, int idCliente){
	eCompra* newCompra = Compra_new();
	int argc = 0;
	argc += Compra_setId(newCompra, id);
	argc += Compra_setCantidadEntradas(newCompra, cantidadEntradas);
	argc += Compra_setPrecioTotal(newCompra, precioTotal);
	argc += Compra_setIdCliente(newCompra, idCliente);

	if(argc!=4){
		Compra_delete(newCompra);
		newCompra = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eCompra entradas %d, precio %.2f, cliente %d.", cantidadEntradas, precioTotal, idCliente);
		ErrorLog_write(errorLog);
	}
	return newCompra;
}

void Compra_delete(eCompra* this){
	free(this);
}


//Attributes
int Compra_setId(eCompra* this, int id){
	int outcome = FAILURE;
	if(this != NULL && id >= 0){
		this->id = id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_getId(eCompra* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->id;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_setCantidadEntradas(eCompra* this, int cantidadEntradas){
	int outcome = FAILURE;
	if(this != NULL && cantidadEntradas >= 0){
		this->cantidadEntradas = cantidadEntradas;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_getCantidadEntradas(eCompra* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->cantidadEntradas;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_setPrecioTotal(eCompra* this, float precioTotal){
	int outcome = FAILURE;
	if(this != NULL && precioTotal >= 0){
		this->precioTotal = precioTotal;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_getPrecioTotal(eCompra* this, float* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->precioTotal;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_setIdCliente(eCompra* this, int idCliente){
	int outcome = FAILURE;
	if(this != NULL && idCliente >= 0){
		this->idCliente = idCliente;
		outcome = SUCCESS;
	}
	return outcome;
}

int Compra_getIdCliente(eCompra* this, int* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		*dest = this->idCliente;
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getCompra(sqlite3_stmt* stmt, void* pCompra);
static void dbReader_getListaCompras(sqlite3_stmt* stmt, void* list);


int DB_getCompraById(eCompra* pCompra, int id){
	return database_getRecordByInt((void*) pCompra, "Compras", "Compras.id", id, DB_DoesCompraExistById, dbReader_getCompra);
}

int DB_getListaCompras(LinkedList* pListaCompras){
	return database_execReader("SELECT * FROM Compras;", (void*) pListaCompras, dbReader_getListaCompras);
}


static void dbReader_getCompra(sqlite3_stmt* stmt, void* pCompra){
	int id = sqlite3_column_int(stmt, 0);
	int cantidadEntradas = sqlite3_column_int(stmt, 1);
	float precioTotal = (float) sqlite3_column_double(stmt, 2);
	int idCliente = sqlite3_column_int(stmt, 3);

	Compra_setId(pCompra, id);
	Compra_setCantidadEntradas(pCompra, cantidadEntradas);
	Compra_setPrecioTotal(pCompra, precioTotal);
	Compra_setIdCliente(pCompra, idCliente);
}

static void dbReader_getListaCompras(sqlite3_stmt* stmt, void* list){
	int id = sqlite3_column_int(stmt, 0);
	int cantidadEntradas = sqlite3_column_int(stmt, 1);
	float precioTotal = (float) sqlite3_column_double(stmt, 2);
	int idCliente = sqlite3_column_int(stmt, 3);

	eCompra* buffer = Compra_newParam(id, cantidadEntradas, precioTotal, idCliente);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertCompra(eCompra compra){
	char sql_insert[256];
	sprintf(sql_insert, "PRAGMA foreign_keys = on; INSERT INTO Compras (id, cantidad_entradas, precio_total, id_cliente) VALUES(\"%d\",\"%d\",\"%.2f\",\"%d\");", compra.id, compra.cantidadEntradas, compra.precioTotal, compra.idCliente);
	return database_execNonQuery(sql_insert);
}

int DB_updateCompra(eCompra compra, int id){
	char sql_update[256];
	sprintf(sql_update, "PRAGMA foreign_keys = on; UPDATE Compras SET cantidad_entradas=\"%d\", precio=\"%.2f\", id_cliente=\"%d\" WHERE Compras.id = \"%d\";", compra.cantidadEntradas, compra.precioTotal, compra.idCliente, id);
	return database_updateRecordByInt(sql_update, "Compras.id", id, DB_DoesCompraExistById);
}

int DB_deleteCompra(int id){
	return database_deleteRecordByInt("Compras", "Compras.id", id, DB_DoesCompraExistById);
}

int DB_DoesCompraExistById(int id){
	return database_CheckRecordExistenceByInt("Compras", "Compras.id", id);
}

int DB_GetTableComprasNextId(){
	return database_GetTableMaxId("Compras") + 1;
}



//Proceso de Automatización de Compras
	//1. Seleccionar un Cliente.
	//2. Seleccionar una Función.
	//3. Seleccionar una Ubicación.
	//4. Calcular el precio según Tipo de Entrada (Tarifa) + Descuento de Socio.
	//5. Construir y agregar la Entrada actual a la Lista de Entradas.
	//6. DB Update de disponibilidad de la Ubicación a 2 (reservada).
	//7. Repetir el Do-Loop() si el Cliente quiere realizar otra compra.
	//8. Cerrar el proceso de Compra:
		//A. DB Insert con la Compra.
		//B. DB Insert de las Entradas en la Lista.
		//C. DB Update de las Ubicaciones de las Entradas a 0 (ocupadas).
		//D. Limpiar la lista de Entradas del Proceso de Compra.
void Automatizacion_generarCompras(int cantidad){
	LinkedList* listaEntradas = ll_newLinkedList();
	LinkedList* listaUbicaciones = ll_newLinkedList();
	int minIdCliente = database_GetTableMinId("Clientes");
	int maxIdCliente = database_GetTableMaxId("Clientes");
	int minIdFuncion = database_GetTableMinId("Funciones");
	int maxIdFuncion = database_GetTableMaxId("Funciones");
	int seed = cantidad;

	for(int i=0; i<cantidad;i++){
		system("cls");
		printf("\n\nSimulando compra Nº %4d / %d.\n", i+1, cantidad);
		int ubicacionesLibres = DB_GetCantidadUbicacionesLibres();
		if(ubicacionesLibres > 0){
			eCompra compra;
			eCliente cliente;
			eFuncion funcion;
			seed *= (i+1)*(ubicacionesLibres/cantidad);
			int finCompra = 0;
			int endloop = 0;
			int cantidadEntradas = 0;
			float precioTotal = 0;
			int entradaNextId = DB_GetTableEntradasNextId();

			Compra_setId(&compra, DB_GetTableComprasNextId());
			//1.
			do{
				int idCliente = randomize_Integer(seed*compra.id, minIdCliente, maxIdCliente);
				if(DB_DoesClienteExistById(idCliente)){
					DB_getClienteById(&cliente, idCliente);
					Compra_setIdCliente(&compra, cliente.id);
					endloop = 1;
				}
			}while(endloop!=1);

			do{
				if(DB_GetCantidadUbicacionesLibres() != 0){
					float precioEntrada = 0;
					cantidadEntradas++;
					seed += precioTotal;
					seed *= cantidadEntradas;
					endloop = 0;
					int round = 10;
					//2.
					do{
						int idFuncion = randomize_Integer(seed*round, minIdFuncion, maxIdFuncion);
						if(DB_DoesFuncionExistById(idFuncion) && DB_GetCantidadUbicacionesLibresPorFuncion(idFuncion)){
							DB_getFuncionById(&funcion, idFuncion);
							endloop = 1;
						}
						round++;
					}while(endloop!=1);

					seed += compra.idCliente;
					seed += funcion.idPelicula;

					//3.
					DB_getListaUbicacionesDisponiblesPorFuncion(listaUbicaciones, funcion.id);
					int maxIndexUbicaciones = ll_len(listaUbicaciones)-1;
					int indexUbicacion= randomize_Integer(seed, 0, maxIndexUbicaciones);
					eUbicacion* ubicacion = (eUbicacion*) ll_get(listaUbicaciones, indexUbicacion);


					//4.
					precioEntrada = DB_SelectTarifa(funcion.idSala, funcion.fecha, Cliente_esNinoOMayorDe65(cliente.dni), cliente.socio);
					precioTotal += precioEntrada;

					//5
					eEntrada* entrada = Entrada_newParam(entradaNextId, precioEntrada, compra.id, (*ubicacion).id);
					ll_add(listaEntradas, (void*)entrada);
					entradaNextId++;

					//6
					Ubicacion_setDisponible(ubicacion, 2);
					DB_updateDisponibilidadUbicacion((*ubicacion).id, 2);

				}else{
					ErrorLog_write("Automation Error (COMPRAS) - Todas las Ubicaciones ya fueron vendidas.");
					printf("\n\n Ya no quedan ubicaciones disponibles para ninguna Función.\n");
					finCompra = 1;
				}

				Compra_setCantidadEntradas(&compra, cantidadEntradas);
				Compra_setPrecioTotal(&compra, precioTotal);
				ll_clear(listaUbicaciones);

				finCompra = randomize_Boolean(seed);
			}while(finCompra!=1);

			//8A.
			DB_insertCompra(compra);

			int len = ll_len(listaEntradas);
			for(int i=0; i<len; i++){
				//8B.
				eEntrada* entrada = ll_get(listaEntradas,i);
				DB_insertEntrada(*entrada);
				//8C.
				DB_updateDisponibilidadUbicacion((*entrada).idUbicacion, 0);
				free(entrada);
			}

			//8D.
			ll_clear(listaEntradas);
		}else{
			ErrorLog_write("Automation Error (COMPRAS) - Todas las Ubicaciones ya fueron vendidas.");
			printf("\n\n  Localidades Agotadas: \n");
			printf("  Ya no quedan ubicaciones disponibles para ninguna Función.\n\n");
			break;
		}
	}

	ll_delete(listaEntradas);
	ll_delete(listaUbicaciones);
}























