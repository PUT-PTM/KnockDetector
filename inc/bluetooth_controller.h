/*
 * bluetooth_controller.h
 *
 *  Created on: 30.05.2018
 *      Author: Przemek
 */

#ifndef BLUETOOTH_CONTROLLER_H_
#define BLUETOOTH_CONTROLLER_H_

void Bluetooth_Init(void);
void Bluetooth_NVIC_Configuration(void);
void Bluetooth_GPIO_Configuration(void);
void Bluetooth_USART_Configuration(void);
void USART3_IRQHandler(void);
//void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);
void Bluetooth_Send(char[], unsigned long);

#endif /* BLUETOOTH_CONTROLLER_H_ */
