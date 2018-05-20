/*
 * sdmodule.c
 *
 *  Created on: 19.05.2018
 *      Author: HP 8560w
 */


#include "sdmodule.h"



/* PB13 - SCK
 * PB14 - MISO
 * PB15 - MOSI
 * PB11 - CHIP SELECT */



FATFS fatfs;
static FRESULT fresult;

void SDmodule_Configuration(void) {
	/* Functions from external library for enabling SD module */
	SystemInit();
	fpu_enable();
	delay_init(168);
	SPI_SD_Init();
}

char* SDmodule_ReadFile(char* fileName, UINT loadedBytes) {
	FIL file;
	loadedBytes = 0;
	char * buffer;
	fresult = f_mount(0, &fatfs);

	if (fresult == FR_OK) {
		fresult = f_open(&file, fileName, FA_OPEN_ALWAYS | FA_READ);

		if (fresult == FR_OK) {
			int fileSize = f_size(&file);
			fresult = f_read(&file, buffer, fileSize, &loadedBytes);

			buffer[fileSize] = SDmodule_EndOfFileSymbol; //end of file
			fresult = f_close(&file);
			return buffer;
		} else {
			/* TO DO: ERROR CODE */
		}

	}
	else {
		/* TO DO: ERROR CODE */
	}
}

uint8_t SDmodule_WriteFile(char * fileName, char * fileContent) {
	FIL file;
	unsigned int storedBytes;
	int fileContentSize = SDmodule_MaxFileSize;

	fresult = f_mount(0, &fatfs);

	if (fresult == FR_OK) {
		fresult = f_open(&file, fileName, FA_OPEN_ALWAYS | FA_WRITE);

		if (fresult == FR_OK) {
			fresult = f_write(&file, fileContent, fileContentSize, &storedBytes);
			fresult = f_close(&file);
		}
	}

	return fresult;
}
