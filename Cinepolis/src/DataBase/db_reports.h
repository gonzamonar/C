

#ifndef DATABASE_DB_REPORTS_H_
#define DATABASE_DB_REPORTS_H_



#endif /* DATABASE_DB_REPORTS_H_ */



int database_GetTableMinId(char* table);
int database_GetTableMaxId(char* table);
int database_CountTableRecords(char* table);

int database_GetSingleInt(char* sql);
float database_GetSingleFloat(char* sql);
void database_GetSingleStr(char* sql, char* dest);
int database_CheckRecordExistenceByInt(char* table, char* column, int value);
int database_CheckRecordExistenceByIntAndInt(char* table, char* column1, int value1, char* column2, int value2);
int database_CheckRecordExistenceByStr(char* table, char* column, char* value);
int database_CheckRecordExistenceByStrAndStr(char* table, char* column1, char* value1, char* column2, char* value2);
