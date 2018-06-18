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






int main(void) {
	Controller_Configuration();

	for (;;)
		;
}

void Controller_Configuration(void) {
	DiodesOnBoard_Config();
	Database_Configuration();
	Bluetooth_Configuration();
	Detector_Configuration();
	Lock_Configuration();
}

void DiodesOnBoard_Config(void) {
	RCC_AHB1PeriphClockCmd(DIODES_ONBOARD_RCC, ENABLE);
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
