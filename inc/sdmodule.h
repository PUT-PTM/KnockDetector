/*
 * sdmodule.h
 *
 *  Created on: 19.05.2018
 *      Author: HP 8560w
 */

#ifndef SDMODULE_H_
#define SDMODULE_H_

#include "delay.h"
#include "fpu.h"
#include "spi_sd.h"
#include "ff.h"
#include "database_parameters.h"

#define SDmodule_MaxFileSize Database_NumberOfUsers*Database_TupleSize
#define SDmodule_EndOfFileSymbol '$'

void SDmodule_Configuration(void);
char* SDmodule_ReadFile(char* fileName, UINT loadedBytes);
uint8_t SDmodule_WriteFile(char * fileName, char * fileContent);


#endif /* SDMODULE_H_ */
