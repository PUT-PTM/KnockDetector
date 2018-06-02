/*
 * detector_controller.c

 *
 *  Created on: 22.05.2018
 *      Author: HP 8560w
 */

#include "detector_controller.h"

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
static void ValidateSecretCode(void);
static void ResetRecordedCode(void);
static void ResetRegisteredCode(void);
static void CopyRegisteredCodeToRecordedCode(void);
static void InsertIntervalIntoSequence(void);

static Database_USER_SecretCode Detector_RecordedCode = { 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static Database_USER_SecretCode Detector_RegisteredCode = { 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int Detector_CurrentKnock = 0;

void Detector_Configuration(void) {
	Sensor_Configuration();
	Detector_Timer_Config();
	Detector_TimerNVIC_Config();
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
	//Doprowadzenie zasilania do systemu przerwan
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);    //EXTI,NVIC

	// ustawienie trybu pracy priorytetów przerwañ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;

	//Konfiguracja przerwania TIM3
	// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	// priorytet g³ówny
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana³
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype³nion¹ strukturê do rejestrów
	NVIC_Init(&NVIC_InitStructure);

	// wyczyszczenie przerwania od timera 3 (wyst¹pi³o przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// zezwolenie na przerwania od przepe³nienia dla timera 3
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
}

static
void DebouncingControl(void) {
	if (Detector_Counter == Detector_DebouncingTime) {
		StopDebouncing();
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
		}
	} else {
		CheckCurrentTimeInterval();
		CheckKnocksAmount();
		/* If Detector_ListenToSecretCode_Flag  is set to FALSE it means its time to validate/record knock*/
		if (Detector_ListenToSecretCode_Flag == FALSE) {
			if (Detector_Current_Mode == LISTEN) {
				ValidateSecretCode();
				/* TO DO: Validate */
			} else if (Detector_Current_Mode == RECORD) {
				ResetRecordedCode();
				CopyRegisteredCodeToRecordedCode();
				Detector_DisableRecordMode();
			}

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
void ValidateSecretCode(void) {
	/*TO DO:
	 * - get database structure
	 * - iterate until it finds pattern, another function for validation two arrays
	 *  */
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
