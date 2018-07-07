/*
 * lock.c
 *
 *  Created on: 09.06.2018
 *      Author: Przemek
 */

#include "lock.h"

static void Lock_GPIO_Config(void);
static void Lock_TimerConfig(void);
static void Lock_TimerNVIC_Config(void);

void Lock_Configuration(){
	Lock_GPIO_Config();
	Lock_TimerConfig();
	Lock_TimerNVIC_Config();
}

static
void Lock_GPIO_Config(void) {
	RCC_AHB1PeriphClockCmd(Engine_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Engine_IN1 | Engine_IN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(Engine_Port, &GPIO_InitStructure);
}

static
void Lock_TimerConfig(void) {

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 8400 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 10000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM4, DISABLE);
}

static
void Lock_TimerNVIC_Config(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);    //EXTI,NVIC

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
		GPIO_ResetBits(Engine_Port, Engine_IN1 | Engine_IN2);
		TIM_Cmd(TIM4, DISABLE);
		LED_GreenOff();
		// clear interrupt flag
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void Lock_Unlock(void) {
	TIM_Cmd(TIM4, ENABLE);
	GPIO_SetBits(Engine_Port, Engine_IN1);
	LED_GreenOn();
}

void Lock_Lock(void) {
	TIM_Cmd(TIM4, ENABLE);
	GPIO_SetBits(Engine_Port, Engine_IN2);
}
