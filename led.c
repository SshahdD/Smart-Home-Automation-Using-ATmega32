/*
 * led.c
 *
 *  Created on: 04/10/2024
 *      Author: shahd
 */
#include "led.h"
#include "gpio.h"
#include "ldr.h"

void LEDS_init(void){

    // Make 3 pins of LEDs output pins
    GPIO_setupPinDirection(RED_LED_PORT_ID, RED_LED_PIN_ID , PIN_OUTPUT);
    GPIO_setupPinDirection(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID , PIN_OUTPUT);
    GPIO_setupPinDirection(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID , PIN_OUTPUT);

    // Turn off LEDs based on the logic type
#ifdef POSITIVE_LOGIC
    GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID , LOGIC_LOW);
    GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
    GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
#elif defined(NEGATIVE_LOGIC)
    GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID , LOGIC_HIGH);
    GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
    GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_HIGH);
#endif
}

void LED_on(LED_ID id){

#ifdef POSITIVE_LOGIC
    uint8 pinValue = LOGIC_HIGH; // In positive logic, HIGH turns the LED on
#elif defined(NEGATIVE_LOGIC)
    uint8_t pinValue = LOGIC_LOW;  // In negative logic, LOW turns the LED on
#endif

    switch (id) {
        case RED_LED:
            GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, pinValue);
            break;
        case GREEN_LED:
            GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, pinValue);
            break;
        case BLUE_LED:
            GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, pinValue);
            break;
        default:
            // Handle invalid LED ID
            break;
    }
}

void LED_off(LED_ID id){

#ifdef POSITIVE_LOGIC
    uint8 pinValue = LOGIC_LOW;  // In positive logic, LOW turns the LED off
#elif defined(NEGATIVE_LOGIC)
    uint8_t pinValue = LOGIC_HIGH; // In negative logic, HIGH turns the LED off
#endif

    switch (id) {
        case RED_LED:
            GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, pinValue);
            break;
        case GREEN_LED:
            GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, pinValue);
            break;
        case BLUE_LED:
            GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, pinValue);
            break;
        default:
            // Handle invalid LED ID
            break;
    }
}
