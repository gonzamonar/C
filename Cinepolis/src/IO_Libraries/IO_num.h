/*
 * IO.h
 *
 *  Created on: Jun 8, 2022
 *      Author: GM
 */

#ifndef TP2_IO_H_
#define TP2_IO_H_

#endif /* TP2_IO_H_ */


/// @brief Función para obtener un nro entero (INT) ingresado por el usuario.
///
/// @param pResultado 	(int*)	-> 	Puntero donde va a almacenarse el resultado del ingreso.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del dato.
/// @param mensajeError (char*)	-> 	Mensaje en caso de error en el ingreso.
/// @param minimo  		(int)	-> 	Valor mínimo del número a ingresar.
/// @param maximo 		(int)	-> 	Valor máximo del número a ingresar.
/// @param reintentos 	(int)	-> 	Cantidad de reintentos otorgados al usuario.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
int IO_getInteger(int*, char*, char*, int, int, int);



/// @brief Función para recibir una confirmación binaria de tipo S/N.
///
/// @param pResultado 	(char*)	-> 	Devuelve el valor S o N ingresado por el usuario.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del caracter.
/// @param mensajeError (char*)	-> 	Mensaje en caso de error en el ingreso.
/// @param reintentos 	(int)	-> 	Cantidad de reintentos otorgados al usuario.
///
/// @return retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
int IO_getConfirm(char*, char*, char*, int);



/// @brief Función para obtener un nro real con decimales (FLOAT) ingresado por el usuario.
///
/// @param pResultado 	(float*)-> 	Puntero donde va a almacenarse el resultado del ingreso.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del dato.
/// @param mensajeError (char)*	->	Mensaje en caso de error en el ingreso.
/// @param minimo 		(float)	->	Valor mínimo del número a ingresar.
/// @param maximo 		(float)	-> 	Valor máximo del número a ingresar.
/// @param reintentos 	(int)	-> 	Cantidad de reintentos otorgados al usuario.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla
int IO_getFloatingPoint(float*, char*, char*, float, float, int);



/// @brief Función para obtener una cadena (string) con formato de nombre propio ingresado por el usuario.
///
/// @param dest 	(char*) -> cadena de destino donde se va a copiar lo ingresado por el usuario
/// @param size		(int) -> tamaño de la cadena de destino
/// @param maxlen	(int) -> tamaño máximo aceptado para el ingreso de la cadena
/// @param minlen	(int) -> tamaño mínimo aceptado para el ingreso de la cadena
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del dato.
/// @param mensajeError (char*)	->	Mensaje en caso de error en el ingreso.
/// @param reintentos (int) -> cantidad de reintentos
/// @param exceptions (char*) -> cadena donde se contienen las excepciones de carácteres especiales para validar (ejemplo: espacios, guiones, etc).
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla
int IO_getProperName(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions);



/// @brief Función para el ingreso de un número de menú sin cancelación por cantidad de intentos fallidos.
///
/// @param pResultado 	(int*)-> 	Puntero donde va a almacenarse el resultado del ingreso.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del dato.
/// @param mensajeError (char)*	->	Mensaje en caso de error en el ingreso.
/// @param minimo  		(int)	-> 	Valor mínimo del número a ingresar.
/// @param maximo 		(int)	-> 	Valor máximo del número a ingresar.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla
int IO_getMenuSelection(short* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo);


int IO_getConfirmOrCancel(char* pResultado, char* mensaje, char* mensajeError, int reintentos);
