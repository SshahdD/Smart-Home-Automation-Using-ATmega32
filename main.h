/*
 * main.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */

#ifndef MAIN_H_
#define MAIN_H_

#include"std_types.h"

#define TEMP_THRESHOLD_1 25
#define TEMP_THRESHOLD_2 30
#define TEMP_THRESHOLD_3 35
#define TEMP_THRESHOLD_4 40

#define LIGHT_THRESHOLD_1 15  // Intensity < 15%
#define LIGHT_THRESHOLD_2 50  // Intensity 16-50%
#define LIGHT_THRESHOLD_3 70  // Intensity 51-70%

void controlFan(uint16 temperature);
void controlLeds(uint16 light);
void controlFlameAlert(uint8 flameStatus);
void System_init(void);

#endif /* MAIN_H_ */
