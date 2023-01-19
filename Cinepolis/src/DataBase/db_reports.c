
#include "database.h"
#include "db_reports.h"

#include <stdio.h>
#include <string.h>


static void dbReader_singleIntReader(sqlite3_stmt* stmt, void* dest);
static void dbReader_singleFloatReader(sqlite3_stmt* stmt, void* dest);
static void dbReader_singleStrReader(sqlite3_stmt* stmt, void* dest);

static void dbReader_singleIntReader(sqlite3_stmt* stmt, void* dest){
	(*(int*) dest) = sqlite3_column_int(stmt, 0);
}

static void dbReader_singleFloatReader(sqlite3_stmt* stmt, void* dest){
	(*(float*) dest) = (float) sqlite3_column_double(stmt, 0);
}

static void dbReader_singleStrReader(sqlite3_stmt* stmt, void* dest){
	strcpy((char*)dest, (const char*)sqlite3_column_text(stmt, 0));
}

int database_GetTableMinId(char* table){
	int min = 0;
	char sql[256];
	sprintf(sql, "SELECT MIN(id) FROM %s;", table);
	database_execReader(sql, (void*)&min, dbReader_singleIntReader);
	return min;
}

int database_GetTableMaxId(char* table){
	int max = 0;
	char sql[256];
	sprintf(sql, "SELECT MAX(id) FROM %s;", table);
	database_execReader(sql, (void*)&max, dbReader_singleIntReader);
	return max;
}

int database_CountTableRecords(char* table){
	int count = 0;
	char sql[256];
	sprintf(sql, "SELECT COUNT() FROM %s;", table);
	database_execReader(sql, (void*)&count, dbReader_singleIntReader);
	return count;
}


int database_GetSingleInt(char* sql){
	int value = 0;
	database_execReader(sql, (void*)&value, dbReader_singleIntReader);
	return value;
}

float database_GetSingleFloat(char* sql){
	float value = 0;
	database_execReader(sql, (void*)&value, dbReader_singleFloatReader);
	return value;
}

void database_GetSingleStr(char* sql, char* dest){
	database_execReader(sql, (void*)dest, dbReader_singleStrReader);
}


int database_CheckRecordExistenceByInt(char* table, char* column, int value){
	int verification = 0;
	char sql[256];
	sprintf(sql, "SELECT 1 FROM %s WHERE %s = \"%d\";", table, column, value);
	database_execReader(sql, (void*)&verification, dbReader_singleIntReader);
	return verification;
}

int database_CheckRecordExistenceByIntAndInt(char* table, char* column1, int value1, char* column2, int value2){
	int verification = 0;
	char sql[256];
	sprintf(sql, "SELECT 1 FROM %s WHERE (%s = \"%d\" AND %s = \"%d\");", table, column1, value1, column2, value2);
	database_execReader(sql, (void*)&verification, dbReader_singleIntReader);
	return verification;
}

int database_CheckRecordExistenceByStr(char* table, char* column, char* value){
	int verification = 0;
	char sql[256];
	sprintf(sql, "SELECT 1 FROM %s WHERE %s = \"%s\";", table, column, value);
	database_execReader(sql, (void*)&verification, dbReader_singleIntReader);
	return verification;
}

int database_CheckRecordExistenceByStrAndStr(char* table, char* column1, char* value1, char* column2, char* value2){
	int verification = 0;
	char sql[256];
	sprintf(sql, "SELECT 1 FROM %s WHERE (%s = \"%s\" AND %s = \"%s\");", table, column1, value1, column2, value2);
	database_execReader(sql, (void*)&verification, dbReader_singleIntReader);
	return verification;
}
