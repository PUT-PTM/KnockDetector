/*
 * bluetooth_controller.c
 *
 *  Created on: 30.05.2018
 *      Author: Przemek
 */

#include "bluetooth_controller.h"

#define Bluetooth_INPUT_SIZE 100

static char input[Bluetooth_INPUT_SIZE];
static int inputIndex = 0;

static void Bluetooth_GPIO_Configuration(void);
static void Bluetooth_USART_Configuration(void);
static void Bluetooth_NVIC_Configuration(void);
static void InterpretInput(void);

static void AddUser(void);
static void DeleteUser(void);
static void ChangeCode(void);
static void RecordCode(void);
static void GetDatabase(void);
static void ChangeName(void);
static void SendOK(void);
static void SendError(void);
static void SendEndOfCommand(void);


int CheckCommand(char* in1, char* in2) {
	for (int i = 0; i < 5; ++i) {
		if (in1[i] != in2[i]) {
			return 0;
		}
	}
	return 1;
}

uint16_t ExtractId(char ch0, char ch1) {
	uint16_t ret = 0;
	ret |= ch1 << 8;
	ret |= ch0;
	return ret;
}

void USART3_IRQHandler(void) {

	if ((USART3->SR & USART_FLAG_RXNE) != (u16) RESET) {
		if ((input[inputIndex++] = USART_ReceiveData(USART3)) != '\a') {

		} else {
			inputIndex=0;
			InterpretInput();
		}
	}
}

void Bluetooth_Configuration(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	Bluetooth_NVIC_Configuration();
	Bluetooth_GPIO_Configuration();
	Bluetooth_USART_Configuration();
}

static void Bluetooth_GPIO_Configuration(void) {
	RCC_AHB1PeriphClockCmd(Bluetooth_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Bluetooth_GPIO_TXD | Bluetooth_GPIO_RXD;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Bluetooth_GPIO_Port, &GPIO_InitStructure);
	GPIO_PinAFConfig(Bluetooth_GPIO_Port, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(Bluetooth_GPIO_Port, GPIO_PinSource11, GPIO_AF_USART3);

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
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
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
}

void Bluetooth_Send(char data[], unsigned long n) {
	char a1=data[0];
	char a2=data[1];
	char a3=data[2];
	char a4=data[3];
	char a5=data[4];
	char a6=data[5];
	for (int j = 0; j < n; ++j) {
		USART_SendData(USART3, (uint16_t) data[j]);
		//Loop until the end of transmission
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
		}
	}
}

static void InterpretInput(void) {

	if (CheckCommand(input, "ADDUS")) {
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		AddUser();
	} else if (CheckCommand(input, "DELUS")) {
		DeleteUser();
	} else if (CheckCommand(input, "CHNCD")) {
		ChangeCode();
	} else if (CheckCommand(input, "RECCD")) {
		RecordCode();
	} else if (CheckCommand(input, "GETDB")) {
		GPIO_SetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
		GetDatabase();
		/*SendOK();*/
	} else if (CheckCommand(input, "CHNNA")) {
		ChangeName();
	} else {
		SendError();
	}
	SendEndOfCommand();
}

static void AddUser(void) {
	Database_USER_DATA user;
	memcpy(user.name, &(input[5]), sizeof(Database_USER_Name));
	memcpy(user.creation_date, &(input[5 + sizeof(Database_USER_Name)]),
			sizeof(Database_USER_CreationDate));
	if (Database_AddUser(user) == DB_OK) {
		SendOK();
	} else {
		SendError();
	}
}

static void DeleteUser(void) {
	Database_USER_ID id = 0;
	memcpy(&id, &(input[5]), sizeof(Database_USER_ID));
	if (Database_DeleteUser(id) == DB_OK) {
		SendOK();
	} else {
		SendError();
	}
}

static void ChangeCode(void) {
	Database_USER_ID id = 0;
	memcpy(&id, &(input[5]), sizeof(Database_USER_ID));
	Database_USER_SecretCode secret_code;
	memcpy(secret_code, &Detector_RecordedCode, sizeof(Database_USER_SecretCode));
	if (Database_ChangeSecretCode(id, secret_code) == DB_OK) {
		SendOK();
	}
	else {
		SendError();
	}

	//to-do get code using detector

	/*Database_USER_SecretCode secret_code;
	memcpy(secret_code, &(input[5]), sizeof(Database_USER_SecretCode));
	Database_ChangeSecretCode(secret_code);*/
}

static void RecordCode(void) {
	Detector_EnableRecordMode();
	while(Detector_Current_Mode==RECORD);

	SendOK();
}

static void GetDatabase(void) {
	char** database = malloc(1);
	int* numberOfBytes = 0;
	if (Database_GetDatatabase(database, numberOfBytes) == DB_OK) {
		char a1 = database[0];
		char a2 = database[1];
		char a3 = database[2];
		char a4 = database[3];
		SendOK();
		Bluetooth_Send(*database, *numberOfBytes);
	} else {
		SendError();
	}
	free(database);
}

static void ChangeName(void){
	Database_USER_ID id = 0;
	Database_USER_Name name;
	memcpy(&id, &(input[5]), sizeof(Database_USER_ID));
	memcpy(name, &(input[5 + sizeof(Database_USER_Name)]), sizeof(Database_USER_Name));
	if (Database_ChangeName(id, name) == DB_OK) {
		SendOK();

	} else {
		SendError();
	}
}

static void SendOK(void) {
	Bluetooth_Send("OK", 2);
}

static void SendError(void) {
	Bluetooth_Send("ER", 2);
}
static void SendEndOfCommand(void) {
	Bluetooth_Send("\a", 1);
}
