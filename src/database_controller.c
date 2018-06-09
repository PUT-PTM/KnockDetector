/*
 * database_controller.c
 *
 *  Created on: 21.05.2018
 *      Author: HP 8560w
 */

#include "database_controller.h"

Database_RESULT error_code;



static Database_RESULT Database_ReadDatabaseFromFile(void);
static Database_RESULT Database_SaveChanges(void);
static Database_RESULT Database_WriteDatabaseToFile(void);
static void Database_SetLastId(void);

Database_RESULT Database_ChangeName(Database_USER_ID id,
		Database_USER_Name name) {
	int i;
	for (i = 0; Database_Users[i].id != id; ++i) {
		if (i >= Database_MaxNumberOfUsers) {
		 return UNKNOWN_ID;
		 }
	}
	memcpy(Database_Users[i].name, name, sizeof(Database_USER_Name));
	return Database_SaveChanges();
}

Database_RESULT Database_ChangeSecretCode(Database_USER_ID id,
		Database_USER_SecretCode secretcode) {
	int i;
	for (i = 0; Database_Users[i].id != id; ++i) {
		if (i==Database_MaxNumberOfUsers){
			return UNKNOWN_ID;
		}
	}
	memcpy(Database_Users[i].secret_code, secretcode,
			sizeof(Database_USER_SecretCode));
	return Database_SaveChanges();


}

Database_RESULT Database_GetDatabase(char * database) {
	for (int i = 0; i < Database_NumberOfUsers; ++i) {
		memcpy(database + i * Database_ReducedTupleSize,
				&(Database_Users[i].id), sizeof(Database_USER_ID));
		memcpy(database + sizeof(Database_USER_ID)
						+ i * Database_ReducedTupleSize,
				&(Database_Users[i].name), sizeof(Database_USER_Name));
		memcpy(database + sizeof(Database_USER_ID)
						+ sizeof(Database_USER_Name)
						+ i * Database_ReducedTupleSize,
				&(Database_Users[i].creation_date),
				sizeof(Database_USER_CreationDate));
		//adding information if user has recorded knock code
		char isRecorded=0;
		if (Database_Users[i].secret_code[0] != 0) {
			isRecorded=1;
		}
			memcpy(
					database + sizeof(Database_USER_ID)
							+ sizeof(Database_USER_Name)
							+ sizeof(Database_USER_CreationDate)
							+ i * Database_ReducedTupleSize, &isRecorded,
					sizeof(char));

			memcpy(
					database + sizeof(Database_USER_ID)
							+ sizeof(Database_USER_Name)
							+ sizeof(Database_USER_CreationDate)
							+ i * Database_ReducedTupleSize, &isRecorded,
					sizeof(char));
	}
	return DB_OK;
}

Database_RESULT Database_AddUser(Database_USER_DATA usr) {
	if (Database_NumberOfUsers<=Database_MaxNumberOfUsers) {
		usr.id = ++Database_LastId;
		/* reset secret code */
		for (int i=0; i<Database_USER_SecretCode_Size; i++) {
			usr.secret_code[i]=0;
		}

		Database_Users[Database_NumberOfUsers] = usr;
		++Database_NumberOfUsers;
		return Database_SaveChanges();

	}
	else {
		return DB_FULL;
	}
}

Database_RESULT Database_DeleteUser(Database_USER_ID id) {
	int index;
	for (index = 0; Database_Users[index].id != id; ++index) {
		if (index==Database_MaxNumberOfUsers) {
			return UNKNOWN_ID;
		}
	}
	Database_NumberOfUsers-=1;
	for (; index < Database_NumberOfUsers; ++index) { //clean array after deleting
		Database_Users[index] = Database_Users[index + 1];
	}

	return Database_SaveChanges();

}

void Database_Configuration(void) {
	SDmodule_Configuration();
	Database_ReadDatabaseFromFile();

}

static Database_RESULT Database_SaveChanges(void) {
	return Database_WriteDatabaseToFile();
}

static Database_RESULT Database_ReadDatabaseFromFile(void) {
	char buffer[Database_MaximumSize];
	UINT loadedBytes = 0;
	if (SDmodule_ReadFile(Database_FilePath, &buffer, &loadedBytes))
	{
		return DB_SDERROR;
	}
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
	UINT file_content_size = Database_TupleSize * Database_NumberOfUsers;
	char *file_content = malloc(file_content_size);
	memcpy(file_content, Database_Users,
			file_content_size);

	if(SDmodule_WriteFile(Database_FilePath, file_content,file_content_size)) {
		return DB_SDERROR;
	}
	free(file_content);
	return DB_OK;
}

