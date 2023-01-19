
#include "database.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sqlite3.h"
#include "../Error_Handling/error_log.h"

#define NO_ERROR 0

static int handleError(sqlite3 *db);

//DB CONFIGURATION
DataBase initDatabase(){
	DataBase db;
	getcwd(db.path, 512);
	strcat(db.path, "\\Cinepolis.db");
	db.pointer = NULL;
	return db;
}


int openDatabase(DataBase* db){
	int outcome = NO_ERROR;
	if(sqlite3_open(db->path, &db->pointer) != SQLITE_OK)
	{
		outcome = handleError(db->pointer);
	}
	return outcome;
}


int closeDatabase(DataBase* db){
	int outcome = NO_ERROR;
	if(sqlite3_close(db->pointer) != SQLITE_OK)
	{
		outcome = handleError(db->pointer);
	}
	return outcome;
}


//ERROR HANDLER
static int handleError(sqlite3 *db)
{
	char log[512];
	sprintf(log, "DB Error Nº%d - %s", sqlite3_errcode(db), sqlite3_errmsg(db));
	ErrorLog_write(log);

	return (int) sqlite3_errmsg(db);
}


//DB QUERIES
int database_execNonQuery(char* sql){
	int outcome = NO_ERROR;
	DataBase db = initDatabase();
	openDatabase(&db);

	if(sqlite3_exec(db.pointer, sql, NULL, NULL, NULL) != SQLITE_OK)
	{
		outcome = handleError(db.pointer);
	}

	closeDatabase(&db);
	return outcome;
}


int database_execCallback(char* sql, int(*pFuncCallback)(void*,int,char**,char**)){
	int outcome = NO_ERROR;
	DataBase db = initDatabase();
	openDatabase(&db);

	if(sqlite3_exec(db.pointer, sql, pFuncCallback, 0, NULL) != SQLITE_OK)
	{
		outcome = handleError(db.pointer);
	}

	closeDatabase(&db);
	return outcome;
}


int database_execReader(char* sql, void* pObject, void(*pFuncReader)(sqlite3_stmt*, void*)){
	int outcome = NO_ERROR;
    DataBase db = initDatabase();

    openDatabase(&db);

	sqlite3_stmt *stmt;
	outcome = sqlite3_prepare_v2(db.pointer, sql, -1, &stmt, NULL);
	if(outcome != SQLITE_OK){
		handleError(db.pointer);
	}

	sqlite3_bind_int(stmt, 1, 1);
	while ((outcome = sqlite3_step(stmt)) == SQLITE_ROW){
		pFuncReader(stmt, pObject);
	}

	if (outcome != SQLITE_DONE){
		handleError(db.pointer);
	}

	sqlite3_finalize(stmt);
	closeDatabase(&db);

	return outcome;
}
