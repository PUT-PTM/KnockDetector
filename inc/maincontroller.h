/*
 * maincontroller.h
 *
 *  Created on: 19.05.2018
 *      Author: HP 8560w
 */

#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include "sensor.h"
#include "sdmodule.h"
#include "bluetooth_controller.h"
#include "database_controller.h"

#define DIODES_ONBOARD_PINS  GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15
#define DIODES_ONBOARD_PORT GPIOD

void Controller_Configuration(void);
void DiodesOnBoard_Config(void);

#endif /* MAINCONTROLLER_H_ */
