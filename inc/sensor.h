/*
 * sensor.h
 *
 *  Created on: 19.05.2018
 *      Author: HP 8560w
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "stm32f4xx.h"

#define Sensor_GPIO_RCC RCC_AHB1Periph_GPIOA
#define Sensor_GPIO_Port GPIOA
#define Sensor_GPIO_Pin GPIO_Pin_0

#define Sensor_ADC_RCC RCC_APB2Periph_ADC1
#define Sensor_ADC ADC1
#define Sensor_ADC_Channel ADC_Channel_0 //depends on GPIO pin

uint16_t Sensor_GetSensorValue(void);
void Sensor_Configuration(void);

#endif /* SENSOR_H_ */
