/*
 * lock.h
 *
 *  Created on: 09.06.2018
 *      Author: Przemek
 */

#ifndef LOCK_H_
#define LOCK_H_

#include "stm32f4xx.h"

#define Engine_IN1 GPIO_Pin_1
#define Engine_IN2 GPIO_Pin_2
#define Engine_Port GPIOA
#define Engine_RCC RCC_AHB1Periph_GPIOA

void Lock_Configuration(void);
void Lock_Unlock(void);
void Lock_Clock(void);

#endif /* LOCK_H_ */
