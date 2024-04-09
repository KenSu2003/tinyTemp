// tinyOLED.h
// This code serves as an SSD1306 OLED & I2C Library for ATtiny MCU
// Tested with ATtiny25 & 0.96" 128x64 OLED
// modified from the original by D. McLaughlin 12/22/23
// Original code 2020 by Stefan Wagner can be found here:
// Project Files (Github):  https://github.com/wagiminatorb
// License: http://creativecommons.org/licenses/by-sa/3.0/
// Changes made: separate single file into .c and .h files;
// used Main/Secondary nomenclature; other small changes


// libraries
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// I2C definitions
#define I2C_SDA         PB0                   // serial data pin
#define I2C_SCL         PB2                   // serial clock pin
#define I2C_SDA_HIGH()  DDRB &= ~(1<<I2C_SDA) // release SDA   -> pulled HIGH by resistor
#define I2C_SDA_LOW()   DDRB |=  (1<<I2C_SDA) // SDA as output -> pulled LOW  by MCU
#define I2C_SCL_HIGH()  DDRB &= ~(1<<I2C_SCL) // release SCL   -> pulled HIGH by resistor
#define I2C_SCL_LOW()   DDRB |=  (1<<I2C_SCL) // SCL as output -> pulled LOW  by MCU

// OLED definitions
#define OLED_ADDR       0x78                  // OLED write address
#define OLED_CMD_MODE   0x00                  // set command mode
#define OLED_DAT_MODE   0x40                  // set data mode
#define OLED_INIT_LEN   12                    // 12: no screen flip, 14: screen flip


// I2C init function
void I2C_init(void);

// I2C transmit one data byte to the secondary, ignore ACK bit, no clock stretching allowed
void I2C_write(uint8_t data);

// I2C start transmission
void I2C_start(uint8_t addr); 

// I2C stop transmission
void I2C_stop(void); 

// OLED init function
void OLED_init(void); 

// OLED set vertical shift
void OLED_shift(uint8_t ypos);

// OLED print a character
void OLED_printC(char ch); 

// OLED print a string from program memory
void OLED_printP(const char* p); 

// OLED set the cursor
void OLED_cursor(uint8_t xpos, uint8_t ypos); 

// OLED clear screen
void OLED_clear(void); 
