

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../DataBase/database.h"
#include "../DataBase/db_structure.h"
#include "../IO_Libraries/console.h"
#include "../IO_Libraries/IO_num.h"
#include "../Model/funcion.h"
#include "../Model/compra.h"
#include "../Model/cliente.h"
#include "../Model/pelicula.h"
#include "../View/user_interface.h"
#include "hardcoder.h"


static int doesFolderExist(char* path, char* folderName);


void controller_automatizacionFunciones(){
	int cantidad = 0;
	printf("\n\n");
	printf("   Durante este proceso se generarán Funciones de forma aleatoria.\n");
	printf("   El sistema eligirá aleatoriamente una Fecha, Sala y Horario libres,\n");
	printf("   una película ya existente y si la Función será o no subtitulada.\n\n");

	printf("   El proceso conlleva la creación de ubicaciones (140 promedio) para cada Función,\n");
	printf("   tomando alrededor de 1m 30s / 50 funciones y, una vez iniciado, no se puede detener,\n");
	printf("   de modo que ");
	SetConsoleErrorColor();
	printf("no recomendamos crear más de 100 funciones por ejecución");
	SetConsoleStandardColor();
	printf(".\n\n");

	if(IO_getInteger(&cantidad, "   ¿Cuántas Funciones desea generar? (0 para Cancelar) ", "\n   Entrada inválida, el rango permitido es de 1 a 500.", 0, 500, 3)){
		if(cantidad>0){
			int funciones_inicial = database_CountTableRecords("Funciones");
			int ubicaciones_inicial = database_CountTableRecords("Ubicaciones");
			Automatizacion_generarFunciones(cantidad);
			int funciones_final = database_CountTableRecords("Funciones");
			int ubicaciones_final = database_CountTableRecords("Ubicaciones");
			//system("cls");
			printf("\n\n Creación de Funciones finalizada.\n\n");
			printf(" Se crearon %d funciones y %d localidades nuevas.\n", funciones_final-funciones_inicial, ubicaciones_final-ubicaciones_inicial);
			printf(" La base de datos cuenta actualmente con %d registros de Funciones y %d de Ubicaciones.\n\n\n", funciones_final, ubicaciones_final);
			fflush(stdin);
			pause();
		}
	}
}


void controller_automatizacionCompras(){
	int cantidad = 0;
	printf("\n\n");
	printf("   Durante este proceso se simularán Ventas de forma aleatoria.\n");
	printf("   El sistema iniciará una Compra, eligiendo al azar un Cliente ya existente.\n");
	printf("   Luego seleccionará una Función y Ubicación disponibles y repetirá esta acción\n");
	printf("   hasta llegar a n Entradas en cada proceso de Compra realizado por un Cliente.\n\n");

	printf("   En promedio se venden dos Entradas por cada proceso de Compra y simular 500 compras\n");
	printf("   toma 1m 30s. Una vez iniciada la simulación no se puede detener. En caso de agotarse\n");
	printf("    las entradas para todas las funciones, la simulación se detiene automáticamente.\n\n");

	if(IO_getInteger(&cantidad, "   ¿Cuántas Ventas desea simular? (0 para Cancelar) ", "\n   Entrada inválida, el rango permitido es de 1 a 5000.", 0, 5000, 3)){
		if(cantidad>0){
			int entradas_inicial = database_CountTableRecords("Entradas");
			int compras_inicial = database_CountTableRecords("Compras");
			Automatizacion_generarCompras(cantidad);
			int entradas_final = database_CountTableRecords("Entradas");
			int compras_final = database_CountTableRecords("Compras");
			printf("\n\n Simulación de Ventas finalizada.\n\n");
			printf(" Se realizaron %d compras y se vendieron %d entradas.\n", compras_final-compras_inicial, entradas_final-entradas_inicial);
			printf(" La base de datos cuenta actualmente con %d registros de compras y %d de entradas vendidas.\n\n\n", compras_final, entradas_final);
			fflush(stdin);
			pause();
		}
	}
}



void controller_restartDatabase(){
	system("cls");
	char confirmation;
	char workingDir[512];
	char hardcodeFolder[] = {"\\CSV"};
	getcwd(workingDir, 512);
	SetConsoleGreenColor();
	printf("\n\n\n\n   Directorio de la Base de Datos: %s.\n\n", workingDir);
	SetConsoleStandardColor();

	int folderExistence = doesFolderExist(workingDir, hardcodeFolder);

	printf("   Esta acción eliminará y creará nuevamente la Base de Datos,\n");
	printf("   borrando todos los registros que se hayan cargado manualmente.\n");
	printf("   Se restaurarán automáticamente los registros de incluidos en la carpeta 'CSV'\n");
	if(folderExistence){
		printf("   ubicada en el directorio de trabajo. No la mueva durante el proceso. ");
	}else{
		printf("   no encontrada en el directorio de trabajo. Cópiela allí antes de iniciar el proceso.");
	}

	SetConsoleErrorColor();
	printf("\n\n   Importante: Esta acción NO se puede deshacer.\n\n");
	SetConsoleStandardColor();

	int confirm = IO_getConfirm(&confirmation, "  ¿Desea confirmar el reinicio de la Base de Datos? [S/N]: ", "  Opción inválida.", 3);
	if(confirm && confirmation == 'S'){
		printf("\n\n");
		if(doesFolderExist(workingDir, hardcodeFolder)){
			printf("  Eliminando tablas.\n");
			DB_dropEveryTable();
			printf("  Creando tablas.\n");
			DB_createEveryTable();

			//Hardcode
			printf("  Iniciando proceso de carga desde CSV.\n");
			HardcodeAdmins();
			Hardcode("Clientes.csv", harcode_ClientesFromCSV);
			Hardcode("Directores.csv", harcode_DirectoresFromCSV);
			Hardcode("Peliculas.csv", harcode_PeliculasFromCSV);
			Hardcode("Actores.csv", harcode_ActoresFromCSV);
			Hardcode("Cast.csv", harcode_CastFromCSV);
			Hardcode("Horarios.csv", harcode_HorariosFromCSV);
			Hardcode("Salas.csv", harcode_SalasFromCSV);
			Hardcode("Tarifas.csv", harcode_TarifasFromCSV);
			printf("  Carga de registros desde CSV finalizada.\n");

			//Automation
			printf("  Randomizando duración de Películas.\n");
			automatizacion_Peliculas_randomizarDuracion();
			automatizacion_Peliculas_randomizarProyectandose();
			printf("  Randomizando calidad de socio de Clientes.\n");
			automatizacion_Clientes_randomizarSocio();

			printf("\n  Reinicio de Base de Datos concluido.\n");
		}else{
			SetConsoleErrorColor();
			printf("  Proceso cancelado: No se encontró la carpeta CSV en el directorio de trabajo.\n");
			SetConsoleStandardColor();
		}
		pause();
	}
}


static int doesFolderExist(char* path, char* folderName){
	int outcome = 0;
	struct stat st = {0};
	getcwd(path, 512);
	strcat(path, folderName);

	if(stat(path, &st)==0){
		outcome = 1;
	}
	return outcome;
}
