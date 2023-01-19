
#include "user_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include "decoration.h"
#include "../IO_Libraries/IO_num.h"

void pause(void){
	char c;
	fflush(stdin);
	printf("\n\n  ***** Presione enter para continuar. *****");
	scanf("%c", &c);
	fflush(stdin);
}


void UI_getExitConfirmation(short* exitFlag){
	UI_getExitConfirmationMsg(exitFlag, "\n  �Est� seguro/a de que desea salir? S/N: ");
}

void UI_getExitConfirmationMsg(short* exitFlag, char* exitMsg){
	char confirmation;
	IO_getConfirm(&confirmation, exitMsg, "  Opci�n inv�lida.", 3);
	if(confirmation == 'S'){
		*exitFlag = 1;
	}
}

void UI_printExitMessage(){
    system("cls");
    decoration_printCinepolisLogo();
    printf("   Muchas gracias por usar el Sistema de Gesti�n de Salas de Cin�polis.");
    pause();
}


void UI_invertVisualStyle(short* visualConfig){
	char* visual[2] = {"minimalista","embellecido"};
	char confirmation;
	char msg[256];
	sprintf(msg, "\n  Actualmente la aplicaci�n funciona con el estilo visual %s.\n  �Desea alternarlo a %s? S/N: ", visual[*visualConfig], visual[1 - *visualConfig]);
	IO_getConfirm(&confirmation, msg, "  Opci�n inv�lida.", 1);
	if(confirmation == 'S'){
		*visualConfig = 1 - *visualConfig;
	}
}
