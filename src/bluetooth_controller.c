/*
 * bluetooth_controller.c
 *
 *  Created on: 30.05.2018
 *      Author: Przemek
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "bluetooth_controller.h"

static int received;

void USART3_IRQHandler(void) {
	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {

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
		}
	}
}

void Bluetooth_Init(void) {
	const unsigned char welcome_str[] = " Welcome to Bluetooth!\r\n";

	// wlaczenie taktowania wybranego portu
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// zegar dla portu GPIO z którego wykorzystany zostanie pin jako wejœcie ADC (PA1)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// wlaczenie taktowania wybranego uk³adu USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* NVIC Configuration */
	Bluetooth_NVIC_Configuration();

	/* Configure the GPIOs */
	Bluetooth_GPIO_Configuration();

	/* Configure the USART1 */
	Bluetooth_USART_Configuration();

	/* Enable the USART1 Receive interrupt: this interrupt is generated when the
	 USART1 receive data register is not empty */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/* print welcome information */
	//UARTSend(welcome_str, sizeof(welcome_str));
}

/*******************************************************************************
 * Function Name  : GPIO_Configuration
 * Description    : Configures the different GPIO ports
 *******************************************************************************/
void Bluetooth_GPIO_Configuration(void) {

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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//inicjalizacja wejœcia ADC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*******************************************************************************
 * Function Name  : USART_Configuration
 * Description    : Configures the USART1
 *******************************************************************************/
void Bluetooth_USART_Configuration(void) {
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

void Bluetooth_NVIC_Configuration(void) {
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void Bluetooth_Send(char data[], unsigned long n) {
	for (int j = 0; j < n; ++j) {
		USART_SendData(USART3, (uint16_t) data[j]);
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
		}
	}
}
