/*
 * bluetooth_controller.h
 *
 *  Created on: 30.05.2018
 *      Author: Przemek
 */

#ifndef BLUETOOTH_CONTROLLER_H_
#define BLUETOOTH_CONTROLLER_H_

#include "stm32f4xx.h"
#include "detector_controller.h"
#include "database_controller.h"


#define Bluetooth_GPIO_RXD GPIO_Pin_11
#define Bluetooth_GPIO_TXD GPIO_Pin_10
#define Bluetooth_GPIO_Port GPIOC
#define Bluetooth_GPIO_RCC RCC_AHB1Periph_GPIOC

void Bluetooth_Configuration(void);
void USART3_IRQHandler(void);
//void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);
void Bluetooth_Send(char[], unsigned long);

#endif /* BLUETOOTH_CONTROLLER_H_ */
