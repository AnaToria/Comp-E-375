#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/delay.h>

// dot function has 200ms time unit
void dot() {
	// Turn on the LED
	PORTB |= (1<<PORTB5);
	_delay_ms(200);
	// Turn of the LED
	PORTB &=~(1<<PORTB5);
	_delay_ms(200);
}

// dash function has 600ms time unit
void dash(){
	// Turn on the LED
	PORTB |= (1<<PORTB5);
	_delay_ms(600);
	// Turn of the LED
	PORTB &=~(1<<PORTB5);
	_delay_ms(200);
}

// spc function is for space between separate words
void spc(){
	// Turn of the LED
	PORTB &=~(1<<PORTB5);
	// 1400ms - 200ms, because I already have 200ms space between letters
	_delay_ms(1200); 
}

int main(void)
{
	// Setting port bit B5 in DDR
	DDRB |= (1<<DDB5);
	
	char input[]="Ana Toria 823359024";
	
	while (1)
	{
		// going through each character in my input
		for(int i=0; input[i]!="\0";i++){
			switch (input[i])
			{
				case 'A':
				case 'a':
					dot(); dash();
					break;
				case 'B':
				case 'b':
					dash(); dot(); dot(); dot();
					break;
				case 'C':
				case 'c':
					dash(); dot(); dash(); dot(); 
					break;
				case 'D':
				case 'd':
					dash(); dot(); dot(); 
					break;
				case 'E':
				case 'e':
					dot(); 
					break;
				case 'F':
				case 'f':
					dot(); dot(); dash(); dot(); 
					break;
				case 'G':
				case 'g':
					dash(); dash(); dot(); 
					break;
				case 'H':
				case 'h':
					dot(); dot(); dot(); dot(); 
					break;
				case 'I':
				case 'i':
					dot(); dot(); 
					break;
				case 'J':
				case 'j':
					dot(); dash(); dash(); dash(); 
					break;
				case 'K':
				case 'k':
					dash(); dot(); dash(); 
					break;
				case 'L':
				case 'l':
					dot(); dash(); dot(); dot(); 
					break;
				case 'M':
				case 'm':
					dash(); dash(); 
					break;
				case 'N':
				case 'n':
					dash(); dot(); 
					break;
				case 'O':
				case 'o':
					dash(); dash(); dash(); 
					break;
				case 'P':
				case 'p':
					dot(); dash(); dash(); dot(); 
					break;
				case 'Q':
				case 'q':
					dash(); dash(); dot(); dash(); 
					break;
				case 'R':
				case 'r':
					dot(); dash(); dot(); 
					break;
				case 'S':
				case 's':
					dot(); dot(); dot(); 
					break;
				case 'T':
				case 't':
					dash(); 
					break;
				case 'U':
				case 'u':
					dot(); dot(); dash(); 
					break;
				case 'V':
				case 'v':
					dot(); dot(); dot(); dash(); 
					break;
				case 'W':
				case 'w':
					dot(); dash(); dash(); 
					break;
				case 'X':
				case 'x':
					dash(); dot(); dot(); dash(); 
					break;
				case 'Y':
				case 'y':
					dash(); dot(); dash(); dash(); 
					break;
				case 'Z':
				case 'z':
					dash(); dash(); dot(); dot(); 
					break;
				case ' ':
					spc();
					break;
				case 1 : 
					dot(); dash(); dash(); dash(); dash(); 
					break;
				case 2 :
					dot(); dot(); dash(); dash(); dash(); 
					break;
				case 3 :
					dot(); dot(); dot(); dash(); dash();
					break;
				case 4 :
					dot(); dot(); dot(); dot(); dash();
					break;
				case 5 :
					dot(); dot(); dot(); dot(); dot(); 
					break;
				case 6 :
					dash(); dot(); dot(); dot(); dot(); 
					break;
				case 7 :
					dash(); dash(); dot(); dot(); dot(); 
					break;
				case 8 :
					dash(); dash(); dash(); dot(); dot(); 
					break;
				case 9 :
					dash(); dash(); dash(); dash(); dot(); 
					break;
				case 0 :
					dash(); dash(); dash(); dash(); dash();
					break;
			}
			if (input[i]!=' ')
			{
				// space between different letters
				PORTB &=~(1<<PORTB5);
				// 600ms - 200ms, because I already have 200ms delays after each character
				_delay_ms(400);
			}
		} 
	} 
	
}
