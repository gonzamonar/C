
#include "admin.h"
#include "macros.h"

static eAdmin* Admin_new(void);

//Constructor & Destructor
static eAdmin* Admin_new(void){
	eAdmin* newAdmin = (eAdmin*) malloc(sizeof(eAdmin));
	if(newAdmin != NULL){
		strcpy(newAdmin->username,"");
		strcpy(newAdmin->password,"");
	}
	return newAdmin;
}

eAdmin* Admin_newParam(char* username, char* password){
	eAdmin* newAdmin = Admin_new();
	int argc = 0;
	argc += Admin_setUsername(newAdmin, username);
	argc += Admin_setPassword(newAdmin, password);

	if(argc!=2){
		Admin_delete(newAdmin);
		newAdmin = NULL;

		char errorLog[512];
		sprintf(errorLog, "Constructor Error - No se pudo crear el objeto eAdmin %s %s.", username, password);
		ErrorLog_write(errorLog);
	}
	return newAdmin;
}

void Admin_delete(eAdmin* this){
	free(this);
}


//Attributes
int Admin_setUsername(eAdmin* this, char* username){
	int outcome = FAILURE;
	if(this != NULL && username != NULL){
		str_tolower(username);
		strcpy(this->username, username);
		outcome = SUCCESS;
	}
	return outcome;
}

int Admin_getUsername(eAdmin* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->username);
		outcome = SUCCESS;
	}
	return outcome;
}

int Admin_setPassword(eAdmin* this, char* password){
	int outcome = FAILURE;
	if(this != NULL && password != NULL){
		strcpy(this->password, password);
		outcome = SUCCESS;
	}
	return outcome;
}

int Admin_getPassword(eAdmin* this, char* dest){
	int outcome = FAILURE;
	if(this != NULL && dest != NULL){
		strcpy(dest, this->password);
		outcome = SUCCESS;
	}
	return outcome;
}


//Database Operations
static void dbReader_getAdmin(sqlite3_stmt* stmt, void* admin);
static void dbReader_getAdminList(sqlite3_stmt* stmt, void* list);
static int dbCallback_printAdminList(void *unused, int argc, char **argv, char **colName);

int DB_getAdmin(eAdmin* pAdmin, char* username){
	return database_getRecordByStr((void*) pAdmin, "Admins", "Admins.username", username, DB_DoesAdminExist, dbReader_getAdmin);
}

int DB_getListaAdmins(LinkedList* pAdminList){
	return database_execReader("SELECT * FROM Admins;", (void*) pAdminList, dbReader_getAdminList);
}

static void dbReader_getAdmin(sqlite3_stmt* stmt, void* admin){
	const unsigned char* username = sqlite3_column_text(stmt, 0);
	const unsigned char* password = sqlite3_column_text(stmt, 1);

	Admin_setUsername((eAdmin*)admin, (char*)username);
	Admin_setPassword((eAdmin*)admin, (char*)password);
}

static void dbReader_getAdminList(sqlite3_stmt* stmt, void* list){
	const unsigned char* username = sqlite3_column_text(stmt, 0);
	const unsigned char* password = sqlite3_column_text(stmt, 1);

	eAdmin* buffer = Admin_newParam((char*)username, (char*)password);
	if(buffer != NULL){
		ll_add((LinkedList*) list, (void*) buffer);
	}
}

int DB_insertAdmin(eAdmin admin){
	char sql_insert[256];
	sprintf(sql_insert, "INSERT INTO Admins VALUES(\"%s\", \"%s\");", admin.username, admin.password);
	return database_insertRecordByStr(sql_insert, "Admins.username", admin.username, DB_DoesAdminExist);
}


int DB_updateAdmin(eAdmin admin, char* username){
	char sql_update[256];
	sprintf(sql_update, "UPDATE Admins SET username=\"%s\", password=\"%s\" WHERE Admins.username = \"%s\";", admin.username, admin.password, username);
	return database_updateRecordByStr(sql_update, "Admins.username", username, DB_DoesAdminExist);
}


int DB_deleteAdmin(char* username){
	return database_deleteRecordByStr("Admins", "Admins.username", username, DB_DoesAdminExist);
}


void DB_printAdminList(void){
	printf("     %-20s | %-20s\n", "username", "password");
	printf(" ----------------------------------------------\n");
	database_execCallback("SELECT * FROM Admins;", dbCallback_printAdminList);
}


static int dbCallback_printAdminList(void *unused, int argc, char **argv, char **colName){
	for(int i=0; i<argc; i++)
	{
		if(strcmp(colName[i], "username")==0){
			printf("     %-20s | ", argv[i]);
		}else{
			printf("%-20s\n", argv[i]);
		}
	}
	return 0;
}

int DB_DoesAdminExist(char* username){
	return database_CheckRecordExistenceByStr("Admins", "Admins.username", username);
}
