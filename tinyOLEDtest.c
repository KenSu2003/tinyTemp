/*********************************************
 * tinyOLEDtest.c
 * This code was written to test an SSD1306 0.96"
 * 64x128 OLED display controlled by ATtiny85 with 
 * the tinyOLED library. 
 * Prepared for ECE-304/JDP Spring 2024
 * D.McLaughlin 3/13/24
 * *******************************************/

#include "tinyOLED.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

// messages to print on OLED
const char Message1[] PROGMEM = "COUNT:";

int main(void)
{
  char buffer[3];
  OLED_init(); // initialize the OLED
  int x = 0;
  OLED_clear();
  while (1)
  { 
    OLED_cursor(10, 1);    // set cursor position
    OLED_printP(Message1); // print message 1
    OLED_cursor(50, 1);    // set cursor position
    x++;
    itoa(x, buffer, 10); // Convert dig value to character string
    unsigned char i;
    for (i = 0; i < strlen(buffer); i++)
    {
      OLED_printC(buffer[i]);
    }
    _delay_ms(1000);
  }
}
