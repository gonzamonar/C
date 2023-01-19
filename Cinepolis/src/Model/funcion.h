
#ifndef MODEL_FUNCION_H_
#define MODEL_FUNCION_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	int idPelicula;
	int idSala;
	char fecha[16];
	char hora[8];
	short subtitulada;
}eFuncion;

#endif /* MODEL_FUNCION_H_ */


eFuncion* Funcion_newParam(int id, int idPelicula, int idSala, char* fecha, char* hora, short subtitulada);
void Funcion_delete(eFuncion* this);
int Funcion_setId(eFuncion* this, int id);
int Funcion_getId(eFuncion* this, int* dest);
int Funcion_setIdPelicula(eFuncion* this, int idPelicula);
int Funcion_getIdPelicula(eFuncion* this, int* dest);
int Funcion_setIdSala(eFuncion* this, int idSala);
int Funcion_getIdSala(eFuncion* this, int* dest);
int Funcion_setFecha(eFuncion* this, char* fecha);
int Funcion_getFecha(eFuncion* this, char* dest);
int Funcion_setHora(eFuncion* this, char* hora);
int Funcion_getHora(eFuncion* this, char* dest);
int Funcion_setSubtitulada(eFuncion* this, short subtitulada);
int Funcion_getSubtitulada(eFuncion* this, short* dest);

int DB_getFuncionById(eFuncion* pFuncion, int id);
int DB_getFuncionByFechaSalaHora(eFuncion* pFuncion, char* fecha, int idSala, char* hora);
int DB_getListaFunciones(LinkedList* pListaFunciones);
int DB_insertFuncion(eFuncion funcion);
int DB_updateFuncion(eFuncion funcion, int id);
int DB_deleteFuncion(int id);
int DB_GetTableFuncionesNextId();
int DB_DoesFuncionExistById(int id);
int DB_DoesFuncionExistByFechaSalaHora(char* fecha, int idSala, char* hora);

void Automatizacion_generarFunciones(int cantidad);

