#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TEMP_THRESHOLD 40  // Temperature threshold in Celsius

// Function to send command to LCD
void cmd(char a)
{
    PORTB = a;
    PORTD |= 0x20;     // RS=0, EN=1
    _delay_ms(50);
    PORTD &= 0x00;     // Clear EN and RS
}

// Function to send data to LCD
void data(char a)
{
    PORTB = a;
    PORTD |= 0xA0;     // RS=1, EN=1
    _delay_ms(50);
    PORTD &= 0xCF;     // Clear RS and EN
    PORTD &= 0x80;     // Clear extra bits
}

// Function to display string on LCD
void display(char *a)
{
    while((*a) != '\0')
    {
        data(*a);
        a++;
    }
}

// Function to display a number on LCD
void display_number(int num)
{
    data((num / 100) + 0x30);
    data(((num % 100) / 10) + 0x30);
    data((num % 10) + 0x30);
}

// ADC Interrupt Service Routine
ISR(ADC_vect)
{
    uint16_t adc_value, adc1, adch;
    
    adc1 = ADCL;
    adch = ADCH;
    adc_value = (adch << 2) | (adc1 >> 6); // 10-bit result

    // Convert ADC to temperature in °C (LM35 = 10mV/°C)
    float voltage = (adc_value * 5.0) / 1024.0;  // Assuming AVCC = 5V
    float temp = voltage * 100;  // LM35: 10mV per °C

    cmd(0x80); // Move to 1st line
    display("Temp:    ");

    // Show temperature value
    data(((int)temp / 10) + 0x30);       
    data(((int)temp % 10) + 0x30);       
    data(0xDF);  // ° symbol
    data('C');

    // If temp >= threshold (e.g., 40°C), turn buzzer ON + Show alert
    if (temp >= TEMP_THRESHOLD)
    {
       // _delay_ms(500);
         cmd(0xC0);               // Move to second line
        display("ALERT High Temp!   ");// Show warning
        PORTD |= (1 << PD0);// Buzzer ON
        _delay_ms(5000);
        
             
    }
    else
    {
        cmd(0xC0);               // Clear second line
        display("Normal           ");
        PORTD &= ~(1 << PD0);    // Buzzer OFF
    }

    _delay_ms(500);
}


// Main Function
int main()
{
    DDRA = 0x00;     // PORTA as input (ADC)
    DDRB = 0xFF;     // PORTB as output (LCD Data)
    DDRD = 0xFF;     // PORTD as output (Control + Buzzer)

    // LCD Initialization
    cmd(0x38);       // 8-bit, 2 line, 5x7
    cmd(0x0C);       // Display ON, Cursor OFF
    cmd(0x01);       // Clear screen
    cmd(0x80);       // First line

    display("Temp Monitor");

    _delay_ms(200);

    // ADC Setup
    ADMUX = 0x60;    // ADC0, AREF=AVCC
    ADCSRA = 0xC8;   // ADC Enable, Start Conv, ADC Int Enable, Prescaler=64

    sei();           // Global Interrupt Enable

    while (1)
    {
        ADCSRA |= (1 << ADSC); // Start ADC conversion
        _delay_ms(500);       // Wait 1 second before next reading
    }
}
