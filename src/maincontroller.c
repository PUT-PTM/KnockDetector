/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "maincontroller.h"





void Zaswiec(void) {
	GPIO_SetBits(GPIOD, DIODES_ONBOARD_PINS);
}

int main(void) {
<<<<<<< HEAD
	/* Only for tests */
	Sensor_Configuration();
	DiodesOnBoard_Config();
	SDmodule_Configuration();
	/*UINT loadedBytes;
	char dane[3000];
	SDmodule_ReadFile(filename, &dane, &loadedBytes);*/
	/*if (c2[0]=='1') {
	Zaswiec();
	}*/
=======
	Controller_Configuration();

>>>>>>> 8e1e5ac0738cca8f9e5c2a308cd7003330356a75
	for (;;)
		;
}

void Controller_Configuration(void) {
	DiodesOnBoard_Config();
	Bluetooth_Configuration();
	Database_Configuration();
}

void DiodesOnBoard_Config(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	//DIODY
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = DIODES_ONBOARD_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DIODES_ONBOARD_PORT, &GPIO_InitStructure);
}
