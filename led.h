/*
 * led.h
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */

#ifndef LED_H_
#define LED_H_

#include "std_types.h"

#define RED_LED_PORT_ID     PORTB_ID
#define RED_LED_PIN_ID      PIN5_ID
#define GREEN_LED_PORT_ID   PORTB_ID
#define GREEN_LED_PIN_ID    PIN6_ID
#define BLUE_LED_PORT_ID    PORTB_ID
#define BLUE_LED_PIN_ID     PIN7_ID

#define POSITIVE_LOGIC   // Comment this line to use Negative Logic
//#define NEGATIVE_LOGIC  // Uncomment this line to use Negative Logic

// Error handling in case both are defined
#ifdef POSITIVE_LOGIC
#ifdef NEGATIVE_LOGIC
#error "Only one logic type can be defined at a time!"
#endif
#endif

typedef enum{
	RED_LED=0,
	GREEN_LED=1,
	BLUE_LED=2

}LED_ID;



void LEDS_init(void);
void LED_on(LED_ID id);
void LED_off(LED_ID id);

#endif /* LED_H_ */
