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

typedef enum {
	DB_OK = 0,
	DB_SDERROR,
} DATABASE_Result;

DATABASE_Result Database_ChangeName(Database_USER_ID id, Database_USER_Name name);
DATABASE_Result Database_ChangeSecretCode(Database_USER_ID id, Database_USER_SecretCode secretcode);
DATABASE_Result Database_GetDatabase(void);
DATABASE_Result Database_AddUser(Database_USER_DATA);
void Database_Configuration(void);



#endif /* DATABASE_CONTROLLER_H_ */
