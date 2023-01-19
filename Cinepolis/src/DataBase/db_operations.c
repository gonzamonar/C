
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "database.h"
#include "db_operations.h"

#include "../Error_Handling/error_log.h"
#include "sqlite3.h"


#define SUCCESS 1
#define FAILURE 0

//DB OPERATIONS
int database_getRecordByInt(void* pObject, char* table, char* column, int value, int(*pFuncCheckExistence)(int), void(*pFuncReader)(sqlite3_stmt*, void*)){
	int outcome = FAILURE;
	if(pFuncCheckExistence(value)){
		outcome = SUCCESS;
		char sql[256];
		sprintf(sql, "SELECT * FROM %s WHERE %s = \"%d\";", table, column, value);
		database_execReader(sql, pObject, pFuncReader);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Select Error - El registro con valor %s = \"%d\" no existe.", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_getRecordByIntAndInt(void* pObject, char* table, char* column1, int value1, char* column2, int value2, int(*pFuncCheckExistence)(int, int), void(*pFuncReader)(sqlite3_stmt*, void*)){
	int outcome = FAILURE;
	if(pFuncCheckExistence(value1, value2)){
		outcome = SUCCESS;
		char sql[256];
		sprintf(sql, "SELECT * FROM %s WHERE (%s = \"%d\" AND %s = \"%d\");", table, column1, value1, column2, value2);
		database_execReader(sql, pObject, pFuncReader);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Select Error - El registro con valor %s = \"%d\" y %s = \"%d\" no existe.", column1, value1, column2, value2);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_getRecordByStr(void* pObject, char* table, char* column, char* value, int(*pFuncCheckExistence)(char*), void(*pFuncReader)(sqlite3_stmt*, void*)){
	int outcome = FAILURE;
	if(pFuncCheckExistence(value)){
		outcome = SUCCESS;
		char sql[256];
		sprintf(sql, "SELECT * FROM %s WHERE %s = \"%s\";", table, column, value);
		database_execReader(sql, pObject, pFuncReader);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Select Error - El registro con valor %s = \"%s\" no existe.", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int database_insertRecordByStr(char* insert, char* column, char* value, int(*pFuncCheckExistence)(char*)){
	int outcome = FAILURE;
	if(!pFuncCheckExistence(value)){
		database_execNonQuery(insert);
		if(pFuncCheckExistence(value)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - El registro con valor %s = \"%s\" ya existe.", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_insertRecordByStrAndStr(char* insert, char* column1, char* value1, char* column2, char* value2, int(*pFuncCheckExistence)(char*, char*)){
	int outcome = FAILURE;
	if(!pFuncCheckExistence(value1, value2)){
		database_execNonQuery(insert);
		if(pFuncCheckExistence(value1, value2)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - El registro con valor %s = \"%s\" y %s = \"%s\" ya existe.", column1, value1, column2, value2);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_insertRecordByInt(char* insert, char* column, int value, int(*pFuncCheckExistence)(int)){
	int outcome = FAILURE;
	if(!pFuncCheckExistence(value)){
		database_execNonQuery(insert);
		if(pFuncCheckExistence(value)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - El registro con valor %s = \"%d\" ya existe.", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_insertRecordByIntAndInt(char* insert, char* column1, int value1, char* column2, int value2, int(*pFuncCheckExistence)(int, int)){
	int outcome = FAILURE;
	if(!pFuncCheckExistence(value1, value2)){
		database_execNonQuery(insert);
		if(pFuncCheckExistence(value1, value2)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Insert Error - El registro con valor %s = \"%d\" y %s = \"%d\" ya existe.", column1, value1, column2, value2);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int database_updateRecordByInt(char* update, char* column, int value, int(*pFuncCheckExistence)(int)){
	int outcome = 0;
	if(pFuncCheckExistence(value)){
		database_execNonQuery(update);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Update Error - No se encontraron registros con valor %s = \"%d\".", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_updateRecordByStr(char* update, char* column, char* value, int(*pFuncCheckExistence)(char*)){
	int outcome = 0;
	if(pFuncCheckExistence(value)){
		database_execNonQuery(update);
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Update Error - No se encontraron registros con valor %s = \"%s\".", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int database_deleteRecordByInt(char* table, char* column, int value, int(*pFuncCheckExistence)(int)){
	int outcome = FAILURE;
	if(pFuncCheckExistence(value)){
		char sql[256];
		sprintf(sql, "PRAGMA foreign_keys = on; DELETE FROM %s WHERE %s = \"%d\";", table, column, value);
		database_execNonQuery(sql);
		if(!pFuncCheckExistence(value)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Delete Error - No se encontraron registros con valor %s = \"%d\" no existe.", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}

int database_deleteRecordByIntAndInt(char* table, char* column1, int value1, char* column2, int value2, int(*pFuncCheckExistence)(int, int)){
	int outcome = FAILURE;
	if(pFuncCheckExistence(value1, value2)){
		char sql[256];
		sprintf(sql, "PRAGMA foreign_keys = on; DELETE FROM %s WHERE (%s = \"%d\" AND %s = \"%d\");", table, column1, value1, column2, value2);
		database_execNonQuery(sql);
		if(!pFuncCheckExistence(value1, value2)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Delete Error - No se encontraron registros con valor %s = \"%d\" y %s = \"%d\" no existe.", column1, value1, column2, value2);
		ErrorLog_write(errorLog);
	}
	return outcome;
}


int database_deleteRecordByStr(char* table, char* column, char* value, int(*pFuncCheckExistence)(char*)){
	int outcome = FAILURE;
	if(pFuncCheckExistence(value)){
		char sql[256];
		sprintf(sql, "PRAGMA foreign_keys = on; DELETE FROM %s WHERE %s = \"%s\";", table, column, value);
		database_execNonQuery(sql);
		if(!pFuncCheckExistence(value)){
			outcome = SUCCESS;
		}
	}else{
		char errorLog[256];
		sprintf(errorLog, "DB Delete Error - No se encontraron registros con valor %s = \"%s\" no existe.", column, value);
		ErrorLog_write(errorLog);
	}
	return outcome;
}
