/*
 * bluetooth_controller.c
 *
 *  Created on: 30.05.2018
 *      Author: Przemek
 */

#include "bluetooth_controller.h"
#include <stdlib.h>

static void Bluetooth_GPIO_Configuration(void);
static void Bluetooth_USART_Configuration(void);
static void Bluetooth_NVIC_Configuration(void);
static void Bluetooth_Receive(char*, int);

int CompareStrings(char* in1, char* in2) {
	int i = 0;
	while (in1[i] == in2[i]) {
		if ((in1[i] && in2[i])==0) {
			return 1;//returns 1 if strings are the same
		}
		++i;
	}
	return 0;//returns 0 if strings are different
}

uint16_t  ExtractId(char ch0, char ch1){
	uint16_t ret = 0;
	ret|=ch1<<8;
	ret|=ch0;
	return ret;
}

void USART3_IRQHandler(void) {
	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {
		char* buffer;
		Bluetooth_Receive(buffer, 6);
		/*if (CompareStrings(buffer,"ADDUS")) {

		} else if (CompareStrings(buffer,"CHNGE")) {

		} else */if (CompareStrings(buffer,"RECCD1")) {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		} else /*if (CompareStrings(buffer,"GETDB")) {

		} else if (CompareStrings(buffer,"CHNID")) {

		}*/
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

	}
}

void Bluetooth_Configuration(void) {
	Bluetooth_NVIC_Configuration();
	Bluetooth_GPIO_Configuration();
	Bluetooth_USART_Configuration();
}

static void Bluetooth_GPIO_Configuration(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

}

static void Bluetooth_USART_Configuration(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART_InitTypeDef USART_InitStructure;

	/* USART1 configuration ------------------------------------------------------*/
	USART_InitStructure.USART_BaudRate = 9600;        // Baud Rate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);

	/* Enable USART1 */
	USART_Cmd(USART3, ENABLE);
}

static void Bluetooth_NVIC_Configuration(void) {
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* Enable the USART3 Receive interrupt: this interrupt is generated when the
	 USART3 receive data register is not empty */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

void Bluetooth_Send(char data[], unsigned long n) {
	for (int j = 0; j < n; ++j) {
		USART_SendData(USART3, (uint16_t) data[j]);
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
		}
	}
}

void Bluetooth_Receive(char* buffer, int n) {
	buffer = calloc(sizeof(char),n+1);
	for (int i = 0; i < n; ++i) {
		buffer[i] = USART_ReceiveData(USART3);
	}
}
