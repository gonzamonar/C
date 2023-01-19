/*
 * session.h
 *
 *  Created on: 11 ene. 2023
 *      Author: GM
 */

#ifndef CONTROLLER_SESSION_H_
#define CONTROLLER_SESSION_H_

#include "../Model/admin.h"

typedef struct{
	eAdmin user;
	short status;
}Session;

#endif /* CONTROLLER_SESSION_H_ */

Session* Session_new(void);
void Session_delete(Session* this);

void controller_startSession(Session* pSession, char* username);
void controller_endSession(Session* pSession);

