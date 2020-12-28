#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(16UL*BAUD)-1)
#define LEDON PORTB|=(1<<PORTB5)
#define LEDOFF PORTB&=~(1<<PORTB5)

short int potentiometer=0;

// RedID:823 359 024
// x=0 => period=(x+1)=1 ms
// y=2 => input channel=(y%8)=2
// z=4 => frequency=(z+1)*100=500Hz=2ms

// Copied form Lab 7
void timer0(){
	OCR0A=61.5; // 1ms period
	TCCR0A|=(1<<WGM01); // CTC mode
	TCCR0B|=(1<<CS02); // 256 Prescaler
	TIMSK0|=(1<<OCIE0A); // Enabling compare math A&B interrupts
}

// Copied form Lab 7
void timer2(){
	OCR2A=30.25; // 2ms period;
	TCCR2A|=(1<<WGM21); // CTC mode
	TCCR2B|=(1<<CS20)|(1<<CS22); // 1024 Prescaler
	TIMSK2|=(1<<OCIE2A)|(1<<OCIE2B); // Enabling compare math A&B interrupts
}

void adc_init(){
	DDRC &= ~(1<<PINC2);
	ADMUX|=(1<<6)|(1<<1); // VCC
	ADCSRA |= (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADPS2); // Enabling ADC auto trigger}
	ADCSRB |= (1<<ADTS1)|(1<<ADTS0); // Comparing the match
}

ISR(ADC_vect){
	uint16_t potentiometer = ADC; // Initializing 16-bit ADC potentiometer
	OCR2B =OCR2A*(potentiometer/1023.0);
}

ISR(TIMER2_COMPA_vect){
	LEDON;
}
ISR(TIMER2_COMPB_vect){
	if(OCR2B!=OCR2A){
		LEDOFF;
	}
}
ISR (TIMER0_COMPA_vect){
	ADCSRA|=(1<<6);
}

int main(void)
{
	timer0();
	timer2();
	adc_init();
	sei();
	DDRB|=(1<<5);
	while (1)
	{
	}
}