/*
 * LED_controller.c
 *
 *  Created on: 22.06.2018
 *      Author: Przemek
 */

#include "LED_controller.h"

void LED_Configuration() {
	RCC_AHB1PeriphClockCmd(LED_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_GREEN | LED_RED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void LED_GreenOn() {
	GPIO_SetBits(LED_PORT, LED_GREEN);
}

void LED_GreenOff() {
	GPIO_SetBits(LED_PORT, LED_GREEN);
}

void LED_RedOn() {
	GPIO_SetBits(LED_PORT, LED_RED);
}

void LED_RedOff() {
	GPIO_SetBits(LED_PORT, LED_RED);
}
