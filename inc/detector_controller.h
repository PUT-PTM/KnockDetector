/*
 * detector_controller.h
 *
 *  Created on: 22.05.2018
 *      Author: HP 8560w
 */

#ifndef DETECTOR_CONTROLLER_H_
#define DETECTOR_CONTROLLER_H_

#include "sensor.h"
#include "database_controller.h"

#define Detector_Sampling 20000
#define Detector_Threshold 200
#define Detector_DebouncingTime 100
#define Detector_MaximumIntervalSeconds 2
#define Detector_MaximumInterval Detector_MaximumIntervalSeconds*Detector_Sampling
#define Detector_MaximumKnocks 20

typedef enum {TRUE = 1, FALSE = 0} bool;
typedef enum {RECORD = 1, LISTEN = 0} Detector_Mode;

bool Detector_ThresholdExceeded_Flag = FALSE;
bool Detector_ListenToSecretCode_Flag = FALSE;
bool Detector_Debouncing_Flag = FALSE;
bool Detector_CountTime_Flag = FALSE;
Detector_Mode Detector_Current_Mode = LISTEN;

int Detector_Counter=0;

void Detector_Configuration(void);
void TIM3_IRQHandler(void);

#endif /* DETECTOR_CONTROLLER_H_ */
