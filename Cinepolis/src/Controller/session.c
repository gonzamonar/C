
#include "session.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Model/admin.h"

#define FAILURE 0
#define SUCCESS 1

static int Session_setStatus(Session* this, short status);

//Constructor & Destructor
Session* Session_new(void){
	Session* newSession = (Session*) malloc(sizeof(Session));
	if(newSession != NULL){
		controller_endSession(newSession);
	}
	return newSession;
}

void Session_delete(Session* this){
	free(this);
}

static int Session_setStatus(Session* this, short status){
	int outcome = FAILURE;
	if(this != NULL && (status == 0 || status == 1)){
		this->status = status;
		outcome = SUCCESS;
	}
	return outcome;
}


//Controller
void controller_startSession(Session* pSession, char* username){
	DB_getAdmin(&(pSession->user), username);
	Session_setStatus(pSession, 1);
}


void controller_endSession(Session* pSession){
	Admin_setUsername(&(pSession->user), "");
	Admin_setPassword(&(pSession->user), "");
	Session_setStatus(pSession, 0);
}
