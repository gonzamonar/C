/*
 * hardcoder.h
 *
 *  Created on: 13 ene. 2023
 *      Author: GM
 */

#ifndef CONTROLLER_HARDCODER_H_
#define CONTROLLER_HARDCODER_H_

#include <stdio.h>

#endif /* CONTROLLER_HARDCODER_H_ */


int Hardcode(char* filename, int(*pFuncHardcoder)(FILE*));
int HardcodeAdmins();
int harcode_ActoresFromCSV(FILE* pFile);
int harcode_CastFromCSV(FILE* pFile);
int harcode_ClientesFromCSV(FILE* pFile);
int harcode_DirectoresFromCSV(FILE* pFile);
int harcode_PeliculasFromCSV(FILE* pFile);
int harcode_HorariosFromCSV(FILE* pFile);
int harcode_SalasFromCSV(FILE* pFile);
int harcode_TarifasFromCSV(FILE* pFile);
