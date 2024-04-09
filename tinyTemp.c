#include "tinyTemp.h"

#define NUMSAMPLES 25  // #ADC Samples to average
#define VREF 1.1        // ADC reference voltage

// const char Message1[] PROGMEM = "TEMP:";
// const char message[] PROGMEM = "POWER ON";
const char mV[] PROGMEM = "mV";
const char dot[] PROGMEM = ".";
const char fahr[] PROGMEM = " Deg F ";
const char cels[] PROGMEM = " Deg C ";
const char poweroff[] PROGMEM = "Power Off";
const char poweron[] PROGMEM = "Power On";
const char toohot[] PROGMEM = "TOO HOT!!!";

const int TEMP_TOO_HOT = 70;
const int DISPLAY_TIME = 3000;  // 3 seconds

// int main(void)
// {
//     float tempC, tempF, analogVoltage;
//     unsigned int digitalValue, temp;
//     unsigned long int totalValue; 
//     char buffer[3];
//     int sleep = 0;

//     adc_init();
//     OLED_init();
//     OLED_clear();
    
//     while(!sleep){
//         // Acquire & average NUMSAMPLES temp measurements
//         totalValue = 0;
//         for (int i = 0; i < NUMSAMPLES; i++)
//             totalValue += get_adc(); // Get a sample from temp sensor
//         digitalValue = totalValue / NUMSAMPLES;
        
//         // Convert to temp & analog voltage in mV
//         tempC = digitalValue * 1.0 * VREF / 10.24 - 50.; 
//         tempF = tempC * (9. / 5.) + 32.;
//         analogVoltage = digitalValue * 1.0 * VREF / 1024; 
//         analogVoltage = analogVoltage * 1000;
    
//         // Display temperatures
//         display_temp(tempF, 0);
//         _delay_ms(1500);
//         OLED_clear();
//         display_temp(tempC, 1);
//         _delay_ms(1500);

//         // Set tinyTemp back to sleep
//         sleep = 1;
//     }
//     OLED_clear();
//     _delay_ms(8000);
//     sleep = 0;
// }


int main(void){

    WDT_OFF();  // Shut off the system

    float tempC, tempF, analogVoltage;
    unsigned int digitalValue, temp;
    unsigned long int totalValue; 

    adc_init();
    OLED_init();
    OLED_clear();
    
    // Test Sleep 
    OLED_printP(poweron);
    _delay_ms(1000);
    OLED_clear();

    // Acquire & average NUMSAMPLES temp measurements
    totalValue = 0;
    for (int i = 0; i < NUMSAMPLES; i++)
        totalValue += get_adc(); // Get a sample from temp sensor
    digitalValue = totalValue / NUMSAMPLES;
    
    // Convert to temp & analog voltage in mV
    tempC = digitalValue * 1.0 * VREF / 10.24 - 50.; 
    tempF = tempC * (9. / 5.) + 32.;
    analogVoltage = digitalValue * 1.0 * VREF / 1024; 
    analogVoltage = analogVoltage * 1000;

    // Display temperatures , display for 3 seconds
    display_temp(tempF, 0);     // print temperature in fahrenheit
    if(tempF > TEMP_TOO_HOT){
        OLED_cursor(50, 1);     // set cursor position
        OLED_printP(toohot);    // print TOO HOT
    }
    _delay_ms(DISPLAY_TIME);
    OLED_clear();

    display_temp(tempC, 1);     // print temperature in celcius
    if(tempF > TEMP_TOO_HOT){
        OLED_cursor(50, 1);     // set cursor position
        OLED_printP(toohot);    // print TOO HOT
    }
    _delay_ms(DISPLAY_TIME);
    OLED_clear();

    wdt_enable(WDTO_8S);    // Start the WDT; reset after 8 seconds
    while(1);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();		    // Put the system to sleep
}


// Display temperature value on the OLED
void display_temp(int value, int unit){
    unsigned int temp;
    char buffer[3];
    
    temp = value * 10.;
    itoa(temp/10, buffer, 10);
    unsigned char i;
    for (i = 0; i < strlen(buffer); i++)
    {
        OLED_printC(buffer[i]);
    }
    OLED_printP(dot);
    itoa(temp%10, buffer, 10);
    unsigned char j;
    for (j = 0; j < strlen(buffer); j++)
    {
        OLED_printC(buffer[j]);
    }

    if(unit == 1){
        OLED_printP(cels);
    } else {
        OLED_printP(fahr);
    }   
}

// Initialize ADC peripheral
void adc_init(void)
{
    // Copied from Brent Dickinson on Piazza
    ADMUX = 0b10000010;   //sets 1.1V IRV, sets ADC2 as channel
    ADCSRA = 0b10000011;   //turn on the ADC, keep ADC single conversion mode
}

// Read ADC value
unsigned int get_adc()
{
    ADCSRA |= (1 << ADSC); // Start ADC conversion
    while ((ADCSRA & (1 << ADIF)) == 0)
        ;                       // Wait till ADC finishes
    ADCSRA |= (1<<ADIF);        // Clear ADIF flag
    return ADCL | (ADCH << 8);  // Read ADCL first !
}

// Disable WTD and clear reset flag immediately at startup
void WDT_OFF()
{
	MCUSR &= ~(1 << WDRF);
    WDTCR = (1 << WDCE) | (1 << WDE);
	WDTCR = 0x00;
}

