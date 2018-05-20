/*
 * sensor.h
 *
 *  Created on: 19.05.2018
 *      Author: HP 8560w
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "stm32f4xx.h"

uint16_t Sensor_GetSensorValue(void);
void Sensor_Configuration(void);

#endif /* SENSOR_H_ */