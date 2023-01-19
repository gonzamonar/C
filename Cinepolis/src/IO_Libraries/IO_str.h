/*
 * IO_str.h
 *
 *  Created on: 9 ene. 2023
 *      Author: GM
 */

#ifndef VIEW_IO_IO_STR_H_
#define VIEW_IO_IO_STR_H_



#endif /* VIEW_IO_IO_STR_H_ */


int IO_getProperName(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions);
int IO_getProperNameString(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions);
int IO_getUsername(char* dest, int size);
int IO_getPassword(char* dest, int size);
int IO_getUbicacion(char* dest, int size);
