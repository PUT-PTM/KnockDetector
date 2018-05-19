/*
 * sensor.c
 *
 *  Created on: 19.05.2018
 *      Author: HP 8560w
 */


#include "sensor.h"

#define Sensor_GPIO_RCC RCC_AHB1Periph_GPIOA
#define Sensor_GPIO_Port GPIOA
#define Sensor_GPIO_Pin GPIO_Pin_0

#define Sensor_ADC_RCC RCC_APB2Periph_ADC1
#define Sensor_ADC ADC1
#define Sensor_ADC_Channel ADC_Channel_0 //depends on GPIO pin


void Sensor_Configuration(void) {
	Sensor_GPIO_Config();
	Sensor_ADC_Config();
}

void Sensor_GPIO_Config(void) {
	RCC_AHB1PeriphClockCmd(Sensor_GPIO_RCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Sensor_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(Sensor_GPIO_Port, &GPIO_InitStructure);
}

void Sensor_ADC_Config(void) {
	RCC_APB2PeriphClockCmd(Sensor_ADC_RCC, ENABLE); // zegar dla modułu ADC1

	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(Sensor_ADC, &ADC_InitStructure);

	ADC_RegularChannelConfig(Sensor_ADC, Sensor_ADC_Channel, 1, ADC_SampleTime_84Cycles);

	ADC_Cmd(Sensor_ADC, ENABLE);

	ADC_SoftwareStartConv(Sensor_ADC);
}

uint16_t Sensor_GetSensorValue(void) {
	while (ADC_GetFlagStatus(Sensor_ADC, ADC_FLAG_EOC) == RESET) {
				 			;
	}
	return ADC_GetConversionValue(Sensor_ADC);
}
