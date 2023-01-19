
#ifndef DATABASE_DB_OPERATIONS_H_
#define DATABASE_DB_OPERATIONS_H_



#endif /* DATABASE_DB_OPERATIONS_H_ */


int database_getRecordByInt(void* pObject, char* table, char* column, int value, int(*pFuncCheckExistence)(int), void(*pFuncReader)(sqlite3_stmt*, void*));
int database_getRecordByIntAndInt(void* pObject, char* table, char* column1, int value1, char* column2, int value2, int(*pFuncCheckExistence)(int, int), void(*pFuncReader)(sqlite3_stmt*, void*));
int database_getRecordByStr(void* pObject, char* table, char* column, char* value, int(*pFuncCheckExistence)(char*), void(*pFuncReader)(sqlite3_stmt*, void*));

int database_insertRecordByStr(char* insert, char* column, char* value, int(*pFuncCheckExistence)(char*));
int database_insertRecordByStrAndStr(char* insert, char* column1, char* value1, char* column2, char* value2, int(*pFuncCheckExistence)(char*, char*));
int database_insertRecordByInt(char* insert, char* column, int value, int(*pFuncCheckExistence)(int));
int database_insertRecordByIntAndInt(char* insert, char* column1, int value1, char* column2, int value2, int(*pFuncCheckExistence)(int, int));

int database_updateRecordByInt(char* update, char* column, int value, int(*pFuncCheckExistence)(int));
int database_updateRecordByStr(char* update, char* column, char* value, int(*pFuncCheckExistence)(char*));

int database_deleteRecordByInt(char* table, char* column, int value, int(*pFuncCheckExistence)(int));
int database_deleteRecordByIntAndInt(char* table, char* column1, int value1, char* column2, int value2, int(*pFuncCheckExistence)(int, int));
int database_deleteRecordByStr(char* table, char* column, char* value, int(*pFuncCheckExistence)(char*));

