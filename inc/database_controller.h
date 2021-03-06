/*
 * database_controller.h
 *
 *  Created on: 21.05.2018
 *      Author: HP 8560w
 */

#ifndef DATABASE_CONTROLLER_H_
#define DATABASE_CONTROLLER_H_

#include "database_parameters.h"
#include "sdmodule.h"
#include <stdlib.h>

typedef enum {
	DB_OK = 0,
	UNKNOWN_ID = 1,
	DB_FULL = 2,
	DB_SDERROR = 3,
} Database_RESULT;


Database_RESULT Database_ChangeName(Database_USER_ID id, Database_USER_Name name);
Database_RESULT Database_ChangeSecretCode(Database_USER_ID id, Database_USER_SecretCode secretcode);
Database_RESULT Database_GetDatabase(char * database);
Database_RESULT Database_AddUser(Database_USER_DATA);
Database_RESULT Database_DeleteUser(Database_USER_ID id);
void Database_Configuration(void);

static char * Database_FilePath = Database_File;
Database_USER_DATA Database_Users[Database_MaxNumberOfUsers];
int Database_NumberOfUsers;
Database_USER_ID Database_LastId;


#endif /* DATABASE_CONTROLLER_H_ */
