#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
    // Setting port bit B5 in DDR
    DDRB |= (1<<DDB5);
	while (1) 
    {
		// Turn on the LED
		PORTB |= (1<<PORTB5);
		_delay_ms(100);
		// Turn of the LED
		PORTB &=~(1<<PORTB5);
		_delay_ms(100);
    }
	
}

