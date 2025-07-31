/*
 * dcmotor.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include"std_types.h"

#define H_Bridge_PORT     PORTB_ID
#define H_Bridge_Pin_IN0  PIN0_ID
#define H_Bridge_Pin_IN1  PIN1_ID

#define Duty_Cycle_100   255
#define Duty_Cycle_75    192
#define Duty_Cycle_50    128
#define Duty_Cycle_25    64
#define Duty_Cycle_0     0

typedef enum {
    MOTOR_STOP = 0,
    MOTOR_CW = 1,   // Clockwise
    MOTOR_ACW = 2   // Anti-Clockwise
} DcMotor_State;



void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state, uint8 speed);


#endif /* DCMOTOR_H_ */
