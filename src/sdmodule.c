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



static FATFS fatfs;
static FIL file;
static FRESULT fresult;

void SDmodule_Configuration(void) {
	/* Functions from external library for enabling SD module */
	SystemInit();
	fpu_enable();
	delay_init(168);
	SPI_SD_Init();
	f_mount(0, &fatfs);
}

uint8_t SDmodule_ReadFile(char* file_name, char * buffer, UINT * loaded_bytes) {
	int file_size = 0;
	UINT loaded_bytes_nonptr=0; /* For copy to loaded_bytes */

	fresult = f_open(&file, file_name, FA_OPEN_ALWAYS | FA_READ);

	if (fresult == FR_OK) {
		file_size = f_size(&file);
		fresult = f_read(&file, &buffer[0], file_size, &loaded_bytes_nonptr);
		*loaded_bytes=loaded_bytes_nonptr;

	}
	f_close(&file);
	return fresult;
}

uint8_t SDmodule_WriteFile(char * file_name, char * file_content, UINT file_content_size) {
	unsigned int storedbytes;
	fresult = f_open(&file, file_name, FA_OPEN_ALWAYS | FA_WRITE);
	if (fresult == FR_OK) {
		fresult = f_write(&file, file_content, file_content_size, &storedbytes);

		int b = f_truncate(&file);

	}
	f_close(&file);
	int a = fresult;
	return fresult;
}
