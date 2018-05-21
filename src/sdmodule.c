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
FIL file;
static FRESULT fresult;

void SDmodule_Configuration(void) {
	/* Functions from external library for enabling SD module */
	SystemInit();
	fpu_enable();
	delay_init(168);
	SPI_SD_Init();
}

uint8_t SDmodule_ReadFile(char* file_name, char * buffer, UINT * loaded_bytes) {
	int file_size = 0;
	UINT loaded_bytes_nonptr=0;

	fresult = f_mount(0, &fatfs);

	if (fresult == FR_OK) {
		fresult = f_open(&file, file_name, FA_OPEN_ALWAYS | FA_READ);

		if (fresult == FR_OK) {
			file_size = f_size(&file);
			fresult = f_read(&file, &buffer[0], file_size, &loaded_bytes_nonptr);
			*loaded_bytes=loaded_bytes_nonptr;
			/*buffer[fileSize] = SDmodule_EndOfFileSymbol; //end of file*/
			fresult = f_close(&file);
		}
	}
	return fresult;
}

uint8_t SDmodule_WriteFile(char * file_name, char * file_content) {
	unsigned int storedbytes;
	int file_content_size = SDmodule_MaxFileSize;

	fresult = f_mount(0, &fatfs);

	if (fresult == FR_OK) {
		fresult = f_open(&file, file_name, FA_OPEN_ALWAYS | FA_WRITE);

		if (fresult == FR_OK) {
			fresult = f_write(&file, file_content, file_content_size, &storedbytes);
			fresult = f_close(&file);
		}
	}

	return fresult;
}
