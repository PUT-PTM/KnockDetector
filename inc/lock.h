/*
 * lock.h
 *
 *  Created on: 09.06.2018
 *      Author: Przemek
 */

#ifndef LOCK_H_
#define LOCK_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Lock_Configuration(void);
void Lock_Unlock(void);
void Lock_Clock(void);

#endif /* LOCK_H_ */
