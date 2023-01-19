
#include "hardcoder.h"

#include <stdio.h>
#include <stdlib.h>

#include "../Error_Handling/error_log.h"
#include "../Model/actor.h"
#include "../Model/admin.h"
#include "../Model/cast.h"
#include "../Model/cliente.h"
#include "../Model/director.h"
#include "../Model/pelicula.h"
#include "../Model/horario.h"
#include "../Model/sala.h"
#include "../Model/tarifa.h"
#include "../View/user_interface.h"

#define SUCCESS 1
#define FAILURE 0


int Hardcode(char* filename, int(*pFuncHardcoder)(FILE*))
{
	int outcome = FAILURE;
	char filepath[256];
	sprintf(filepath, "C:\\Users\\GM\\eclipse-workspace\\Cinepolis\\Debug\\CSV\\%s", filename);
	FILE* f = fopen(filepath, "r");
	if(f==NULL){
		char errorLog[256];
		sprintf(errorLog, "Hardcode Error - No se pudo abrir el archivo \"%s\".", filename);
		ErrorLog_write(errorLog);
		printf("  Error - No se encontró el archivo %s para realizar el proceso de carga.\n", filename);
	}else{
		pFuncHardcoder(f);
		outcome = SUCCESS;
		printf("  Carga del archivo %s exitosa.\n", filename);
	}
	fclose(f);
    return outcome;
}


int HardcodeAdmins()
{
	int outcome = SUCCESS;
	char adminsUsernames[3][32] = {"root", "admin", "administrador"};
	char adminsPasswords[3][32] = {"r00t", "admin", "pass1234"};
	for(int i=0; i<3; i++){
		eAdmin* adminAux = Admin_newParam(adminsUsernames[i], adminsPasswords[i]);
		if(adminAux != NULL){
			DB_insertAdmin(*adminAux);
			Admin_delete(adminAux);
		}
	}
    return outcome;
}

int harcode_ActoresFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eActor buffer;
		int argc;
		char id[20];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^,],%[^\n]\n", id, buffer.nombre, buffer.apellido);
			buffer.id = atoi(id);
			if(argc==3)
			{
				eActor* actorAux = Actor_newParam(buffer.id, buffer.nombre, buffer.apellido);
				if(actorAux != NULL){
					DB_insertActor(*actorAux);
					Actor_delete(actorAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga del actor %s %s. Recuento de argumentos incorrecto: %d/3 argc.", buffer.nombre, buffer.apellido, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}

int harcode_CastFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eCast buffer;
		int argc;
		char idPelicula[12];
		char idActor[12];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^\n]\n", idPelicula, idActor);
			buffer.idPelicula = atoi(idPelicula);
			buffer.idActor = atoi(idActor);
			if(argc==2)
			{
				eCast* castAux = Cast_newParam(buffer.idPelicula, buffer.idActor);
				if(castAux != NULL){
					DB_insertCast(*castAux);
					Cast_delete(castAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga del cast {idPelicula: %d, idActor: %d}. Recuento de argumentos incorrecto: %d/2 argc.", buffer.idPelicula, buffer.idActor, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}

int harcode_ClientesFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eCliente buffer;
		int argc;
		char dni[64];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^,],%[^\n]\n", buffer.nombre, buffer.apellido, dni);
			buffer.dni = atoi(dni);
			if(argc==3)
			{
				eCliente* clienteAux = Cliente_newParam(0, buffer.nombre, buffer.apellido, buffer.dni, 0);
				if(clienteAux != NULL){
					DB_insertCliente(*clienteAux);
					Cliente_delete(clienteAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga del cliente %s %s (DNI: %d). Recuento de argumentos incorrecto: %d/3 argc.", buffer.nombre, buffer.apellido, buffer.dni, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}

int harcode_DirectoresFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eDirector buffer;
		int argc;
		char id[20];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^\n]\n", id, buffer.nombre);
			buffer.id = atoi(id);
			if(argc==2)
			{
				eDirector* directorAux = Director_newParam(buffer.id, buffer.nombre);
				if(directorAux != NULL){
					DB_insertDirector(*directorAux);
					Director_delete(directorAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga del director %s. Recuento de argumentos incorrecto: %d/2 argc.", buffer.nombre, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}


int harcode_PeliculasFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		ePelicula buffer;
		int argc;
		char id[20];
		char year[20];
		char duracion[20];
		char idDirector[20];
		char proyectandose[20];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, buffer.titulo, year, duracion, idDirector, proyectandose);
			buffer.id = atoi(id);
			buffer.year = atoi(year);
			buffer.duracion = 0;
			buffer.idDirector = atoi(idDirector);
			buffer.proyectandose = (short) atoi(proyectandose);
			if(argc==6)
			{
				ePelicula* peliculaAux;
				peliculaAux = Pelicula_newParam(buffer.id, buffer.titulo, buffer.year, buffer.duracion, buffer.idDirector, buffer.proyectandose);
				if(peliculaAux != NULL){
					DB_insertPelicula(*peliculaAux);
					Pelicula_delete(peliculaAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga de la película %s. Recuento de argumentos incorrecto: %d/6 argc.", buffer.titulo, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}


int harcode_HorariosFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eHorario buffer;
		int argc;
		char id[20];
		char idSala[20];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^,],%[^\n]\n", id, idSala, buffer.hora);
			buffer.id = atoi(id);
			buffer.idSala = atoi(idSala);
			if(argc==3)
			{
				eHorario* horarioAux = Horario_newParam(buffer.id, buffer.idSala, buffer.hora);
				if(horarioAux != NULL){
					DB_insertHorario(*horarioAux);
					Horario_delete(horarioAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga del horario %s en sala %d. Recuento de argumentos incorrecto: %d/3 argc.", buffer.hora, buffer.idSala, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}

int harcode_SalasFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eSala buffer;
		int argc;
		char id[20];
		char asientosPorFila[20];
		char cantidadFilas[20];
		char tienePasilloCentral[20];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, buffer.tipoSala, asientosPorFila, cantidadFilas, tienePasilloCentral);
			buffer.id = atoi(id);
			buffer.asientosPorFila = atoi(asientosPorFila);
			buffer.cantidadFilas = atoi(cantidadFilas);
			buffer.tienePasilloCentral = (short) atoi(tienePasilloCentral);
			if(argc==5)
			{
				eSala* salaAux = Sala_newParam(buffer.id, buffer.tipoSala, buffer.asientosPorFila, buffer.cantidadFilas, buffer.tienePasilloCentral);
				if(salaAux != NULL){
					DB_insertSala(*salaAux);
					Sala_delete(salaAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga de la sala %d. Recuento de argumentos incorrecto: %d/5 argc.", buffer.id, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}

int harcode_TarifasFromCSV(FILE* pFile)
{
	int outcome = SUCCESS;
	if(pFile != NULL)
	{
		eTarifa buffer;
		int argc;
		char id[20];
		char precio[20];
		char readHeader[512];
		fscanf(pFile, "%s\n", readHeader);
		do{
			argc = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, buffer.tipoSala, buffer.tipoEntrada, precio);
			buffer.id = atoi(id);
			buffer.precio = (float) atof(precio);
			if(argc==4)
			{
				eTarifa* tarifaAux = Tarifa_newParam(buffer.id, buffer.tipoSala, buffer.tipoEntrada, buffer.precio);
				if(tarifaAux != NULL){
					DB_insertTarifa(*tarifaAux);
					Tarifa_delete(tarifaAux);
				}
			}
			else
			{
				char errorLog[512];
				sprintf(errorLog, "Hardcode Error - No se pudo realizar la carga de la tarifa %d: %s. Recuento de argumentos incorrecto: %d/4 argc.", buffer.id, buffer.tipoEntrada, argc);
				ErrorLog_write(errorLog);
				outcome = FAILURE;
				break;
			}
		}while(!feof(pFile));
	}
    return outcome;
}
