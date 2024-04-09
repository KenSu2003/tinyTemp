repository: tinyOLED 

owner: David McLaughlin, UMass Amherst

created: March 20, 2024
updated March 23, 2024 and various other dates

This repository contains code for testing SSD1306 OLED using ATtiny85 microcontroller
This code has been built for ECE-304 Spring semester 2024

The user-defined library for I2C and SSD1306 is contained in tinyOLED.c (source code) and tinyOLED.h (API).  

A simple program to display some characters and numbers on the OLED is contained in tinyOLEDtest.c. A photograph of the wiring is also contained in this repository.

blink.c is also added. Very simple code to blink an LED on ATtiny85 just to be sure things are working ok

Acknowledgement: files tinyOLED.h and tinyOLED.c were based on open source code published on github by Stefan Wagner  which can be found here:
https://github.com/wagiminator/ATtiny13-TinyOLEDdemo/tree/main/software/TinyOLEDdemo_t10_text
