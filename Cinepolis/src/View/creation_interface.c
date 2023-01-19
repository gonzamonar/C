

#include "creation_interface.h"


void View_printAdminCreationMenu(int* flags, char* username, char* password){
	system("cls");
	printf("\n\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
	printf(" |-------------------------------------  ***   ALTA DE ADMIN  ***  -------------------------------------|\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" |                                                                                                      |\n");
	if(flags[0]){
		printf(" |  - USUARIO:                   %-50s                     |\n", username);
	}else{
		printf(" |  - USUARIO:                   %-20s                                                   |\n", "Sin Ingresar");
	}

	if(flags[1]){
		printf(" |  - CONTRASEŅA:                %-50s                     |\n", password);
	}else{
		printf(" |  - CONTRASEŅA:                %-20s                                                   |\n", "Sin Ingresar");
	}
	printf(" |                                                                                                      |\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
}
