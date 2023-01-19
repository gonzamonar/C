/*
 * IO_validation.c
 *
 *  Created on: 9 ene. 2023
 *      Author: GM
 */

#ifndef VIEW_IO_IO_VALIDATION_C_
#define VIEW_IO_IO_VALIDATION_C_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../IO_Libraries/IO_validation.h"

#endif /* VIEW_IO_IO_VALIDATION_C_ */



/// @brief Valida que todos los valores dentro de una cadena sean números reales (con decimales).
///
/// @param str (char*)-> STRING a validar por la función.
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
//static int validateFloat(char*);

/// @brief Valida que todos los valores dentro de una cadena sean números enteros.
///
/// @param str (char*)-> STRING a validar por la función.
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
//static int validateInteger(char* str);


/// @brief Valida que la cadena esté compuesta por letras.
///
/// @param str -> cadena a validar
/// @param exceptions -> excepciones de validación (espacios, guiones, etc)
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
//static int validateAlphaStr(char* str, char* exceptions);

static int validateStr(char* str, char* exceptions, int (*pFuncValidation)(int));

/// @brief Valida que la cadena posea al menos una vocal y una consonante.
///
/// @param str -> cadena a validar
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
static int checkVowelsAndConsonants(char* str);



static int validateStr(char* str, char* exceptions, int (*pFuncValidation)(int)){
	int outcome = 1;
	int i = 0;

	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if(!pFuncValidation(str[i]) && !(strchr(exceptions, str[i]))){
				outcome = 0;
				break;
			}
			i++;
		}
	}
	return outcome;
}

/*
static int validateInteger(char* str){
	int outcome = 1;
	int i = 0;
	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if(str[i] < '0' || str[i] > '9'){
				outcome = 0;
				break;
			}
			i++;
		}
	}
	return outcome;
}


static int validateFloat(char* str){
	int outcome = 1;
	int i = 0;
	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if((str[i] < '0' || str[i] > '9') && str[i] != '.'){
				outcome = 0;
				break;
			}
			i++;
		}
	}
	return outcome;
}

*/

static int checkVowelsAndConsonants(char* str){
	int outcome = 0;
	int i = 0;
	int consonantFlag = 0;
	int vowelFlag = 0;

	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if(!vowelFlag && strchr("aeiouAEIOU", str[i])){
				vowelFlag = 1;
			}

			if(!consonantFlag && strchr("bcdfghjklmnñpqrstvwxyzBCDFGHJKLMNÑPQRSTVWXYZ", str[i])){
				consonantFlag = 1;
			}

			if(vowelFlag && consonantFlag){
				outcome = 1;
				break;
			}
			i++;
		}
	}
	return outcome;
}


int validateProperNameStr(char* str, char* exceptions){
	return validateStr(str, exceptions, isalpha) && checkVowelsAndConsonants(str);
}

int validateAlphaStr(char* str, char* exceptions){
	return validateStr(str, exceptions, isalpha);
}

int validateAlnumStr(char* str, char* exceptions){
	return validateStr(str, exceptions, isalnum);
}

int validateInteger(char* str){
	return validateStr(str, "", isdigit);
}

int validateFloat(char* str){
	return validateStr(str, ".", isdigit);
}
