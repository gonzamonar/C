
#include "menus.h"

#include <stdio.h>
#include <stdlib.h>
#include "decoration.h"
#include "user_interface.h"
#include "../IO_Libraries/console.h"
#include "../IO_Libraries/IO_num.h"


//STANDARD MENU PRINTER
static int View_StandardMenu(int maxOption, void(*pFuncMenuPrinter)(void));
//WELCOME MENU
static void printer_simple_WelcomeMenu();
static void printer_complex_WelcomeMenu();
//MAIN MENU
static void printer_MainMenu();
//SUBMENUS OF MAIN MENU
static void printer_MenuCompras();
static void printer_MenuFunciones();
static void printer_MenuPeliculas();
static void printer_MenuClientes();
static void printer_MenuSalas();
static void printer_MenuCuenta();



//STANDARD MENU PRINTER
static int View_StandardMenu(int maxOption, void(*pFuncMenuPrinter)(void)){
	short selection = 0;
	system("cls");
	printf("\n\n");
	pFuncMenuPrinter();
	if(!IO_getMenuSelection(&selection, "     Ingrese una opción : ", "\n  Opción de menú inválida, inténtelo nuevamente.", 1, maxOption)){
		pause();
	}
	return selection;
}


//WELCOME MENU
int View_WelcomeMenu(short visualStyle){
	void(*pFuncPrinter)(void) = (visualStyle) ? printer_complex_WelcomeMenu : printer_simple_WelcomeMenu ;
	return View_StandardMenu(5, pFuncPrinter);
}


static void printer_simple_WelcomeMenu(){
	printf("\n     Bienvenido/a al Sistema de Gestión de Salas de Cinépolis\n\n\n");
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Inicio ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf("     1. Login\n");
	printf("     2. Crear Nuevo Admin\n");
	printf("     3. Cambiar estilo visual\n");
	printf("     4. Reiniciar Base de Datos\n");
	printf("     5. Salir\n\n");
}


static void printer_complex_WelcomeMenu(){
	decoration_printCinepolisLogo();
	printf("        Bienvenido/a al Sistema de Gestión de Salas de Cinépolis.\n\n\n");
	printf("  +------------------------------------------------------------------------------------------------------+\n");
	printf("  |--------------------------------------  ");
	SetConsoleMenuTitleColor();
	printf("*** MENÚ DE INICIO ***");
	SetConsoleStandardColor();
	printf("  --------------------------------------|\n");
	printf("  |------------------------------------------------------------------------------------------------------|\n");
	printf("  |                                                                                                      |\n");
	printf("  |  1. Login                                                                                            |\n");
	printf("  |  2. Crear nuevo Admin                                                                                |\n");
	printf("  |  3. Cambiar estilo visual                                                                            |\n");
	printf("  |  4. Reiniciar Base de Datos                                                                          |\n");
	printf("  |  5. Salir                                                                                            |\n");
	printf("  |                                                                                                      |\n");
	printf("  |------------------------------------------------------------------------------------------------------|\n");
	printf("  +------------------------------------------------------------------------------------------------------+\n\n");
}


//MAIN MENU
int View_MainMenu(){
	return View_StandardMenu(9, printer_MainMenu);
}

/*
static void printer_MainMenu(){
	printf("  +------------------------------------------------------------------------------------------------------+\n");
	printf("  |--------------------------------------  ");
	SetConsoleMenuTitleColor();
	printf("*** MENÚ PRINCIPAL ***");
	SetConsoleStandardColor();
	printf("  --------------------------------------|\n");
	printf("  |------------------------------------------------------------------------------------------------------|\n");
	printf("  |                                                                                                      |\n");
	printf("  |  1. Procesar COMPRAS                                                                                 |\n");
	printf("  |  2. Gestionar FUNCIONES                                                                              |\n");
	printf("  |  3. Gestionar PELÍCULAS                                                                              |\n");
	printf("  |  4. Administrar CLIENTES                                                                             |\n");
	printf("  |  5. Administrar SALAS                                                                                |\n");
	printf("  |  6. Configuración de CUENTA                                                                          |\n");
	printf("  |  7. Estado BASE DE DATOS                                                                             |\n");
	printf("  |  8. Cerrar Sesión                                                                                    |\n");
	printf("  |  9. Salir                                                                                            |\n");
	printf("  |                                                                                                      |\n");
	printf("  |------------------------------------------------------------------------------------------------------|\n");
	printf("  +------------------------------------------------------------------------------------------------------+\n\n");
}
*/

static void printer_MainMenu(){
	printf("  +------------------------------------------------------------------------------------------------------+\n");
	printf("  |--------------------------------------  ");
	SetConsoleMenuTitleColor();
	printf("*** MENÚ PRINCIPAL ***");
	SetConsoleStandardColor();
	printf("  --------------------------------------|\n");
	printf("  |------------------------------------------------------------------------------------------------------|\n");
	printf("  |                                                                                                      |\n");
	printf_highlight("  |  1. Procesar ","COMPRAS","                                                                                 |\n", SetConsoleYellowColor);
	printf_highlight("  |  2. Gestionar ","FUNCIONES","                                                                              |\n", SetConsoleYellowColor);
	printf_highlight("  |  3. Gestionar ","PELÍCULAS","                                                                              |\n", SetConsoleYellowColor);
	printf_highlight("  |  4. Administrar ","CLIENTES","                                                                             |\n", SetConsoleYellowColor);
	printf_highlight("  |  5. Administrar ","SALAS","                                                                                |\n", SetConsoleYellowColor);
	printf_highlight("  |  6. Configuración de ","CUENTA","                                                                          |\n", SetConsoleYellowColor);
	printf_highlight("  |  7. Estado ","BASE DE DATOS","                                                                             |\n", SetConsoleYellowColor);
	printf("  |  8. Cerrar Sesión                                                                                    |\n");
	printf("  |  9. Salir                                                                                            |\n");
	printf("  |                                                                                                      |\n");
	printf("  |------------------------------------------------------------------------------------------------------|\n");
	printf("  +------------------------------------------------------------------------------------------------------+\n\n");
}



//SUBMENUS OF MAIN MENU
int View_MenuCompras(){
	return View_StandardMenu(4, printer_MenuCompras);
}

int View_MenuFunciones(){
	return View_StandardMenu(3, printer_MenuFunciones);
}

int View_MenuPeliculas(){
	return View_StandardMenu(4, printer_MenuPeliculas);
}

int View_MenuClientes(){
	return View_StandardMenu(4, printer_MenuClientes);
}

int View_MenuSalas(){
	return View_StandardMenu(4, printer_MenuSalas);
}

int View_MenuCuenta(){
	return View_StandardMenu(3, printer_MenuCuenta);
}


static void printer_MenuCompras(){
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Ventas ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf("     1. Nuevo proceso de Compra\n");
	printf_highlight("     2. Simular Compras ","(automatización)","\n",SetConsoleGreenColor);
	printf("     3. Listar Tarifas vigentes\n");
	printf("     4. Volver al Menú Principal\n\n");
}



static void printer_MenuFunciones(){
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Gestión de Funciones ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf_highlight("     1. Generar Funciones ","(automatización)","\n",SetConsoleGreenColor);
	printf("     2. Listar Funciones y Disponibilidad\n");
	printf("     3. Volver al Menú Principal\n\n");
}


static void printer_MenuPeliculas(){
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Gestión de Películas ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf("     1. Listar Películas\n");
	printf("     2. Listar Cast de Películas\n");
	printf("     3. Informar cantidad de Funciones por Película\n");
	printf("     4. Volver al Menú Principal\n\n");
}



static void printer_MenuClientes(){
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Gestión de Clientes ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf("     1. Listar Clientes\n");
	printf("     2. Cambiar calidad de Socio\n");
	printf("     3. Informar compras por Cliente\n");
	printf("     4. Volver al Menú Principal\n\n");
}



static void printer_MenuSalas(){
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Gestión de Salas ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf("     1. Listar Salas\n");
	printf("     2. Informar recaudación total por Sala\n");
	printf("     3. Informar recaudación de Sala por Función\n");
	printf("     4. Volver al Menú Principal\n\n");
}


static void printer_MenuCuenta(){
	SetConsoleMenuTitleColor();
	printf("     *** Configuración de Cuenta ***\n");
	SetConsoleStandardColor();
	printf("     --------------------------------------------------------\n");
	printf("     1. Cambiar nombre de usuario\n");
	printf("     2. Cambiar contraseña\n");
	printf("     3. Volver al Menú Principal\n\n");
}










void view_printFunciones(){
	system("cls");
	printf("\n\n\n  +---------------------------------------------------------------------------------------------------+\n");
	printf("  |-----------------------------------  ");
	SetConsoleMenuTitleColor();
	printf("***  FUNCIONES DÍA  ***");
	SetConsoleStandardColor();
	printf("  -------------------------------------|\n");
	printf("  |-----------------------------------  ");
	SetConsoleMenuTitleColor();
	printf("***    %-10s   ***", "14/01/2023");
	SetConsoleStandardColor();
	printf("  -------------------------------------|\n");
	printf("  |---------------------------------------------------------------------------------------------------|\n");
	printf("  |         SALA 1         |         SALA 2         |         SALA 3         |         SALA 4         |\n");
	printf("  |---------------------------------------------------------------------------------------------------|\n");
	printf("  |                        |                        |                        |                        |\n");
	printf("  | 12:30  %-15s | 13:50  %-15s | 14:20  %-15s | 14:50  %-15s |\n", "Pelicula 1", "Pelicula 2", "Pelicula 3", "Pelicula 4");
	printf("  |                        |                        |                        |                        |\n");
	printf("  | 15:20  %-15s | 16:50  %-15s | 17:50  %-15s | 18:20  %-15s |\n", "Pelicula 1", "Pelicula 2", "Pelicula 3", "Pelicula 4");
	printf("  |                        |                        |                        |                        |\n");
	printf("  | 18:50  %-15s | 18:50  %-15s | 20:50  %-15s | 21:50  %-15s |\n", "Pelicula 1", "Pelicula 2", "Pelicula 3", "Pelicula 4");
	printf("  |                        |                        |                        |                        |\n");
	printf("  | 21:20  %-15s | 22:20  %-15s | 22:50  %-15s | 23:00  %-15s |\n", "Pelicula 1", "Pelicula 2", "Pelicula 3", "Pelicula 4");
	printf("  |                        |                        |                        |                        |\n");
	printf("  | 23:30  %-15s |                        |                        |                        |\n", "Pelicula 1");
	printf("  |                        |                        |                        |                        |\n");
	printf("  |---------------------------------------------------------------------------------------------------|\n");
	printf("  +---------------------------------------------------------------------------------------------------+\n\n");
}
