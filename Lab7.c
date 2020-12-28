#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(16UL*BAUD)-1)
#define LEDON PORTB|=(1<<PORTB5)
#define LEDOFF PORTB&=~(1<<PORTB5)

// RedID:823 359 024
// x=0 => period=(x+1)=1 ms
// z=4 => frequency=(z+1)*100=500Hz=2ms

// Global variable
short int dutyCycle=0;

void keybordScan(){
	// Copied from Lab 4
	DDRD|=(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); // Output rows
	DDRB&=~(1<<DDB0)&~(1<<DDB1)&~(1<<DDB2)&~(1<<DDB3); // Input columns
	PORTB|=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3); // Setting pull up resistors
	PORTD|=(1<<4|1<<5|1<<6|1<<7); // Setting all rows high
}

void uart_initialization(){
	// Copied from Lab 4
	UBRR0H=(BAUDRATE>>8); // shifting register by 8 bits to the right
	UBRR0L=BAUDRATE;  // setting baud rate
	UCSR0B|=(1<<TXEN0); // enabling transmitter
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); // data format in 8 bit
}

void uart_transmit(char key){
	// Copied from Lab 4
	while(!(UCSR0A & (1<<UDRE0))); // waiting until the register gets free
	UDR0=key;	// load the data into the register
}

void timer0(){
	OCR0A=61.5; // 1ms period
	TCCR0A|=(1<<WGM01); // CTC mode
	TCCR0B|=(1<<CS02); // 256 Prescaler
	TIMSK0|=(1<<OCIE0A); // Enabling compare math A&B interrupts
}

void timer2(){
	OCR2A=30.25; // 2ms period;
	TCCR2A|=(1<<WGM21); // CTC mode
	TCCR2B|=(1<<CS20)|(1<<CS22); // 1024 Prescaler
	TIMSK2|=(1<<OCIE2A)|(1<<OCIE2B); // Enabling compare math A&B interrupts
}

ISR(TIMER0_COMPA_vect){
	int keyboard[4][4]= {
		{0,0,0,0},
		{0,9,8,7},
		{0,6,5,4},
		{0,3,2,1}
	};
	
	// Copied and modified from Lab 4
	for(int row=4;row<8;row++){
		PORTD&=~(1<<row); // Setting row low
		for (int column=0; column<4;column++)
		{
			if(!(PINB&(1<<column))){
				dutyCycle=keyboard[row-4][column];
				uart_transmit(keyboard[row-4][column]);
			}
		}
		PORTD|=0xF0;
	}
}

ISR(TIMER2_COMPA_vect){
	LEDON;
}

ISR(TIMER2_COMPB_vect){
	LEDOFF;	
}

int main(void)
{
	DDRB|=(1<<PORTB); // Setting output
	uart_initialization();
	keybordScan();
	timer0();
	timer2();
	sei(); // Enable global interrupt
	
	while(1)
	{
		OCR2B=OCR2A/10*dutyCycle;
	}
		
}