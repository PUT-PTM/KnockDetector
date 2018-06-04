/*
 * database_controller.c
 *
 *  Created on: 21.05.2018
 *      Author: HP 8560w
 */

#include "database_controller.h"

Database_RESULT error_code;

static char * Database_FilePath = Database_File;
Database_USER_DATA Database_Users[Database_MaxNumberOfUsers];
int Database_NumberOfUsers;
Database_USER_ID Database_LastId;

static Database_RESULT Database_ReadDatabaseFromFile(void);
static Database_RESULT Database_SaveChanges(void);
static Database_RESULT Database_WriteDatabaseToFile(void);
static void Database_SetLastId(void);

Database_RESULT Database_ChangeName(Database_USER_ID id,
		Database_USER_Name name) {
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
	int i;
	for (i = 0; Database_Users[i].id != id; ++i) {

	}
	memcpy(Database_Users[i].secret_code, secretcode,
			sizeof(Database_USER_SecretCode));
	Database_SaveChanges();
	return DB_OK;
}

Database_RESULT Database_GetDatatabase(char** database, int* numberOfBytes) {
	/* It is for bluetooth module, just send structure, no SD loading */
	*database = malloc(
	Database_ReducedTupleSize * (Database_NumberOfUsers + 1) + 1);
	int i;
	for (i = 0; i < Database_NumberOfUsers; ++i) {
		memcpy(*database + i * Database_ReducedTupleSize,
				&(Database_Users[i]).id, sizeof(Database_USER_ID));
		memcpy(
				*database + sizeof(Database_USER_ID)
						+ i * Database_ReducedTupleSize,
				&(Database_Users[i]).name, sizeof(Database_USER_Name));
		memcpy(
				*database + sizeof(Database_USER_ID)
						+ sizeof(Database_USER_Name)
						+ i * Database_ReducedTupleSize,
				&(Database_Users[i]).creation_date,
				sizeof(Database_USER_CreationDate));
		//adding information if user has recorded knock code
		if (Database_Users[i].secret_code[0] == 0) {
			memcpy(
					*database + sizeof(Database_USER_ID)
							+ sizeof(Database_USER_Name)
							+ sizeof(Database_USER_CreationDate)
							+ i * Database_ReducedTupleSize, (char) 0,
					sizeof(char));
		} else {
			memcpy(
					*database + sizeof(Database_USER_ID)
							+ sizeof(Database_USER_Name)
							+ sizeof(Database_USER_CreationDate)
							+ i * Database_ReducedTupleSize, (char) 1,
					sizeof(char));
		}
	}
	memcpy((*database + i * Database_ReducedTupleSize), (char) '\a',
			sizeof(char));
	numberOfBytes = Database_ReducedTupleSize * (Database_NumberOfUsers + 1)
			+ 1;
	return DB_OK;
}
Database_RESULT Database_AddUser(Database_USER_DATA usr) {
	usr.id = ++Database_LastId;
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
	Database_SetLastId();
	return DB_OK;

}

static void Database_SetLastId(void) {
	Database_LastId = 0;
	for (int i = 0; i < Database_NumberOfUsers; ++i) {
		if (Database_LastId < Database_Users[i].id) {
			Database_LastId = Database_Users[i].id;
		}
	}
}

static Database_RESULT Database_WriteDatabaseToFile(void) {
	char *file_content = malloc(Database_TupleSize * Database_NumberOfUsers);
	memcpy(file_content, Database_Users,
	Database_TupleSize * Database_NumberOfUsers);
	SDmodule_WriteFile(Database_FilePath, file_content);
	free(file_content);
	return DB_OK;
}

