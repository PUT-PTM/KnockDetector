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
			return 1;
		}
		++i;
	}
	return 0;
}

void USART3_IRQHandler(void) {
	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {
		char* buffer;
		Bluetooth_Receive(buffer, 5);
		if (CompareStrings(buffer,"ADDUS")) {

		} else if (CompareStrings(buffer,"CHNGE")) {

		} else if (CompareStrings(buffer,"RECCD")) {

		} else if (CompareStrings(buffer,"GETDB")) {

		} else if (CompareStrings(buffer,"CHNID")) {

<<<<<<< HEAD

		received = USART_ReceiveData(USART3);
		if (received == '1') {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);        // Set '1' on PA8
			//UARTSend("LED ON\r\n",sizeof("LED ON\r\n"));    // Send message to UART1
		} else if (received == '2') {
			//UARTSend2(c, 6);
		} else {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);      // Set '0' on PA8
			//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
=======
>>>>>>> d5285b50013d8573b2b76d6ee60e8cb9edb3b185
		}
	}
}

void Bluetooth_Configuration(void) {
	Bluetooth_NVIC_Configuration();
	Bluetooth_GPIO_Configuration();
	Bluetooth_USART_Configuration();
	/* print welcome information */
	//UARTSend(welcome_str, sizeof(welcome_str));
}

static void Bluetooth_GPIO_Configuration(void) {
	// wlaczenie taktowania wybranego portu
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	// ustawienie funkcji alternatywnej dla pinów (USART)
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

void BluetoothReceive(char* buffer, int n) {
	buffer = calloc(sizeof(char),n+1);
	for (int i = 0; i < n; ++i) {
		buffer[i] = USART_ReceiveData(USART3);
	}
}
