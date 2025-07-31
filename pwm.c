/*
 * pwm.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */
#include <avr/io.h>
#include "common_macros.h"
#include "pwm.h"
#include "gpio.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = LOGIC_LOW; // Set Timer Initial Value to 0

	OCR0  = duty_cycle; //Set Compare value

	 // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
	 GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02)| (1<<CS00);
}
