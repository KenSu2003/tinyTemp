# Specify the com port (windows) or USB port (macOS) -- not needed for USBtinyISP
# SERIALPORT = /dev/tty.usbmodem1101

# Specify the name of your source code here:
# SOURCEFILE = main.c tinyOLED.c 
SOURCEFILE = tinyTemp.c tinyOLED.c


# Use 16000000 for Arduino Uno; 1000000 for new ATmega328P chip
CLOCKSPEED = 1000000UL	
PROGRAMMER = usbtiny 	# Use usbtiny for pocket programmer 
MCU = ATtiny85 	    # Use ATmega328p, ATtiny85, or other MCU name as appropriate

# Don't change anything below unless you know what you're doing
begin:	main.hex

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(MCU) main.elf

main.elf: $(SOURCEFILE)
	avr-gcc -Wall -Os -DF_CPU=$(CLOCKSPEED) -mmcu=$(MCU) -o main.elf $(SOURCEFILE)

clean:
	rm -f *.hex *.elf *.o

flash:	begin
	avrdude -c $(PROGRAMMER) -P usb -p $(MCU) -U flash:w:main.hex:i
