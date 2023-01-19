
#ifndef MODEL_PELICULA_H_
#define MODEL_PELICULA_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	int id;
	char titulo[50];
	int year;
	int duracion;
	int idDirector;
	short proyectandose;
}ePelicula;

#endif /* MODEL_PELICULA_H_ */

ePelicula* Pelicula_newParam(int id, char* titulo, int year, int duracion, int idDirector, short proyectandose);
void Pelicula_delete(ePelicula* this);
int Pelicula_setId(ePelicula* this, int id);
int Pelicula_getId(ePelicula* this, int* dest);
int Pelicula_setTitulo(ePelicula* this, char* titulo);
int Pelicula_getTitulo(ePelicula* this, char* dest);
int Pelicula_setYear(ePelicula* this, int year);
int Pelicula_getYear(ePelicula* this, int* dest);
int Pelicula_setDuracion(ePelicula* this, int duracion);
int Pelicula_getDuracion(ePelicula* this, int* dest);
int Pelicula_setIdDirector(ePelicula* this, int idDirector);
int Pelicula_getIdDirector(ePelicula* this, int* dest);
int Pelicula_setProyectandose(ePelicula* this, short proyectandose);
int Pelicula_getProyectandose(ePelicula* this, short* dest);

int DB_getPeliculaById(ePelicula* pPelicula, int id);
void DB_getTituloDePeliculaById(char* dest, int id);
int DB_getListaPeliculas(LinkedList* pListaPeliculas);
int DB_insertPelicula(ePelicula pelicula);
int DB_updatePelicula(ePelicula pelicula, int id);
int DB_deletePelicula(int id);
int DB_DoesPeliculaExistById(int id);
int DB_DoesPeliculaExistByTitle(char* title);
void DB_printListaPeliculas(void);

void automatizacion_Peliculas_randomizarDuracion();
void automatizacion_Peliculas_randomizarProyectandose();
