/*
 * Lab5.c
 *
 * Created: 19.11.2020 01:21:56
 * Author : anano
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
void setUp(){
	DDRB&=~(1<<PORTB7); // Setting button as an input
	DDRB|=(1<<PORTB5); // Setting LED an an output
	TCCR0A|=(1<<WGM01); // Setting timer to CTC
	PORTB|=(1<<PORTB7); // Enabling button to pull-up
	OCR0A=155; // Timer
	OCR0B=0; // Duty cycle
	TCCR0B|=(1<<CS00)|(1<<CS02); // Setting prescale to 1024
}

int main(void)
{
	setUp();
    while (1) 
    {
		PORTB|=(1<<PORTB5); 
		while((TIFR0&(1<<OCF0B))==0); // Waiting for B flag
		TIFR0|=(1<<OCF0B); // Reseting B flag
		
		PORTB&=~(1<<PORTB5); 
		while((TIFR0&(1<<OCF0A))==0); // Waiting for A flag
		TIFR0|=(1<<OCF0A); // Reseting A flag
		
		// Button is pushed and the duty cycle is less than the top
		if(!(PINB&(1<<PINB7))&&(OCR0B<OCR0A)) {
			OCR0B++; // Incrementing duty cycle
		}
		
		if(PINB&(1<<PINB7)&&(OCR0B>0)){
			OCR0B--; // Decrementing duty cycle
		}
		
    }
}

