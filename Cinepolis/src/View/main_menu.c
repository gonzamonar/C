
#include "main_menu.h"

#include <stdio.h>
#include "menus.h"
#include "user_interface.h"
#include "../Controller/controller_mainMenu.h"
#include "../Controller/automation.h"
#include "../Model/pelicula.h"
#include "../Controller/controller_compras.h"
#include "../Controller/listar_objetos.h"
#include "../Controller/session.h"

void mainMenu_SubmenuVentas(){
	short exitSubmenu = 0;

	do{
		switch(View_MenuCompras()){
			case 1:
				controller_procesarCompra();
				break;
			case 2:
				controller_automatizacionCompras();
				break;
			case 3:
				DB_listarTarifas();
				break;
			case 4:
				exitSubmenu = 1;
				break;
		}
	}while(exitSubmenu != 1);
}


void mainMenu_SubmenuFunciones(){
	short exitSubmenu = 0;

	do{
		switch(View_MenuFunciones()){
			case 1:
				controller_automatizacionFunciones();
				break;
			case 2:
				DB_listarFunciones();
				pause();
				break;
			case 3:
				exitSubmenu = 1;
				break;
		}
	}while(exitSubmenu != 1);
}

void mainMenu_SubmenuPeliculas(){
	short exitSubmenu = 0;

	do{
		switch(View_MenuPeliculas()){
			case 1:
				DB_listarPeliculas();
				break;
			case 2:
				DB_listarCast();
				break;
			case 3:
				DB_listarFuncionesDePeliculas();
				break;
			case 4:
				exitSubmenu = 1;
				break;
		}
	}while(exitSubmenu != 1);
}


void mainMenu_SubmenuClientes(){
	short exitSubmenu = 0;

	do{
		switch(View_MenuClientes()){
			case 1:
				DB_listarClientes();
				pause();
				break;
			case 2:
				controller_cambiarCalidadSocio();
				break;
			case 3:
				DB_listarComprasPorCliente();
				break;
			case 4:
				exitSubmenu = 1;
				break;
		}
	}while(exitSubmenu != 1);
}


void mainMenu_SubmenuSalas(){
	short exitSubmenu = 0;

	do{
		switch(View_MenuSalas()){
			case 1:
				DB_listarSalas();
				break;
			case 2:
				DB_listarRecaudacionSalas();
				break;
			case 3:
				DB_listarRecaudacionSalasPorFuncion();
				break;
			case 4:
				exitSubmenu = 1;
				break;
		}
	}while(exitSubmenu != 1);
}


void mainMenu_SubmenuCuenta(Session* session){
	short exitSubmenu = 0;

	do{
		switch(View_MenuCuenta()){
			case 1:
				controller_cambiarUsername(session);
				break;
			case 2:
				controller_cambiarPassword(session);
				break;
			case 3:
				exitSubmenu = 1;
				break;
		}
	}while(exitSubmenu != 1);
}
