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
#include "lock.h"
#include "LED_controller.h"


#define Detector_Sampling 20000 //20000 in 1s
#define Detector_Threshold 60 //Sensor value
#define Detector_SingularErrorThreshold 25 //25ms
#define Detector_GlobalErrorThreshold 15 //25ms
#define Detector_DebouncingTime 3000 //3000 = 150ms
#define Detector_MaximumIntervalSeconds 3
#define Detector_MaximumInterval Detector_MaximumIntervalSeconds*Detector_Sampling
#define Detector_MaximumKnocks 20


typedef enum {RECORD = 1, LISTEN = 0} Detector_Mode;
typedef enum {GOOD = 1, WRONG = 0} Detector_Verdict;

Database_USER_SecretCode Detector_RecordedCode;
bool Detector_ThresholdExceeded_Flag;
bool Detector_ListenToSecretCode_Flag;
bool Detector_Debouncing_Flag;
bool Detector_CountTime_Flag;
Detector_Mode Detector_Current_Mode;

void Detector_Configuration(void);
void TIM3_IRQHandler(void);
Database_USER_SecretCode * Detector_GetRecordedCode(void);
void Detector_EnableRecordMode(void);
int map(int x, int in_min, int in_max, int out_min, int out_max);

#endif /* DETECTOR_CONTROLLER_H_ */
