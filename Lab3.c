/*
 * Lab3.c
 *
 * Created: 10.11.2020 00:33:13
 * Author : anano
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL 
#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) 

void uart_initilation(){
	UBRR0H=(BAUDRATE>>8); // shifting register by 8 bits to the right
	UBRR0L=BAUDRATE;  // setting baud rate
	UCSR0B|=(1<<TXEN0); // enabling transmitter
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); // data format in 8 bit
}

void uart_transmit(char redID){
	while(!(UCSR0A & (1<<UDRE0))); // waiting until the register gets free
	UDR0=redID;	// load the data into the register
}

int main(void)
{
    uart_initilation();
	char redID[]="823359024\r\n";
	while (1) 
    {
		for (int i=0; redID[i]!='\0';i++)
		{
			uart_transmit(redID[i]);
			_delay_ms(500);
		}
		
    }
}

