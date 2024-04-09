#include <avr/io.h>
#include <util/delay.h>
#include "tinyOLED.h"
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>
void adc_init(void);
unsigned int get_adc(void);
#include "tinyOLED.h"
void display_temp(int value, int unit);
#include <avr/wdt.h>
#include <avr/sleep.h>