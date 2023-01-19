
#ifndef MODEL_DATABASE_H_
#define MODEL_DATABASE_H_

#include "sqlite3.h"
#include "db_operations.h"
#include "db_reports.h"
#include "../My_Libraries/LinkedList.h"

typedef struct{
	char path[256];
	sqlite3 *pointer;
}DataBase;

#endif /* MODEL_DATABASE_H_ */

DataBase initDatabase();
int openDatabase(DataBase* db);
int closeDatabase(DataBase* db);
int database_execNonQuery(char* sql);
int database_execCallback(char* sql, int(*callback)(void*,int,char**,char**));
int database_execReader(char* sql, void* pObject, void(*pFuncReader)(sqlite3_stmt*, void*));

