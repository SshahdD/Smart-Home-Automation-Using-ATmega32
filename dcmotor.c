/*
 * dcmotor.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */
#include"dcmotor.h"
#include"pwm.h"
#include"gpio.h"

 uint8 DC_motor_speed=0;
void DcMotor_Init(void){

		/* configure pin PB0 and PB1 as output pins */

		GPIO_setupPinDirection(H_Bridge_PORT, H_Bridge_Pin_IN0, PIN_OUTPUT);
		GPIO_setupPinDirection(H_Bridge_PORT,H_Bridge_Pin_IN1, PIN_OUTPUT);
		/* Motor is stop at the beginning */
		GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN0 , LOGIC_LOW);
		GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN1 , LOGIC_LOW);
}
void DcMotor_Rotate(DcMotor_State state, uint8 speed){


	switch (state) {
	    case MOTOR_STOP:
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN0 , LOGIC_LOW);
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN1 , LOGIC_LOW);
	        break;  // Exit the switch block
	    case MOTOR_CW:
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN0 , LOGIC_LOW);
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN1 , LOGIC_HIGH);
	        break;
	    // You can add more cases as needed
	    case MOTOR_ACW:
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN0 , LOGIC_HIGH);
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN1 , LOGIC_LOW);
	    	 break;
	    default:
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN0 , LOGIC_LOW);
	    	GPIO_writePin(H_Bridge_PORT, H_Bridge_Pin_IN1 , LOGIC_LOW);
	        break;
	}
	switch (speed) {
		    case 100:
		    	DC_motor_speed = Duty_Cycle_100 ;

		        break;  // Exit the switch block
		    case 75:
		    	DC_motor_speed=Duty_Cycle_75;

		        break;
		    // You can add more cases as needed
		    case 50:
		    	DC_motor_speed=Duty_Cycle_50;

		    	 break;
		    case 25:
		    	DC_motor_speed=Duty_Cycle_25;

		    	 break;
		    default:
		    	DC_motor_speed=Duty_Cycle_0;

		        break;
		}
	PWM_Timer0_Start(DC_motor_speed);

}
