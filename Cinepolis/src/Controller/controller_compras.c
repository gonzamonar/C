

#include "controller_compras.h"

#include "listar_objetos.h"
#include "../DataBase/database.h"
#include "../IO_Libraries/console.h"
#include "../IO_Libraries/IO_num.h"
#include "../IO_Libraries/IO_str.h"
#include "../View/creation_interface.h"
#include "../View/user_interface.h"
#include "../View/decoration.h"
#include "../Controller/session.h"

#include "../Model/macros.h"
#include "../Model/admin.h"
#include "../Model/cliente.h"
#include "../Model/sala.h"
#include "../Model/funcion.h"
#include "../Model/ubicacion.h"
#include "../Model/compra.h"
#include "../Model/entrada.h"
#include "../Model/tarifa.h"


static void compra_seleccionarCliente(eCompra* compra);
static void compra_seleccionarFuncion(LinkedList* carritoCompra, eCompra* compra);
static void compra_seleccionarUbicacion(LinkedList* carritoCompra, eCompra* compra, int idFuncion);
static void compra_agregarEntradaAlCarrito(LinkedList* carritoCompra, eCompra* compra, eFuncion funcion, int idUbicacion);
static float compra_seleccionarTarifa(eFuncion funcion, int idCliente);
static int compra_revisionCompra(LinkedList* carritoCompra, eCompra* compra);
static void compra_finalizarCompra(LinkedList* carritoCompra, eCompra* compra);


//Proceso de Compra
	//8. Cerrar el proceso de Compra:
		//A. DB Insert con la Compra.
		//B. DB Insert de las Entradas en la Lista.
		//C. DB Update de las Ubicaciones de las Entradas a 0 (ocupadas).
void controller_procesarCompra(){
	LinkedList* carritoCompra = ll_newLinkedList();

	system("cls");
	if(DB_GetCantidadUbicacionesLibres() > 0){
		eCompra compra;
		Compra_setId(&compra, DB_GetTableComprasNextId());
		Compra_setCantidadEntradas(&compra, 0);
		Compra_setPrecioTotal(&compra, 0);
		Compra_setIdCliente(&compra, 0);

		compra_seleccionarCliente(&compra);
		if(compra.idCliente!=0){
			compra_seleccionarFuncion(carritoCompra, &compra);
			if(ll_len(carritoCompra)>0){
				if(compra_revisionCompra(carritoCompra, &compra)){
					compra_finalizarCompra(carritoCompra, &compra);
				}
				pause();
			}
		}
	}else{
		ErrorLog_write("Error de Alta (COMPRAS) - Todas las Ubicaciones ya fueron vendidas.");
		printf("\n\n  Localidades Agotadas: \n");
		printf("  Ya no quedan ubicaciones disponibles para ninguna Función.\n\n");
	}

	ll_delete(carritoCompra);
}


static void compra_seleccionarCliente(eCompra* compra){
	int exit_flag = 0;
	int idCliente;
	int maxID = database_GetTableMaxId("Clientes");

	do{
		system("cls");
		char confirm;
		DB_listarClientes();
		if(IO_getInteger(&idCliente, "\n   Ingrese el ID del Cliente (0 para Cancelar la Compra) : ", "\n     ID inválido. ", 0, maxID, 3)){
			if(idCliente == 0){
				exit_flag = 1;
			}else{
				if(DB_DoesClienteExistById(idCliente)){
					system("cls");
					DB_listarCliente(idCliente);
					IO_getConfirm(&confirm, "\n   ¿Confirma la selección de Cliente? [S/N] : ", "   Opción inválida.", 3);
					if(confirm == 'S'){
						Compra_setIdCliente(compra, idCliente);
						exit_flag = 1;
					}
				}else{
					printf("\n  El ID seleccionado no corresponde a un Cliente activo, inténtelo nuevamente.\n");
					pause();
				}
			}
		}
	}while(exit_flag!=1);
}

static void compra_seleccionarFuncion(LinkedList* carritoCompra, eCompra* compra){
	int exit_flag = 0;
	int idFuncion;
	int maxID = database_GetTableMaxId("Funciones");

	//CODEADO ACTUAL
	do{
		system("cls");
		decoration_printCarritoCompra(carritoCompra);
		DB_listarFunciones();
		//2. Seleccionar FUNCION
		if(IO_getInteger(&idFuncion, "\n   Ingrese el ID de la Función o 0 para Ir a Finalizar la Compra : ", "\n     ID inválido. ", 0, maxID, 3)){
			if(idFuncion == 0){
				exit_flag = 1;
			}else{
				if(DB_DoesFuncionExistById(idFuncion) && DB_GetCantidadUbicacionesLibresPorFuncion(idFuncion)>0){
					//3. Seleccionar UBICACION
					compra_seleccionarUbicacion(carritoCompra, compra, idFuncion);
				}else{
					printf("\n   La Función no está disponible o está completa. Inténtelo nuevamente.");
					pause();
				}
			}
		}
	}while(exit_flag!=1);
}

static void compra_seleccionarUbicacion(LinkedList* carritoCompra, eCompra* compra, int idFuncion){
	LinkedList* listaUbicaciones = ll_newLinkedList();

	eFuncion funcion;
	eSala sala;
	DB_getFuncionById(&funcion, idFuncion);
	DB_getSalaById(&sala, funcion.idSala);
	DB_getListaUbicacionesPorFuncion(listaUbicaciones, funcion.id);

	int seleccionTerminada;
	do{
		char seat[5];
		system("cls");
		seleccionTerminada = 0;
		decoration_printCarritoCompra(carritoCompra);
		DB_listarFuncion(idFuncion);
		if(decoration_printUbicacionesSala(listaUbicaciones, sala)){
			printf("\n     [Para seleccionar otra Función ingrese 'exit']");
			if(IO_getUbicacion(seat, 5)){
				if(strcmp(seat,"exit")!=0 && strcmp(seat,"EXIT")!=0){
					char confirm;
					char fila = ' ';
					int numero = 0;
					Ubicacion_parser(seat, &fila, &numero);
					if(numero < 1 || numero > sala.asientosPorFila){
						printf("\n  El número de asiento ingresado no existe.");
						pause();
					}else if(fila < 'A' || fila > ('A'+sala.cantidadFilas-1)){
						printf("\n  El orden de fila ingresada no existe.");
						pause();
					}else{
						int disponible = UbicacionLL_getDisponibilidad(listaUbicaciones, fila, numero);
						if(disponible==1 && UbicacionLL_cambiarDisponibilidad(listaUbicaciones, fila, numero, 2)){
							system("cls");
							DB_listarFuncion(idFuncion);
							decoration_printUbicacionesSala(listaUbicaciones, sala);
							IO_getConfirm(&confirm, "\n   ¿Desea confirmar su selección? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
							if(confirm == 'S'){
								compra_agregarEntradaAlCarrito(carritoCompra, compra, funcion, UbicacionLL_getId(listaUbicaciones, fila, numero));
							}else{
								UbicacionLL_cambiarDisponibilidad(listaUbicaciones, fila, numero, 1);
							}

							IO_getConfirm(&confirm, "\n   ¿Desea elegir más asientos para la misma función? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
							if(confirm != 'S'){
								seleccionTerminada = 1;
							}
						}else if(disponible==0){
							printf("\n  Esa ubicación no está disponible.\n");
							pause();
						}else if(disponible==2){
							printf("\n  Esa ubicación ya está en el carrito de compra.\n");
							pause();
						}
					}
				}else{
					seleccionTerminada = 1;
				}
			}else{
				seleccionTerminada = 1;
			}
		}else{
			pause();
			seleccionTerminada = 1;
		}
	}while(seleccionTerminada != 1);

	ll_delete(listaUbicaciones);
}

static void compra_agregarEntradaAlCarrito(LinkedList* carritoCompra, eCompra* compra, eFuncion funcion, int idUbicacion){
	float precio = compra_seleccionarTarifa(funcion, compra->idCliente);
	int idEntrada = DB_GetTableEntradasNextId() + compra->cantidadEntradas;
	eEntrada* entrada = Entrada_newParam(idEntrada, precio, compra->id, idUbicacion);

	Compra_setCantidadEntradas(compra, compra->cantidadEntradas+1);
	Compra_setPrecioTotal(compra, compra->precioTotal+precio);
	ll_add(carritoCompra, entrada);
	printf("\n  Entrada agregada al carrito.\n");
}

static float compra_seleccionarTarifa(eFuncion funcion, int idCliente){
	char confirm;
	int esNinoOMayor = 0;

	IO_getConfirm(&confirm, "\n   ¿La entrada es para un niño/a o mayor de 65 años? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
	if(confirm == 'S'){
		esNinoOMayor = 1;
	}

	return DB_SelectTarifa(funcion.idSala, funcion.fecha, esNinoOMayor, DB_getClienteSocioValue(idCliente));
}


static int compra_revisionCompra(LinkedList* carritoCompra, eCompra* compra){
	char confirm;
	int outcome = SUCCESS;
	int exit_flag = 0;
	do{
		system("cls");
		decoration_printCarritoCompra(carritoCompra);
		printf("\n [Proceso de cierre de compra]\n");
		IO_getConfirmOrCancel(&confirm, "\n   ¿Desea remover algún ítem de su orden antes del check-out? (C para Cancelar la compra) [S/N]: ", "  Error, ingrese una respuesta válida. ", 3);
		if(confirm == 'S'){
			do{
				int len = ll_len(carritoCompra);
				int item;
				system("cls");
				decoration_printCarritoCompra(carritoCompra);
				if(IO_getInteger(&item, "\n   Ingrese el nº de ítem o 0 para cancelar : ", "\n   Item inválido. ", 0, len, 3)){
					if(item!=0){
						char deleteMsg[256];
						sprintf(deleteMsg, "\n   ¿Está seguro/a de que desea eliminar el ítem Nº%d? [S/N]: ", item);
						IO_getConfirm(&confirm, deleteMsg, "  Error, ingrese una respuesta válida. ", 3);
						if(confirm == 'S'){
							eEntrada* entrada = ll_pop(carritoCompra, item-1);
							Compra_setCantidadEntradas(compra, compra->cantidadEntradas-1);
							Compra_setPrecioTotal(compra, compra->precioTotal-entrada->precio);
							free(entrada);
						}
					}

					IO_getConfirm(&confirm, "\n   ¿Desea remover algún ítem más? [S/N]: ", "  Error, ingrese una respuesta válida. ", 3);
					if(confirm == 'N'){
						exit_flag = 1;
					}
				}
			}while(exit_flag!=1);
		}else if(confirm == 'N'){
			exit_flag = 1;
		}else if(confirm == 'C'){
			IO_getConfirm(&confirm, "\n   ¿Está segura/o de que desea cancelar la compra? [S/N]: ", "  Error, ingrese una respuesta válida. ", 3);
			if(confirm == 'S'){
				exit_flag = 1;
				outcome = FAILURE;
				printf("\n   Compra cancelada.\n");
			}
		}
	}while(exit_flag!=1);

	return outcome;
}


static void compra_finalizarCompra(LinkedList* carritoCompra, eCompra* compra){
	char confirm;
	char confirmMsg[512];
	int exit_flag = 0;
	do{
		system("cls");
		decoration_printCarritoCompra(carritoCompra);
		sprintf(confirmMsg, "\n   ¿Desea confirmar su compra de %d entradas por un monto total de $ %.2f? [S/N]: ", compra->cantidadEntradas, compra->precioTotal);
		if(IO_getConfirm(&confirm, confirmMsg, "  Error, ingrese una respuesta válida. ", 3)){
			if(confirm == 'S'){
				DB_insertCompra(*compra);
				int len = ll_len(carritoCompra);
				for(int i=0; i<len; i++){
					//8B.
					eEntrada* entrada = (eEntrada*) ll_get(carritoCompra,i);
					DB_insertEntrada(*entrada);
					//8C.
					DB_updateDisponibilidadUbicacion((*entrada).idUbicacion, 0);
					free(entrada);
				}
				printf("\n   Su compra por un monto de $ %.2f fue efectuada exitosamente.\n", compra->precioTotal);
				exit_flag = 1;
			}else{
				IO_getConfirm(&confirm, "\n   ¿Está segura/o de que desea cancelar la compra? [S/N]: ", "  Error, ingrese una respuesta válida. ", 3);
				if(confirm == 'S'){
					exit_flag = 1;
					printf("\n   Compra cancelada.\n");
				}
			}
		}
	}while(exit_flag!=1);
}
