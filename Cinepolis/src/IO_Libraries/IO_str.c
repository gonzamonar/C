
#ifndef VIEW_IO_IO_STR_C_
#define VIEW_IO_IO_STR_C_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../IO_Libraries/IO_str.h"
#include "../IO_Libraries/IO_validation.h"
#include "../IO_Libraries/str_ctype.h"
#include "../IO_Libraries/console.h"

#endif /* VIEW_IO_IO_STR_C_ */



/// @brief Reversión de la función fgets eliminando el enter final del ingreso con longitud minima y maxima de cadena.
///
/// @param str -> cadena de destino del ingreso
/// @param size -> tamaño de la cadena de destino
/// @param maxlen -> longitud máxima aceptada
/// @param minlen -> longitud minima aceptada
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
static int myStrGets(char* str, int size, int maxlen, int minlen);

static int getProperNameStr(char* dest, int size, int maxlen, int minlen, char* exceptions);
static int getAlphaStr(char* dest, int size, int maxlen, int minlen, char* exceptions);
static int getAlnumStr(char* dest, int size, int maxlen, int minlen, char* exceptions);
static int getStr(char* dest, int size, int maxlen, int minlen, char* exceptions, int (*pFuncValidation)(char*, char*));
static int IO_getString(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions, int (*pFuncStrType)(char*, int, int, int, char*), int (*pFuncCaption)(char*));


static int myStrGets(char* str, int size, int maxlen, int minlen){
	int outcome = 0;
	if(str != NULL && size > 0 && fgets(str, size, stdin) == str){
		if(strlen(str)<=maxlen && strlen(str)>=minlen){
			fflush(stdin);
			if(str[strlen(str)-1] == '\n'){
				str[strlen(str)-1] = '\0';
			}
			outcome = 1;
		}
	}
	return outcome;
}

static int getProperNameStr(char* dest, int size, int maxlen, int minlen, char* exceptions){
	return getStr(dest, size, maxlen, minlen, exceptions, validateProperNameStr);
}

static int getAlphaStr(char* dest, int size, int maxlen, int minlen, char* exceptions){
	return getStr(dest, size, maxlen, minlen, exceptions, validateAlphaStr);
}

static int getAlnumStr(char* dest, int size, int maxlen, int minlen, char* exceptions){
	return getStr(dest, size, maxlen, minlen, exceptions, validateAlnumStr);
}


static int getStr(char* dest, int size, int maxlen, int minlen, char* exceptions, int (*pFuncValidation)(char*, char*)){
	int outcome = 0;
	char buffer[size+4];
	if(dest != NULL){
		if(myStrGets(buffer, size, maxlen, minlen) && pFuncValidation(buffer, exceptions)){
			strcpy(dest, buffer);
			outcome = 1;
		}
	}
	return outcome;
}

static int IO_getString(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions, int (*pFuncStrType)(char*, int, int, int, char*), int (*pFuncCaption)(char*)){
	int outcome = 0;
	char strBuffer[size+4];

	if(mensaje != NULL && dest != NULL && mensajeError != NULL && size >0 && maxlen>=minlen && reintentos >= 1){
		do{
			reintentos--;
			fflush(stdin);
			SetConsoleEnterOptionColor();
			printf("%s", mensaje);
			SetConsoleStandardColor();
			if(pFuncStrType(strBuffer,size,maxlen,minlen,exceptions)){
					fflush(stdin);
					pFuncCaption(strBuffer);
					strcpy(dest, strBuffer);
					outcome = 1;
					break;
			}
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


int IO_getProperNameString(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions){
	return IO_getString(dest, size, maxlen, minlen, mensaje, mensajeError, reintentos, " ", getProperNameStr, str_totitle);
}

int IO_getUsername(char* dest, int size){
	return IO_getString(dest, size, 24, 4, "\n     Ingrese nombre de usuario: ", "\n     Formato de nombre de usuario inválido. ", 3, "._", getAlnumStr, str_tolower);
}

int IO_getPassword(char* dest, int size){
	return IO_getString(dest, size, 24, 4, "\n     Ingrese contraseña: ", "\n     Formato de contraseña inválido. ", 3, "._", getAlnumStr, str_nochange);
}

int IO_getUbicacion(char* dest, int size){
	return IO_getString(dest, size, 5, 3, "\n     Ingrese fila y número de ubicación (formato A00): ", "\n     Formato inválido. ", 3, "", getAlnumStr, str_nochange);
}

int IO_getAlphaString(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions){
	return IO_getString(dest, size, maxlen, minlen, mensaje, mensajeError, reintentos, " ", getAlphaStr, str_tolower);
}
