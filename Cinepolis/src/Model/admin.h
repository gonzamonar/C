
#ifndef MODEL_ADMIN_H_
#define MODEL_ADMIN_H_

#include "../My_Libraries/LinkedList.h"

typedef struct{
	char username[32];
	char password[32];
}eAdmin;

#endif /* MODEL_ADMIN_H_ */

eAdmin* Admin_newParam(char* username, char* password);
void Admin_delete(eAdmin* this);

int Admin_setUsername(eAdmin* this, char* username);
int Admin_getUsername(eAdmin* this, char* dest);
int Admin_setPassword(eAdmin* this, char* password);
int Admin_getPassword(eAdmin* this, char* dest);
int DB_getAdmin(eAdmin* pAdmin, char* username);
int DB_getListaAdmins(LinkedList* pAdminList);
int DB_insertAdmin(eAdmin admin);
int DB_updateAdmin(eAdmin admin, char* username);
int DB_deleteAdmin(char* username);
int DB_DoesAdminExist(char* username);

void DB_printAdminList(void);
