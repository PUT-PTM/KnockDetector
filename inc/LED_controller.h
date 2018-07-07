/*
 * LED_controller.h
 *
 *  Created on: 22.06.2018
 *      Author: Przemek
 */

#ifndef LED_CONTROLLER_H_
#define LED_CONTROLLER_H_

#include "stm32f4xx.h"

#define LED_PORT GPIOA
#define LED_GREEN GPIO_Pin_6
#define LED_RED GPIO_Pin_7
#define LED_RCC RCC_AHB1Periph_GPIOA

void LED_Configuration();
void LED_RedOn();
void LED_GreenOn();
void LED_RedOff();
void LED_GreenOff();

#endif /* LED_CONTROLLER_H_ */
