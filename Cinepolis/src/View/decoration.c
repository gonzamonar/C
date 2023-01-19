
#include <stdio.h>
#include <string.h>
#include "decoration.h"
#include "user_interface.h"
#include "../IO_Libraries/console.h"
#include "../IO_Libraries/str_ctype.h"
#include "../Model/sala.h"
#include "../Model/ubicacion.h"
#include "../Model/pelicula.h"
#include "../Model/entrada.h"
#include "../My_Libraries/LinkedList.h"
#include "../Error_Handling/error_log.h"


void printf_highlight(char* startString, char* colorString, char* endString, void (*pFuncColor)(void)){
	printf("%s", startString);
	pFuncColor();
	printf("%s", colorString);
	SetConsoleStandardColor();
	printf("%s", endString);
}


void decoration_printCinepolisLogo(void){
    SetConsoleWhite();
    printf("                                                                                                                               .\n");
    printf("                                                                                                                               .\n");
    SetConsoleLogoColor();
	printf("                  &&&                             &&&&                                             @&&&&    &&&                 \n");
	printf("                  &&&                            &&&&                                              @&&&&    &&&                 \n");
	printf("                                                                                                   @&&&&                        \n");
	printf("    .&&&&&&&&.   @&&&@   &&&&& .&&&&&.         &&&&&&&           &&&&&&&&.         .&&&&&&&&&.     @&&&&   &&&&#     ,&&&&&*    \n");
	printf("   &&&&&&&&&&&&  @&&&@   &&&&&&&&&&&&&&.    &&&&&&&&&&&&&    &&&&&&&&&&&&&&&.   .&&&&&&&&&&&&&&&.  @&&&&   &&&&#  ,&&&&&&&&&&&  \n");
	printf(" &&&&&           @&&&@   &&&&&      &&&&.  &&&&      .&&&&   &&&&&       &&&&&  &&&&&       &&&&&  @&&&&   &&&&#  &&&&&&        \n");
	printf("                 @&&&@   &&&&&      &&&&. &&&&&&&&&&&&&&&&&  &&&&         &&&&  &&&&         &&&&  @&&&&   &&&&#   &&&&&&&&&&   \n");
	printf(" &&&&&           @&&&@   &&&&&      &&&&. *&&&&              &&&&&       &&&&&  &&&&&       &&&&&  @&&&&   &&&&#        ,&&&&&& \n");
	printf("  &&&&&&&&&&&&&  @&&&@   &&&&&      &&&&.  *&&&&&@&&&&&&     &&&&&&&&.&&&&&&&   *&&&&&&&&&&&&&&&*  @&&&&   &&&&#  &&&&&,.,&&&&& \n");
	printf("    *&&&&&&&&*   @&&&@   &&&&&      &&&&.     &&&&&&&&&      &&&&.&&&&&&&&&        *&&&&&&&&&*     @&&&&   &&&&#   &&&&&&&&&&*  \n");
	printf("                                                             &&&&.                                                              \n");
	printf("                                                             &&&&.                                                              \n");
	printf("                                                             &&&&.                                                              \n");
	SetConsoleWhite();
    printf("                                                                                                                               .\n");
    printf("                                                                                                                               .\n");
    SetConsoleStandardColor();
    printf("\n\n");
}

int decoration_printUbicacionesSala(LinkedList *listaUbicaciones, eSala sala){
	int outcome = 1;
	int capacidad = sala.asientosPorFila * sala.cantidadFilas;
	int hallway = (sala.asientosPorFila / 2) - 1;
	int lastseat = sala.asientosPorFila - 1;
	char seat[3];
	char row = 'A';

	printf("\n\n\n");
	int len = ll_len(listaUbicaciones);
	if(capacidad != len){
		ErrorLog_write("Printing Error - No se pudo imprimir la función: cantidad de ubicaciones y capacidad de sala no coinciden.");
		printf("  Ocurrió un Error durante la impresión de asientos disponibles, reinténtelo nuevamente.\n\n");
		outcome = 0;
	}else{
		if(sala.asientosPorFila == 14){
			printf("                      SCREEN                     \n");
			printf("     /--------------------------------------\\    \n\n");
			printf("   01 02 03 04 05 06 07    08 09 10 11 12 13 14  \n");
		}else if(sala.asientosPorFila == 16){
			printf("                         SCREEN                     \n");
			printf("     /--------------------------------------------\\ \n\n");
			printf("   01 02 03 04 05 06 07 08    09 10 11 12 13 14 15 16  \n");
		}else{
			printf("            SCREEN          \n");
			printf("     /------------------\\   \n\n");
			printf("   01 02 03 04 05 06 07 08  \n");
		}

		for (int i = 0; i < capacidad; i++) {
			eUbicacion *ubicacion = (eUbicacion*) ll_get(listaUbicaciones, i);

			if ((i % sala.asientosPorFila) == 0) {
				SetConsoleStandardColor();
				printf(" %c ", row);
			}

			if (ubicacion != NULL) {
				if (ubicacion->disponible == 1) {
					strcpy(seat, "OO");
					SetFreeSeatColor();
				} else if (ubicacion->disponible == 0) {
					strcpy(seat, "XX");
					SetTakenSeatColor();
				} else {
					strcpy(seat, "RR");
					SetReservedSeatColor();
				}
			}

			printf("%s ", seat);

			if (i == hallway && sala.tienePasilloCentral) {
				printf("   ");
				hallway += sala.asientosPorFila;
			}

			if (i == lastseat) {
				SetConsoleStandardColor();
				printf("%c\n", row);
				lastseat += sala.asientosPorFila;
				row++;
			}
		}
		SetConsoleStandardColor();
		if (sala.asientosPorFila == 14) {
			printf("   01 02 03 04 05 06 07    08 09 10 11 12 13 14  \n");
		} else if (sala.asientosPorFila == 16) {
			printf("   01 02 03 04 05 06 07 08    09 10 11 12 13 14 15 16  \n");
		} else {
			printf("   01 02 03 04 05 06 07 08  \n");
		}
		printf("\n\n");
	}
	return outcome;
}



int decoration_printCarritoCompra(LinkedList *carrito){
	int outcome = 1;
	eUbicacion ubicacion;
	eFuncion funcion;
	int len = ll_len(carrito);
	char titulo[128];

	printf("\n\n\n");
	printf("  +-----------------------------------------------------------------------------------------------------+\n");
printf_highlight("  |-----------------------------------  ","***  CARRITO DE COMPRA  ***","  -----------------------------------|\n", SetConsoleColor_DarkCyan);
	printf("  |-----------------------------------------------------------------------------------------------------|\n");
	printf("  | Item |                      Película                      |   Fecha    | Hora  | Asiento |  Precio  |\n");
	printf("  |-----------------------------------------------------------------------------------------------------|\n");

	for(int i=0; i<len; i++){
		eEntrada* entrada = (eEntrada*) ll_get(carrito, i);

		DB_getUbicacion(&ubicacion, entrada->idUbicacion);
		DB_getFuncionById(&funcion, ubicacion.idFuncion);
		DB_getTituloDePeliculaById(titulo, funcion.idPelicula);

		printf("  | %4d | %-50s | %10s | %4s |   %c%-2d   |  %7.2f |\n", i+1, titulo, funcion.fecha, funcion.hora, ubicacion.fila, ubicacion.numero, entrada->precio);
	}
	printf("  +-----------------------------------------------------------------------------------------------------+\n\n");
	return outcome;
}
