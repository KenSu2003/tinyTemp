// main.c
#include "tinyOLED.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

// messages to print on OLED
const char Message1[] PROGMEM = "TEMP:";

int main(void)
{
  char buffer[3];
  // DDRB = 1<<DDB4;

  OLED_init(); // initialize the OLED
  int x = 0;
  OLED_clear();
  while (1)
  { // loop until forever

    OLED_cursor(20, 1);    // set cursor position
    OLED_printP(Message1); // print message 1
    OLED_cursor(50, 1);    // set cursor position
    x++;
    itoa(x, buffer, 10); // Convert dig value to character string
    unsigned char i;
    for (i = 0; i < strlen(buffer); i++)
    {
      OLED_printC(buffer[i]);
    }
    OLED_cursor(20, 3);
    OLED_printC(x / 100 + '0');     // hundreds Digit
    OLED_printC(x / 10 % 10 + '0'); // tens digit
    OLED_printC('.');
    OLED_printC(x % 10 + '0'); // 10's digit
    // PORTB ^= 1<<PB4;
    _delay_ms(50);
  }
}
