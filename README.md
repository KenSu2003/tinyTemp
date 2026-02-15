# tinyTemp

This project is a **temperature display** I built for **ATtiny85**: it reads a sensor via the ADC and shows °F and °C on a **SSD1306 OLED** (0.96" 128×64). It was my ECE 304 course project (Spring 2024).

---

## What It Does

- **Reads temperature** from an analog sensor on **ADC channel 2** (1.1 V internal reference).
- **Averages 25 samples** to reduce noise, then converts the ADC value to °C and °F.
- **Displays on the OLED:** temperature in °F for 3 seconds, then in °C for 3 seconds.
- **"TOO HOT!!!"** is shown if the temperature exceeds 70 °F.
- **Watchdog** is enabled (8 s) and the MCU is prepared for sleep after the display cycle.

---

## Hardware

- **MCU:** ATtiny85 @ 1 MHz  
- **Display:** SSD1306 0.96" 128×64 OLED (I2C)  
- **I2C pins (bit-banged):** SDA = PB0, SCL = PB2  
- **Temperature:** analog sensor on ADC2 (e.g. TMP36 or similar)  
- **Programmer:** USBtinyISP (or compatible)

---

## Project Structure

| File | Role |
|------|------|
| **tinyTemp.c** / **tinyTemp.h** | Main application: ADC init, temperature conversion, display sequence, and watchdog/sleep setup. |
| **tinyOLED.c** / **tinyOLED.h** | I2C (bit-banged) and SSD1306 OLED driver: init, cursor, print character/string from program memory, clear. |
| **main.c** | Alternate main: simple "TEMP:" + counter on OLED (no temperature reading). |
| **tinyOLEDtest.c** | OLED test: "COUNT:" and incrementing value. |
| **blink.c** | Minimal LED blink on PB3; useful to verify toolchain and programmer. |
| **makefile** | Builds `tinyTemp.c` + `tinyOLED.c` by default; switch `SOURCEFILE` to build other mains. |

---

## Build and Flash

```bash
make          # builds main.elf and main.hex
make flash    # programs ATtiny85 via USBtinyISP (avrdude)
```

To build a different main (e.g. OLED test or blink), edit the makefile and set:

```makefile
SOURCEFILE = tinyOLEDtest.c tinyOLED.c
# or
SOURCEFILE = blink.c
```

---

## Credits

- **tinyOLED** driver: initial template by **D. McLaughlin** (Dec 2023), based on SSD1306/I2C code by **Stefan Wagner** (ATtiny13 TinyOLEDdemo):  
  [github.com/wagiminator/ATtiny13-TinyOLEDdemo](https://github.com/wagiminator/ATtiny13-TinyOLEDdemo/tree/main/software/TinyOLEDdemo_t10_text)  
- **ECE 304** (Spring 2024): course where this was assigned; the temperature application and integration are my own work.
