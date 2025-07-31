/*
 * flamesensor.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */

#ifndef FLAMESENSOR_H_
#define FLAMESENSOR_H_

#include "std_types.h"

#define FLAME_SENSOR_PORT_ID  PORTD_ID
#define FLAME_SENSOR_PIN_ID   PIN2_ID

void FlameSensor_init(void);
uint8 FlameSensor_getValue(void);


#endif /* FLAMESENSOR_H_ */
