/*
 * IO.c
 *
 *  Created on: Jun 8, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../IO_Libraries/console.h"
#include "IO_validation.h"


/// @brief Reversión de la función fgets eliminando el enter final del ingreso.
///
/// @param str (char*)	-> Puntero a STRING donde se almacena la cadena ingresada.
/// @param len (int)	-> INT que indica la longitud de la cadena.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
static int myGets(char*, int);

/// @brief Solicita el ingreso de un número al usuario y valida que sea INT.
///
/// @param pResultado (int*)-> Puntero a INT donde se almacena el ingreso.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
static int getInt(int*);

/// @brief Solicita el ingreso de un número al usuario y valida que sea FLOAT.
///
/// @param pResultado (float*)-> Puntero a FLOAT donde se almacena el ingreso.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
static int getFloat(float*);



static int myGets(char* str, int len){
	int outcome = 0;
	if(str != NULL && len > 0 && fgets(str, len, stdin) == str){
		fflush(stdin);
		if(str[strlen(str)-1] == '\n'){
			str[strlen(str)-1] = '\0';
		}
		outcome = 1;
	}
	return outcome;
}

static int getInt(int* pResultado){
	int outcome = 0;
	char buffer[64];
	if(pResultado != NULL){
		if(myGets(buffer, sizeof(buffer)) && validateInteger(buffer)){
			*pResultado = atoi(buffer);
			outcome = 1;
		}
	}
	return outcome;
}


static int getFloat(float* pResultado){
	int outcome = 0;
	char buffer[64];
	if(pResultado != NULL){
		if(myGets(buffer, sizeof(buffer)) && validateFloat(buffer)){
			*pResultado = atof(buffer);
			outcome = 1;
		}
	}
	return outcome;
}


int IO_getInteger(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
	int outcome = 0;
	int number;
	if(mensaje != NULL && pResultado != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 1){
		do{
			reintentos--;
			fflush(stdin);
			SetConsoleEnterOptionColor();
			printf("%s", mensaje);
			SetConsoleStandardColor();
			if(getInt(&number)){
				if(number >= minimo && number <= maximo){
					*pResultado = number;
					outcome = 1;
					break;
				}
			}
			fflush(stdin);
			if(reintentos>=1){
				SetConsoleErrorColor();
				printf("%s", mensajeError);
				printf("(Intentos restantes: %d)\n", reintentos);
				SetConsoleStandardColor();
			}
		}while(reintentos >= 1);
	}
	return outcome;
}


int IO_getConfirm(char* pResultado, char* mensaje, char* mensajeError, int reintentos){
	int outcome = 0;
	char buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 1){
		do{
			fflush(stdin);
			SetConsoleEnterOptionColor();
			printf("%s", mensaje);
			scanf("%c", &buffer);
			SetConsoleStandardColor();
			buffer = toupper(buffer);
			if(buffer == 'S' || buffer == 'N'){
				*pResultado = buffer;
				outcome = 1;
				break;
			}else{
				if(reintentos>=1){
					SetConsoleErrorColor();
					printf("%s", mensajeError);
					printf("(Intentos restantes: %d)\n", reintentos);
					SetConsoleStandardColor();
				}
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return outcome;
}

int IO_getConfirmOrCancel(char* pResultado, char* mensaje, char* mensajeError, int reintentos){
	int outcome = 0;
	char buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 1){
		do{
			fflush(stdin);
			SetConsoleEnterOptionColor();
			printf("%s", mensaje);
			scanf("%c", &buffer);
			SetConsoleStandardColor();
			buffer = toupper(buffer);
			if(buffer == 'S' || buffer == 'N' || buffer == 'C'){
				*pResultado = buffer;
				outcome = 1;
				break;
			}else{
				if(reintentos>=1){
					SetConsoleErrorColor();
					printf("%s", mensajeError);
					printf("(Intentos restantes: %d)\n", reintentos);
					SetConsoleStandardColor();
				}
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return outcome;
}


int IO_getFloatingPoint(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos){
	int outcome = 0;
	float number;
	if(mensaje != NULL && pResultado != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0){
		do{
			fflush(stdin);
			SetConsoleEnterOptionColor();
			printf("%s", mensaje);
			SetConsoleStandardColor();
			if(getFloat(&number)){
				if(number >= minimo && number <= maximo){
					*pResultado = number;
					outcome = 1;
					break;
				}
			}

			if(reintentos>=1){
				SetConsoleErrorColor();
				printf("%s", mensajeError);
				printf("(Intentos restantes: %d)\n", reintentos);
				SetConsoleStandardColor();
			}
			reintentos--;
		}while(reintentos >= 0);
	}
	return outcome;
}


int IO_getMenuSelection(short* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo){
	int outcome = 0;
	int number;
	if(mensaje != NULL && pResultado != NULL && mensajeError != NULL && minimo <= maximo){
		fflush(stdin);
		SetConsoleEnterOptionColor();
		printf("%s", mensaje);
		SetConsoleStandardColor();
		if(getInt(&number)){
			if(number >= minimo && number <= maximo){
				*pResultado = number;
				outcome = 1;
				return outcome;
			}
		}
		fflush(stdin);
		SetConsoleErrorColor();
		printf("%s", mensajeError);
		SetConsoleStandardColor();
	}
	return outcome;
}
