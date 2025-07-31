/*
 * main.c
 *
 *  Created on: ٠٤‏/١٠‏/٢٠٢٤
 *      Author: shahd
 */

#include <avr/io.h>
#include <util/delay.h>
#include "dcmotor.h"  // Include DC motor driver library
#include "main.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "ldr.h"
#include "led.h"
#include "buzzer.h"
#include "flamesensor.h"

uint16 current_temperature=0;
uint8  current_fan_status=0;
uint16 current_light_intensity=0;
uint8  flame_sensor_status=0;

void controlFan(uint16 temperature) {


    if (temperature >= TEMP_THRESHOLD_4) {
        DcMotor_Rotate( MOTOR_CW, 100);  // 100% speed
        current_fan_status=1;
    } else if (temperature >= TEMP_THRESHOLD_3) {
        DcMotor_Rotate( MOTOR_CW, 75);  // 75% speed
        current_fan_status=1;
    } else if (temperature >= TEMP_THRESHOLD_2) {
        DcMotor_Rotate( MOTOR_CW, 50);  // 50% speed
        current_fan_status=1;
    } else if (temperature >= TEMP_THRESHOLD_1) {
        DcMotor_Rotate( MOTOR_CW, 25);  // 25% speed
        current_fan_status=1;
    } else {
        DcMotor_Rotate(MOTOR_STOP, 0);  // Stop the fan
        current_fan_status=0;
    }

}

void controlLeds(uint16 lightIntensity){
	if (lightIntensity < LIGHT_THRESHOLD_1) {
	          // Turn ON all LEDs
		LED_on(RED_LED);
		LED_on(GREEN_LED);
		LED_on(BLUE_LED);
	    } else if (lightIntensity <= LIGHT_THRESHOLD_2) {
	    	LED_on(RED_LED);
	        LED_on(GREEN_LED);  // Turn ON Red and Green LEDs
	        LED_off(BLUE_LED);  // Turn OFF Blue LED
	    } else if (lightIntensity <= LIGHT_THRESHOLD_3) {
	    	LED_on(RED_LED);  // Turn ON Red LED
	        LED_off(GREEN_LED);  // Turn OFF Green LED
	        LED_off(BLUE_LED);  // Turn OFF Blue LED
	    } else {
	    	// Turn OFF all LEDs
	        LED_off(RED_LED);
	    	LED_off(GREEN_LED);
	    	LED_off(BLUE_LED);
	    }
}
void System_init(void){
	        ADC_init();  // Initialize ADC for temperature sensor
		    PWM_Timer0_Start(0);  // Initialize PWM with 0% duty cycle
		    DcMotor_Init();  // Initialize DC motor
		    LCD_init();
		    LEDS_init();
		    FlameSensor_init();
		    Buzzer_init();

}
void controlFlameAlert(uint8 flameStatus) {
    static uint8 alertDisplayed = 0;  // Flag to track if the alert is already displayed

    if (flameStatus == 1) {
        if (alertDisplayed == 0) {
            // Only clear the screen and write the message once when fire is detected
            LCD_clearScreen();
            LCD_moveCursor(1, 1);
            LCD_displayString("Critical alert!");
            alertDisplayed = 1;  // Set the flag to indicate the alert is displayed
        }

        // Continue turning on the buzzer, stopping the motor, and turning off LEDs
        Buzzer_on();


    } else {
        if (alertDisplayed == 1) {
            // Clear the alert when fire is no longer detected
        	LCD_moveCursor(0,1);
        	LCD_displayString("  FAN is OFF ");
        	LCD_moveCursor(1,0);
            LCD_displayString("Temp=   LDR=   %");  // Optional: Show a normal state message
            alertDisplayed = 0;  // Reset the flag
        }
        // Turn off the buzzer when no flame is detected
        Buzzer_off();
    }
}


int main() {
    System_init();

    LCD_moveCursor(0,1);
    LCD_displayString("  FAN is OFF ");
    LCD_moveCursor(1,0);
    LCD_displayString("Temp=   LDR=   %");

    while(1) {
        current_temperature = LM35_getTemperature();  // Get the current temperature
        controlFan(current_temperature);
        current_light_intensity = LDR_getLightIntensity(); // Get light intensity
        controlLeds(current_light_intensity);  // Control LEDs based on light

        flame_sensor_status = FlameSensor_getValue(); // Get flame sensor status

        controlFlameAlert(flame_sensor_status);  // Handle flame alert

        if (flame_sensor_status == 0) {  // Normal operation, no flame alert
            // Update LCD with temperature and light values
            LCD_moveCursor(1,5);
            LCD_intgerToString(current_temperature);
            if (current_temperature < 100) {
                LCD_displayCharacter(' ');  // Space for two-digit numbers
            }

            LCD_moveCursor(1,12);
            if(current_light_intensity >= 100)
             {
               	LCD_intgerToString(current_light_intensity);
             }
            else
             {
                LCD_intgerToString(current_light_intensity);
                /* In case the digital value is two or one digits print space in the next digit place */
                LCD_displayCharacter(' ');
              }

            // Display fan status
            LCD_moveCursor(0,9);
            if (current_fan_status == 1) {
                LCD_displayString(" ON ");
            } else {
                LCD_displayString(" OFF ");
            }

            _delay_ms(100);  //  suitable delay to prevent constant refresh
        }
    }
}
