/*
 * detector_controller.h
 *
 *  Created on: 22.05.2018
 *      Author: HP 8560w
 */

#ifndef DETECTOR_CONTROLLER_H_
#define DETECTOR_CONTROLLER_H_

#include <stdlib.h>
#include "sensor.h"
#include "database_controller.h"
#include "bool.h"


#define Detector_Sampling 20000 //20000 in 1s
#define Detector_Threshold 200 //Sensor value
#define Detector_SingularErrorThreshold 500 //25ms
#define Detector_GlobalErrorThreshold 500 //25ms
#define Detector_DebouncingTime 3000 //3000 = 150ms
#define Detector_MaximumIntervalSeconds 2
#define Detector_MaximumInterval Detector_MaximumIntervalSeconds*Detector_Sampling
#define Detector_MaximumKnocks 20


typedef enum {RECORD = 1, LISTEN = 0} Detector_Mode;

bool Detector_ThresholdExceeded_Flag = FALSE;
bool Detector_ListenToSecretCode_Flag = FALSE;
bool Detector_Debouncing_Flag = FALSE;
bool Detector_CountTime_Flag = FALSE;
Detector_Mode Detector_Current_Mode = LISTEN;

int Detector_Counter=0;

void Detector_Configuration(void);
void TIM3_IRQHandler(void);
Database_USER_SecretCode * Detector_GetRecordedCode(void);
void Detector_EnableRecordMode(void);

#endif /* DETECTOR_CONTROLLER_H_ */
