/*
 * database_controller.c
 *
 *  Created on: 21.05.2018
 *      Author: HP 8560w
 */

#include "database_controller.h"
#include <stdlib.h>

Database_USER_ID Database_LastID;
Database_RESULT error_code;

static char * Database_FilePath = Database_File;

static Database_RESULT Database_ReadDatabaseFromFile(void);
static Database_RESULT Database_SaveChanges(void);
static Database_RESULT Database_WriteDatabaseToFile(void);

Database_RESULT Database_ChangeName(Database_USER_ID id,
		Database_USER_Name name) {
	/* TO DO: Database_Users -> iteration, find, change,
	 * and Database_SaveChanges */
	int i;
	for (i = 0; Database_Users[i].id != id; ++i) {
		/*if (i >= Database_MaxNumberOfUsers) {
		 return UNKNOWN_ID;
		 }*/
	}
	memcpy(Database_Users[i].name, name, sizeof(Database_USER_Name));
	Database_SaveChanges();
	return DB_OK;
}

Database_RESULT Database_ChangeSecretCode(Database_USER_ID id,
		Database_USER_SecretCode secretcode) {
	/* TO DO: Database_Users -> iteration, find, change,
	 * and Database_SaveChanges */
	int i;
	for (i = 0; Database_Users[i].id != id; ++i) {

	}
	memcpy(Database_Users[i].secret_code, secretcode,
			sizeof(Database_USER_SecretCode));
	Database_SaveChanges();
	return DB_OK;
}

Database_RESULT Database_GetDatatabase(char* database) {
	/* It is for bluetooth module, just send structure, no SD loading */
	database = malloc(sizeof(Database_USER_DATA) * (Database_NumberOfUsers + 1));
	for (int i = 0; i < Database_NumberOfUsers; ++i) {

	}
	return DB_OK;
}
Database_RESULT Database_AddUser(Database_USER_DATA usr) {
	Database_Users[Database_NumberOfUsers] = usr;
	++Database_NumberOfUsers;
	return DB_OK;
}

Database_RESULT Database_DeleteUser(Database_USER_ID id) {
	int index;
	for (index = 0; Database_Users[index].id != id; ++index) {
	}
	--Database_NumberOfUsers;
	for (; index < Database_NumberOfUsers; ++index) { //clean array after deleting
		Database_Users[index] = Database_Users[index + 1];
	}
	return DB_OK;
}

void Database_Configuration(void) {
	SDmodule_Configuration();
	Database_ReadDatabaseFromFile();
}

static Database_RESULT Database_SaveChanges(void) {
	Database_WriteDatabaseToFile();
	Database_ReadDatabaseFromFile();
	/* TO DO: return of the code with higher value */
	return DB_OK;
}

static Database_RESULT Database_ReadDatabaseFromFile(void) {
	char buffer[Database_MaximumSize];
	UINT loadedBytes = 0;
	SDmodule_ReadFile(Database_FilePath, &buffer, loadedBytes);
	Database_NumberOfUsers = loadedBytes / Database_TupleSize;
	memcpy(Database_Users, &buffer[0], loadedBytes);
	return DB_OK;
	/* TO DO: Skrocenie buffer do loadedBytes i zapisanie do */

}

static Database_RESULT Database_WriteDatabaseToFile(void) {
	char *file_content = malloc(Database_TupleSize * Database_NumberOfUsers);
	memcpy(file_content, Database_Users, Database_TupleSize * Database_NumberOfUsers);
	SDmodule_WriteFile(Database_FilePath, file_content);
	free(file_content);
	return DB_OK;
}

