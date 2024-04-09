/********************************
 * blink.c This is a simple code to blink
 * an LED connected to PB0 (pin 5) of an
 * ATtiny85 MCU. This can be helpful for verifying
 * end-to-end functioning of all tools needed
 * to flash code to the MCU 
 * D. McLaughlin for ECE-304 Spring 2024
 * Version 1 3/23/24
**************************************/

#define LED PB0
#define MYDELAY 1000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 1<<PB3;

    while(1){
        PORTB |= 1<<PB3;    // LED on
        _delay_ms(MYDELAY);
        PORTB &= ~(1<<PB3); // LED off
        _delay_ms(MYDELAY);
    }
}