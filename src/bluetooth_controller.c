/*
 * bluetooth_controller.c
 *
 *  Created on: 30.05.2018
 *      Author: Przemek
 */

#include "bluetooth_controller.h"
#include <stdlib.h>

#define Bluetooth_INPUT_SIZE 100

static char input[Bluetooth_INPUT_SIZE];
static int inputIndex = 0;

static void Bluetooth_GPIO_Configuration(void);
static void Bluetooth_USART_Configuration(void);
static void Bluetooth_NVIC_Configuration(void);

int CheckCommand(char* in1, char* in2) {
	for (int i = 0; i < 5; ++i) {
		if (in1[i] != in2[i]) {
			return 1;
		}
	}
	return 0;
}

uint16_t ExtractId(char ch0, char ch1) {
	uint16_t ret = 0;
	ret |= ch1 << 8;
	ret |= ch0;
	return ret;
}

void USART3_IRQHandler(void) {
	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {
		if(input[inputIndex] = USART_ReceiveData(USART3)){

		}else{
			InterpretInput();
		}
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
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

void InterpretInput() {
	if (CheckCommand(input, "ADDUS")) {

	} else if (CheckCommand(input, "CHNGE")) {

	} else if (CheckCommand(input, "RECCD")) {

	} else if (CheckCommand(input, "GETDB")) {

	} else if (CheckCommand(input, "CHNID")) {

	} else {

	}
}
