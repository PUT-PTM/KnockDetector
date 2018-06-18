/*
 * detector_controller.c

 *
 *  Created on: 22.05.2018
 *      Author: HP 8560w
 */

#include "detector_controller.h"

void Zaswiec(void) {
	GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
}

void NieSwiec(void) {
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
}

void ZaswiecGood(void) {
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
}

void NieSwiecGood(void) {
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}

void ZaswiecDebounce(void) {
	GPIO_SetBits(GPIOD,GPIO_Pin_15);
}

void NieSwiecDebounce(void) {
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);
}

void ZaswiecKoniec(void) {
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
}

void NieSwiecKoniec(void) {
	GPIO_ResetBits(GPIOD,GPIO_Pin_14);
}

static void Detector_Timer_Config(void);
static void Detector_TimerNVIC_Config(void);
static void Detector_IRQHandler(void);
static void CheckThresholdExceedion(void);
static void CountTime(void);
static void StartCountTime(void);
static void StopCountTime(void);
static void ResetTime(void);
static void SetDebouncing(void);
static void StopDebouncing(void);
static void DebouncingControl(void);
static void StartListenToSecretCode(void);
static void StopListenToSecretCode(void);
static void ControlProgram(void);
static void CheckCurrentTimeInterval(void);
static void CheckKnocksAmount(void);
static void EndOfSequence(void);
static int ValidateSecretCode(void);
static void ResetRecordedCode(void);
static void ResetRegisteredCode(void);
static void CopyRegisteredCodeToRecordedCode(void);
static void InsertIntervalIntoSequence(void);
static int CountCodeKnocks(Database_USER_SecretCode secretCode);
static void SequenceMapping(void);

Database_USER_SecretCode Detector_RecordedCode = { 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static Database_USER_SecretCode Detector_RegisteredCode = { 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int Detector_CurrentKnock = 0;
static int MaxKnockInterval=0;

bool Detector_ThresholdExceeded_Flag = FALSE;
bool Detector_ListenToSecretCode_Flag = FALSE;
bool Detector_Debouncing_Flag = FALSE;
bool Detector_CountTime_Flag = FALSE;
Detector_Mode Detector_Current_Mode = LISTEN;

int Detector_Counter=0;

void Detector_Configuration(void) {
	Sensor_Configuration();
	Detector_Timer_Config();
	Detector_TimerNVIC_Config();
	ResetRecordedCode();
}

Database_USER_SecretCode * Detector_GetRecordedCode(void) {
	return &Detector_RecordedCode;
}

void Detector_EnableRecordMode(void) {
	Detector_Current_Mode=RECORD;
}

void Detector_DisableRecordMode(void) {
	Detector_Current_Mode=LISTEN;
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
	{
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

static
void Detector_Timer_Config(void) {

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 200 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 21 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, ENABLE);
}

static
void Detector_TimerNVIC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);    //EXTI,NVIC

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		Detector_IRQHandler();
		// clear interrupt flag
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

static
void Detector_IRQHandler(void) {
	CheckThresholdExceedion();
	CountTime();
	/* We do not call a function when debouncing is on */
	if (Detector_Debouncing_Flag == FALSE) {
		ControlProgram();
	} else {
		DebouncingControl();
	}
}

static
void CheckThresholdExceedion(void) {
	Detector_ThresholdExceeded_Flag = FALSE;
	if (Sensor_GetSensorValue() < Detector_Threshold) {
		Detector_ThresholdExceeded_Flag = TRUE;
	}
}

static
void CountTime(void) {
	if (Detector_CountTime_Flag == TRUE) {
		Detector_Counter++;
	}
}

static
void StartCountTime(void) {
	SetDebouncing();
	Detector_CountTime_Flag = TRUE;
}

static
void StopCountTime(void) {
	Detector_CountTime_Flag = FALSE;
	ResetTime();
}

static
void ResetTime(void) {
	Detector_Counter = 0;
}

static
void SetDebouncing(void) {
	Detector_Debouncing_Flag = TRUE;
}

static
void StopDebouncing(void) {
	Detector_Debouncing_Flag = FALSE;
	NieSwiecDebounce();
}

static
void DebouncingControl(void) {
	if (Detector_Counter == Detector_DebouncingTime) {
		StopDebouncing();
	} else {
		ZaswiecDebounce();
	}
}

static
void StartListenToSecretCode(void) {
	Detector_ListenToSecretCode_Flag = TRUE;
}

static
void StopListenToSecretCode(void) {
	Detector_ListenToSecretCode_Flag = FALSE;
}

static
void ControlProgram(void) {
	if (Detector_ListenToSecretCode_Flag == FALSE) {

		if (Detector_ThresholdExceeded_Flag == TRUE) {
			ResetRegisteredCode();
			StartCountTime();
			StartListenToSecretCode();

			NieSwiecKoniec();
		}
	} else {
		CheckCurrentTimeInterval();
		CheckKnocksAmount();
		/* If Detector_ListenToSecretCode_Flag  is set to FALSE it means its time to validate/record knock*/
		if (Detector_ListenToSecretCode_Flag == FALSE) {
			SequenceMapping();
			if (Detector_Current_Mode == LISTEN) {
				if(ValidateSecretCode() == GOOD) {
					Lock_Unlock();
					//UNLOCK
					ZaswiecGood();
				}
				else {
					NieSwiecGood();
					//TURN ON RED DIODE
				}
			} else if (Detector_Current_Mode == RECORD) {
				ResetRecordedCode();
				CopyRegisteredCodeToRecordedCode();
				Detector_DisableRecordMode();
			}

			ZaswiecKoniec();

		} else if (Detector_ThresholdExceeded_Flag == TRUE) {
			InsertIntervalIntoSequence();
		}
	}
}

static
void InsertIntervalIntoSequence(void) {
	int interval;
	interval = Detector_Counter;
	Detector_RegisteredCode[Detector_CurrentKnock] = interval;
	if(interval>MaxKnockInterval) {
			MaxKnockInterval=interval;
		}

	StopCountTime();
	StartCountTime();
	Detector_CurrentKnock += 1;
}

static
void CheckCurrentTimeInterval(void) {
	if (Detector_Counter >= Detector_MaximumInterval) {
		EndOfSequence();
	}
}

static
void CheckKnocksAmount(void) {
	if (Detector_CurrentKnock >= 20) {
		EndOfSequence();
	}
}

static
void EndOfSequence(void) {
	StopCountTime();
	StopListenToSecretCode();
	Detector_ThresholdExceeded_Flag = FALSE;
}

static
int ValidateSecretCode(void) {
	if (Database_NumberOfUsers>0) {

		int registeredCodeKnockCount;
		registeredCodeKnockCount=CountCodeKnocks(Detector_RegisteredCode);
		Detector_Verdict verdict=WRONG;

		for (int i=0; i<Database_NumberOfUsers; i++) {
			int totalTimeDifference=0;
			int secretCodeKnockCount;
			secretCodeKnockCount=CountCodeKnocks(Database_Users[i].secret_code);
			if (registeredCodeKnockCount==secretCodeKnockCount) {
				verdict=GOOD;
				for (int j=0; j<Detector_MaximumKnocks; j++) {
					int timeDifference;
					timeDifference=abs(Database_Users[i].secret_code[j]-Detector_RegisteredCode[j]);
					if (timeDifference>Detector_SingularErrorThreshold) {
						verdict=WRONG;
					}
					totalTimeDifference=totalTimeDifference+timeDifference;
				}
				totalTimeDifference=totalTimeDifference/secretCodeKnockCount;
				if (totalTimeDifference>Detector_GlobalErrorThreshold) {
					verdict=WRONG;
				}
			}
			else {
				verdict=WRONG;
			}
			if (verdict==GOOD) {
				return GOOD;
			}
		}
	}
	return WRONG;
}

static
int CountCodeKnocks(Database_USER_SecretCode secretCode) {
	int codeKnockCount=0;

	for (int i=0; i<Detector_MaximumKnocks; i++) {
		if (secretCode[i]>0) {
			codeKnockCount+=1;
		}
		else {
			break;
		}
	}
	return codeKnockCount;
}


static
void ResetRecordedCode(void) {
	for (int i = 0; i < Detector_MaximumKnocks; i++) {
		Detector_RecordedCode[i] = 0;
	}
}

static
void ResetRegisteredCode(void) {
	for (int i = 0; i < Detector_MaximumKnocks; i++) {
		Detector_RegisteredCode[i] = 0;
	}
	Detector_CurrentKnock = 0;
}

static
void CopyRegisteredCodeToRecordedCode(void) {
	for (int i = 0; i < Detector_MaximumKnocks; i++) {
		Detector_RecordedCode[i] = Detector_RegisteredCode[i];
	}
}

static
void SequenceMapping(void) {
	for (int i=0; i<Detector_MaximumKnocks; i++) {

		Detector_RegisteredCode[i]=map(Detector_RegisteredCode[i],0,MaxKnockInterval,0,100);
	}
}


