/*
 * database_parameters.h
 *
 *  Created on: 20.05.2018
 *      Author: HP 8560w
 */

#ifndef DATABASE_PARAMETERS_H_
#define DATABASE_PARAMETERS_H_

#include "stm32f4xx.h"

#define Database_USER_Name_Size 20
#define Database_USER_CreationDate_Size 20
#define Database_USER_SecretCode_Size 20

typedef uint16_t Database_USER_ID;
typedef char Database_USER_Name[Database_USER_Name_Size];
typedef char Database_USER_CreationDate[Database_USER_CreationDate_Size];
typedef int Database_USER_SecretCode[Database_USER_SecretCode_Size];

typedef struct {
	Database_USER_ID id;
	Database_USER_Name name;
	/* char password[20]; */
	Database_USER_CreationDate creation_date;
	Database_USER_SecretCode secret_code;
} Database_USER_DATA;

#define Database_NumberOfUsers 20
#define Database_TupleSize sizeof(Database_USER_DATA)
#define Database_MaximumSize Database_NumberOfUsers*Database_TupleSize

#define Database_File "database.txt"








#endif /* DATABASE_PARAMETERS_H_ */
