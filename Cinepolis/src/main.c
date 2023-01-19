/*
 ============================================================================
 Name        : Cinepolis.c
 ============================================================================
 */

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Controller/automation.h"
#include "Controller/session.h"
#include "Controller/login.h"
#include "Controller/controller_mainMenu.h"
#include "IO_Libraries/console.h"
#include "View/main_menu.h"
#include "View/menus.h"
#include "View/user_interface.h"

int main(void){
	//main variables
	short visualConfig = 1;
	short exitProgram = 0;
    Session* session = Session_new();

    //Console setting
	setlocale(LC_ALL, "spanish");
	setbuf(stdout, NULL);
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    SetConsoleTitle("Cinépolis - Sistema de Gestión de Salas");
    SetConsoleWindowSize(130, 50);

    //Program loop
    do{
		switch(View_WelcomeMenu(visualConfig)){

			case 1: //Session loop
				if(controller_Login(session, visualConfig) && session->status){
					short exitSession = 0;
					do{
						switch(View_MainMenu()){
							case 1:
								mainMenu_SubmenuVentas();
								break;
							case 2:
								mainMenu_SubmenuFunciones();
								break;
							case 3:
								mainMenu_SubmenuPeliculas();
								break;
							case 4:
								mainMenu_SubmenuClientes();
								break;
							case 5:
								mainMenu_SubmenuSalas();
								break;
							case 6:
								mainMenu_SubmenuCuenta(session);
								break;
							case 7:
								database_InformeCantidadRegistros();
								break;
							case 8:
								UI_getExitConfirmationMsg(&exitSession, "\n  ¿Está seguro/a de que desea cerrar la sesión? S/N: ");
								if(exitSession){
									controller_endSession(session);
								}
								break;
							case 9:
								UI_getExitConfirmation(&exitProgram);
								exitSession = exitProgram;
								break;
						}
					}while(exitSession != 1);
				}
				break;

			case 2: //Create Admin
				controller_crearAdmin();
				break;

			case 3: //Visual Style
				UI_invertVisualStyle(&visualConfig);
				break;

			case 4: //Restart Database
				controller_restartDatabase();
				break;

			case 5: //Exit
				UI_getExitConfirmation(&exitProgram);
				break;
		}
    }while(exitProgram != 1);

    //Exit operations
    Session_delete(session);
    UI_printExitMessage();
	return 0;
}
