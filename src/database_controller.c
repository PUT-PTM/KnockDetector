/*
 * database_controller.c
 *
 *  Created on: 21.05.2018
 *      Author: HP 8560w
 */

#include "database_controller.h"

Database_USER_DATA Database_Users[Database_NumberOfUsers];
static const char * Database_FilePath = Database_File;
Database_USER_ID Database_LastID;
DATABASE_Result error_code;



DATABASE_Result Database_ChangeName(Database_USER_ID id, Database_USER_Name name) {
	/* TO DO: Database_Users -> iteration, find, change,
	 * and Database_SaveChanges */
}
DATABASE_Result Database_ChangeSecretCode(Database_USER_ID id, Database_USER_SecretCode secretcode) {
	/* TO DO: Database_Users -> iteration, find, change,
		 * and Database_SaveChanges */
}
DATABASE_Result Database_GetDatabase(void) {
	/* It is for bluetooth module */
}
DATABASE_Result Database_AddUser(Database_USER_DATA) {

}


void Database_Configuration(void){
	SDmodule_Configuration();
	Database_LoadDatabase();
}

static DATABASE_Result Database_SaveChanges(void) {
	Database_SaveDatabase();
	Database_LoadDatabase();
	/* TO DO: return of the code with higher value */
}

static DATABASE_Result Database_SaveDatabase(void) {
	/* TO DO: Zapisanie struktury do tablicy charow */
}


static DATABASE_Result Database_LoadDatabase(void) {
	char * database_data;
	Database_ReadDatabaseFromFile(&database_data);
	/* TO DO: Przetworzenie tablicy charow i zapisanie do tablicy uzytkownikow Database_Users */

}


static DATABASE_Result Database_ReadDatabaseFromFile(char * database_data) {
	char * buffer[Database_MaximumSize];
	UINT loadedBytes=0;
	SDModule_ReadFile(Database_FilePath, &buffer, &loadedBytes);
	/* TO DO: Skrocenie buffer do loadedBytes i zapisanie do */

}

static DATABASE_Result Database_WriteDatabaseToFile(void) {

	SDmodule_WriteFile(filename, char * file_content);


}








