
#include "controller_mainMenu.h"

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



void database_InformeCantidadRegistros(){
	system("cls");
	printf("\n\n\n  +--------------------------------------------------+\n");
	printf("  |-----------  ");
	SetConsoleMenuTitleColor();
	printf("***  BASE DE DATOS  ***");
	SetConsoleStandardColor();
	printf("  ------------|\n");
	printf("  |--------------------------------------------------|\n");
	printf("  |              REGISTROS DE USUARIOS               |\n");
	printf("  |    Admins              |     %-5d registros     |\n", database_CountTableRecords("Admins"));
	printf("  |    Clientes            |     %-5d registros     |\n", database_CountTableRecords("Clientes"));
	printf("  |--------------------------------------------------|\n");
	printf("  |              REGISTROS DE PELÍCULAS              |\n");
	printf("  |    Películas           |     %-5d registros     |\n", database_CountTableRecords("Peliculas"));
	printf("  |    Directores          |     %-5d registros     |\n", database_CountTableRecords("Directores"));
	printf("  |    Actores             |     %-5d registros     |\n", database_CountTableRecords("Actores"));
	printf("  |    Cast                |     %-5d registros     |\n", database_CountTableRecords("Cast"));
	printf("  |--------------------------------------------------|\n");
	printf("  |            REGISTROS DE SALAS DE CINE            |\n");
	printf("  |    Salas               |     %-5d registros     |\n", database_CountTableRecords("Salas"));
	printf("  |    Tarifas             |     %-5d registros     |\n", database_CountTableRecords("Tarifas"));
	printf("  |    Horarios            |     %-5d registros     |\n", database_CountTableRecords("Horarios"));
	printf("  |--------------------------------------------------|\n");
	printf("  |          REGISTROS COMERCIALES / VENTAS          |\n");
	printf("  |    Funciones           |     %-5d registros     |\n", database_CountTableRecords("Funciones"));
	printf("  |    Ubicaciones         |     %-5d registros     |\n", database_CountTableRecords("Ubicaciones"));
	printf("  |    Entradas Vendidas   |     %-5d registros     |\n", database_CountTableRecords("Entradas"));
	printf("  |    Compras Realizadas  |     %-5d registros     |\n", database_CountTableRecords("Compras"));
	printf("  +--------------------------------------------------+\n\n\n");
    pause();
}


int controller_crearAdmin(){
	int outcome = FAILURE;
	int stage = 1;
	int flags[2] = {0,0}; //Flag: usuario,contraseña
	char confirm;
	char username[32]; 			//Stage 1
	char password[32]; 			//Stage 2

	do{
		fflush(stdin);
		View_printAdminCreationMenu(flags, username, password);
		switch (stage){
			case 1:	//get username
					printf("\n  El usuario sólo puede contener letras, números, punto, guión bajo y es insensible a mayúsculas.\n");
					if(IO_getUsername(username, 32)){
						if(!DB_DoesAdminExist(username)){
							flags[0] = 1;
							printf("\n   Usuario ingresado: %s.", username);
							stage++;
						}else{
							printf("\n   El nombre de usuario ya se encuentra en uso.");
						}
					}else{
						printf("\n   Intentos de carga de usuario agotados. El proceso de alta ha sido cancelado.");
						stage = 4;
					}
					break;

			case 2:	//get password
					printf("\n   La contraseña sólo puede contener letras, números, punto, guión bajo y es sensible a mayúsculas.\n");
					if(IO_getPassword(password, 32)){
						flags[1] = 1;
						printf("\n   Contraseña ingresada: %s.", password);
						stage++;
					}else{
						printf("\n   Intentos de carga de contraseña agotados. El proceso de alta ha sido cancelado.");
						stage = 7;
					}
					break;

			case 3:	//get confirmation
					IO_getConfirm(&confirm, "\n   ¿Desea confirmar el alta en el sistema? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
					if(confirm == 'S'){
						eAdmin* nuevoAdmin = Admin_newParam(username, password);
						DB_insertAdmin(*nuevoAdmin);
						if(DB_DoesAdminExist(username)){
							printf("\n   Admin creado correctamente.");
							outcome = SUCCESS;
						}else{
							printf("\n   No se pudo realizar el alta en el sistema.") ;
						}
						Admin_delete(nuevoAdmin);
					}else{
						printf("\n   El alta ha sido cancelada.");
					}
					stage++;
					break;
		}
		pause();
	}while(stage != 4);
    return outcome;
}


int controller_cambiarCalidadSocio(){
	int outcome = FAILURE;
	char str_socio[10];
	char confirmMsg[128];
	short socio;
	int id;
	int exit_flag = 0;
	int maxID = database_GetTableMaxId("Clientes");

	do{
		system("cls");
		char confirm = ' ';
		DB_listarClientes();
		if(IO_getInteger(&id, "\n   Ingrese el ID del Cliente (0 para Cancelar) : ", "\n     ID inválido. ", 0, maxID, 3)){
			if(id == 0){
				exit_flag = 1;
			}else{
				if(DB_DoesClienteExistById(id)){
					system("cls");
					DB_listarCliente(id);
					socio = (short) DB_getClienteSocioValue(id);
					(socio) ? strcpy(str_socio, "SÍ a NO") : strcpy(str_socio, "NO a SÍ") ;
					sprintf(confirmMsg, "\n   ¿Confirma que desea cambiar la calidad de socio del Cliente Nº%d de %s? [S/N] : ", id, str_socio);
					IO_getConfirm(&confirm, confirmMsg, "   Opción inválida.", 3);
					if(confirm == 'S'){
						DB_updateClienteSocioValue(id, 1-socio);
						outcome = SUCCESS;
					}
					confirm = ' ';
					IO_getConfirm(&confirm, "\n   ¿Desea realizar otra modificación? [S/N] : ", "   Opción inválida.", 3);
					if(confirm != 'S'){
						exit_flag = 1;
					}
				}

			}
		}else{
			exit_flag = 1;
		}
	}while(exit_flag != 1);
    return outcome;
}


int controller_cambiarUsername(Session* session){
	int outcome = FAILURE;
	char confirmMsg[256];
	char username[32];
	char currentUsername[32];
	int exit;

	strcpy(currentUsername, session->user.username);
	do{
		exit = 1;
		system("cls");
		char confirm = ' ';
		printf("\n  El usuario sólo puede contener letras, números, punto, guión bajo y es insensible a mayúsculas.\n");
		if(IO_getUsername(username, 32)){
			if(!DB_DoesAdminExist(username)){
				sprintf(confirmMsg,"\n   ¿Confirmar el cambio de nombre de usuario a \"%s\"? (S/N): ", username);
				IO_getConfirm(&confirm, confirmMsg, "   Opción inválida.", 3);
				if(confirm == 'S'){
					Admin_setUsername(&(session->user), username);
					DB_updateAdmin(session->user, currentUsername);
					outcome = SUCCESS;
				}
			}else{
				printf("\n   El nombre de usuario ya se encuentra en uso.");
				pause();
				exit = 0;
			}
		}else{
			printf("\n   Intentos de carga de usuario agotados. La modificación ha sido cancelada.");
			pause();
		}
	}while(exit != 1);
    return outcome;
}


int controller_cambiarPassword(Session* session){
	int outcome = FAILURE;
	char confirmMsg[256];
	char password[32];

	system("cls");
	char confirm = ' ';
	printf("\n   La contraseña sólo puede contener letras, números, punto, guión bajo y es sensible a mayúsculas.\n");
	if(IO_getPassword(password, 32)){
		sprintf(confirmMsg,"\n   ¿Desea confirmar el cambio de contraseña a \"%s\"? (S/N): ", password);
		IO_getConfirm(&confirm, confirmMsg, "   Opción inválida.", 3);
		if(confirm == 'S'){
			Admin_setPassword(&(session->user), password);
			DB_updateAdmin(session->user, session->user.username);
			outcome = SUCCESS;
		}
	}else{
		printf("\n   Intentos de carga de contraseña agotados. La modificación ha sido cancelada.");
		pause();
	}
    return outcome;
}


/*
int controller_nuevaVenta(){
	int outcome = FAILURE;
	int stage = 1;
	int flags[2] = {0,0}; //Flag: usuario,contraseña
	char confirm;
	char username[32]; 			//Stage 1
	char password[32]; 			//Stage 2

	do{
		fflush(stdin);
		View_printAdminCreationMenu(flags, username, password);
		switch (stage){
			case 1:	//get username
					printf("\n  El usuario sólo puede contener letras, números, punto, guión bajo y es insensible a mayúsculas.\n");
					if(IO_getUsername(username, 32)){
						if(!DB_DoesAdminExist(username)){
							flags[0] = 1;
							printf("\n   Usuario ingresado: %s.", username);
							stage++;
						}else{
							printf("\n   El nombre de usuario ya se encuentra en uso.");
						}
					}else{
						printf("\n   Intentos de carga de usuario agotados. El proceso de alta ha sido cancelado.");
						stage = 4;
					}
					break;

			case 2:	//get password
					printf("\n   La contraseña sólo puede contener letras, números, punto, guión bajo y es sensible a mayúsculas.\n");
					if(IO_getPassword(password, 32)){
						flags[1] = 1;
						printf("\n   Contraseña ingresada: %s.", password);
						stage++;
					}else{
						printf("\n   Intentos de carga de contraseña agotados. El proceso de alta ha sido cancelado.");
						stage = 7;
					}
					break;

			case 3:	//get confirmation
					IO_getConfirm(&confirm, "\n   ¿Desea confirmar el alta en el sistema? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
					if(confirm == 'S'){
						eAdmin* nuevoAdmin = Admin_newParam(username, password);
						DB_insertAdmin(*nuevoAdmin);
						if(DB_DoesAdminExist(username)){
							printf("\n   Admin creado correctamente.");
							outcome = SUCCESS;
						}else{
							printf("\n   No se pudo realizar el alta en el sistema.") ;
						}
						Admin_delete(nuevoAdmin);
					}else{
						printf("\n   El alta ha sido cancelada.");
					}
					stage++;
					break;
		}
		pause();
	}while(stage != 4);
    return outcome;
}
*/

















