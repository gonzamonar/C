
#include "login.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../Model/admin.h"
#include "../DataBase/database.h"
#include "../IO_Libraries/console.h"
#include "../IO_Libraries/IO_str.h"
#include "../View/decoration.h"
#include "../View/user_interface.h"


#define ACCESS_DENIED 0
#define ACCESS_GRANTED 1

static int TryLogin(char* username, char* password);
static int CheckPassword(char* username, char* password);
static void printLoginScreen(short flag, char* username, short visualConfig);

static int TryLogin(char* username, char* password){
	int result = -1;
    if (DB_DoesAdminExist(username))
    {
        result = 0;
        if (CheckPassword(username, password))
        {
            result = 1;
        }
    }
	return result;
}


static int CheckPassword(char* username, char* password){
	int verification = ACCESS_DENIED;
	eAdmin adminBuffer;
	DB_getAdmin(&adminBuffer, username);

	if(strcmp(adminBuffer.password, password)==0){
		verification = ACCESS_GRANTED;
	}
	Admin_delete(&adminBuffer);
	return verification;
}


static void printLoginScreen(short flag, char* username, short visualConfig){
	system("cls");
	(visualConfig) ? decoration_printCinepolisLogo() : printf("\n\n");
	SetConsoleMenuTitleColor();
	printf("     *** Menu de Login ***\n");
	SetConsoleStandardColor();
	printf("     -----------------------------------------------------------------------------\n");
	if(flag){
		printf("      Usuario: %s\n", username);
	}else{
		printf("     Usuario por defecto: admin/admin.\n");
	}
}


int controller_Login(Session* pSession, short visualConfig)
{
	short flag = 0;
	short outcome = 0;
	short stage = 1;
	short login;
	char username[32];
	char password[32];

	do{
		fflush(stdin);
		printLoginScreen(flag, username, visualConfig);
		switch (stage){
			case 1:	//get username
					if(IO_getUsername(username, 32)){
						flag = 1;
						stage++;
					}else{
						printf("\n     Ha superado el máximo de intentos permitidos.");
						stage = 4;
					}
					break;

			case 2:	//get password
					if(IO_getPassword(password, 32)){
						stage++;
					}else{
						printf("\n     Ha superado el máximo de intentos permitidos.");
						stage = 4;
					}
					break;

			case 3:	//verification
					login = TryLogin(username, password);
					switch (login)
					{
						case -1:
							printf("\n     Usuario inexistente.");
							break;
						case 0:
							printf("\n     Contraseña incorrecta.");
							break;
						case 1:
							controller_startSession(pSession, username);
							if(pSession != NULL){
								printf("\n     Acceso concedido.");
								outcome = 1;
							}else{
								printf("\n     ERROR: No se pudo crear la sesión.");
							}
							break;
					}
					stage++;
					break;
		}
	}while(stage != 4);
	pause();
    return outcome;
}
