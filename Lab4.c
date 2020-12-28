/*
 * Lab4.c
 *
 * Created: 15.11.2020 00:26:02
 * Author : anano
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

// Repeating code snippet from previous lab
void uart_initialization(){
	UBRR0H=(BAUDRATE>>8); // shifting register by 8 bits to the right
	UBRR0L=BAUDRATE;  // setting baud rate
	UCSR0B|=(1<<TXEN0); // enabling transmitter
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); // data format in 8 bit
}

void uart_transmit(char key){
	while(!(UCSR0A & (1<<UDRE0))); // waiting until the register gets free
	UDR0=key;	// load the data into the register
}


int main(void)
{
	// Setting 8 bit data frame
	uart_initialization();
	DDRD|=(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); // Output rows
	DDRB&=~(1<<DDB0)&~(1<<DDB1)&~(1<<DDB2)&~(1<<DDB3); // Input columns
	PORTB|=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3); // Setting pull up resistors
	PORTD|=(1<<4|1<<5|1<<6|1<<7); // Setting all rows high
	
	// Initialize  matrix's elements according to my real buttons' positions
	char keyboard[4][4]= {
		{'D','#','0','*'},
		{'C','9','8','7'},
		{'B','6','5','4'},
		{'A','3','2','1'}
		};
	
    while (1) 
    {
		for(int row=4;row<8;row++){
			PORTD&=~(1<<row); // Setting row low
			for (int column=0; column<4;column++)
			{
				if(!(PINB&(1<<column))){
					uart_transmit(keyboard[row-4][column]);
					_delay_ms(3500);
				}
			}
			PORTD|=(1<<row);
		}
    }
}
