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
#include "delay.h"
#include "fpu.h"
#include "spi_sd.h"
#include "ff.h"
#include "user_data.h"
#include <string.h>

FATFS fatfs;
static FRESULT fresult;
char* filename = "Database.txt";
int i;
const unsigned char* c = "Szymon Bandowski";
user_data* Data;

char buffer[42];

void to_phone(user_data* input) {
	memcpy(buffer, &input->id, 2);
	memcpy(buffer + 2, &input->name, 20);
	memcpy(buffer + 22, &input->creation_date, 20);
}

int SD_read() {
	FIL file;
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	UINT have_read = 0;
	fresult = f_mount(0, &fatfs);
	if (fresult == FR_OK) {
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		fresult = f_open(&file, filename,
		FA_OPEN_ALWAYS | FA_READ);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		if (fresult == FR_OK) {
			GPIO_WriteBit(GPIOB, GPIO_Pin_9, SET);
			int to_read = f_size(&file);
			fresult = f_read(&file, buffer, to_read, &have_read);
			buffer[to_read] = 0;
			fresult = f_close(&file);
			return 0;
		} else {
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			return 1;
		}
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		return 1;
	}
	return 0;
}

int SD_write() {
	int to_write = 10;
	FIL file;
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	unsigned int have_written;
	fresult = f_mount(0, &fatfs);
	if (fresult == FR_OK) {
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		fresult = f_open(&file, filename,
		FA_OPEN_ALWAYS | FA_WRITE);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		if (fresult == 0) {
			fresult = f_write(&file, buffer, to_write, &have_written);
			fresult = f_close(&file);
			if (fresult == FR_OK) {
				return 0;
			} else {
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				return 1;
			}
		} else {
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			return 1;
		}
	} else {
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		return 1;
	}
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
	return 0;
}

void init() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =
	GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	SystemInit();
	fpu_enable();
	delay_init(168);
	SPI_SD_Init();
}

int Speaker_input;

//Bluetooth
//ErrorStatus HSEStartUpStatus;
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void USART3_IRQHandler(void);
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);
void UARTSend2(char[],unsigned long);

void USART3_IRQHandler(void) {
	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {

		i = USART_ReceiveData(USART3);
		if (i == '1') {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);        // Set '1' on PA8
			//UARTSend("LED ON\r\n",sizeof("LED ON\r\n"));    // Send message to UART1
		} else if (i == '2') {
			UARTSend2(buffer, 42);
		} else {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);      // Set '0' on PA8
			//UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
		}
	}
}

void usart_rxtx(void) {
	const unsigned char welcome_str[] = " Welcome to Bluetooth!\r\n";

	// wlaczenie taktowania wybranego portu
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// zegar dla portu GPIO z którego wykorzystany zostanie pin jako wejœcie ADC (PA1)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// wlaczenie taktowania wybranego uk³adu USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* NVIC Configuration */
	NVIC_Configuration();

	/* Configure the GPIOs */
	GPIO_Configuration();

	/* Configure the USART1 */
	USART_Configuration();

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
void GPIO_Configuration(void) {

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
void USART_Configuration(void) {
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

void NVIC_Configuration(void) {
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount) {
	//
	// Loop while there are more characters to send.
	//
	while (ulCount--) {
		USART_SendData(USART3, *pucBuffer++);
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
		}
	}
}

void UARTSend2(char data[], unsigned long n) {
	for (int j = 0; j < n; ++j) {
		USART_SendData(USART3,(uint16_t) data[j]);
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
		}
	}
}

int main(void) {
	usart_rxtx();
	init();
	int res;
	/*res = SD_read();
	while (res)
		;

	SD_write();
	while (res)
		;*/
	user_data ud1;
	Data=&ud1;
	Data->id=0;
	memcpy(Data->name, "Jean Pauleeeeeeeeeee", 20);
	memcpy(Data->creation_date, "19.15.2018dddddddddd", 20);
	to_phone(Data);
	memcpy(buffer, &Data->id, 2);
	memcpy(buffer + 2, &Data->name, 20);
	memcpy(buffer + 22,& Data->creation_date, 20);
	//memcpy(buffer, "  ", 2);
	//memcpy(buffer + 2, "Jean Pauleeeeeeeeeee", 20);
	//memcpy(buffer + 22,"19.15.2018dddddddddd", 20);
	for (;;) {
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		for (int i = 5000000; i > 0; --i)
			;
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		for (int i = 5000000; i > 0; --i)
			;
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		for (int i = 5000000; i > 0; --i)
			;
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		for (int i = 5000000; i > 0; --i)
			;
	}
}
