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

#define DIODES_ON_BOARD  GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15

char* filename = "20_05_2018.txt";
char* buffer= "123456789";

void DiodesOnBoard_Config(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	//DIODY
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = DIODES_ON_BOARD;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Zaswiec(void) {

	GPIO_SetBits(GPIOD, DIODES_ON_BOARD);
}

int main(void) {
	/* Only for tests */
	Sensor_Configuration();
	DiodesOnBoard_Config();
	if(!SDmodule_WriteFile(filename, buffer)){
		Zaswiec();
	}
	for (;;)
		;
}

void Controller_Configuration(void) {

}
