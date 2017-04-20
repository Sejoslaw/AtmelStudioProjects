/*
 * Fala.c
 *
 * Created: 03.06.2016 11:32:04
 * Author : Krzysztof
 */ 

#ifndef F_CPU
	#define F_CPU  16000000UL  // 16Hz clock timer
#endif

#define TICK 10

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	PORTB |= (1<<PINB0); //Turns ON LED
    while (1) // infinite loop
    {
		_delay_ms(TICK);
		PORTB |= (1<<PINB1); //Turns ON LED
		PORTB &= ~(1<<PINB0); //Turns OFF LED
		
		_delay_ms(TICK);
		PORTB |= (1<<PINB2); //Turns ON LED
		PORTB &= ~(1<<PINB1); //Turns OFF LED
		
		_delay_ms(TICK);
		PORTB |= (1<<PINB3); //Turns ON LED
		PORTB &= ~(1<<PINB2); //Turns OFF LED

		_delay_ms(TICK);
		PORTB |= (1<<PINB4); //Turns ON LED
		PORTB &= ~(1<<PINB3); //Turns OFF LED
		
		_delay_ms(TICK);
		PORTB |= (1<<PINB5); //Turns ON LED
		PORTB &= ~(1<<PINB4); //Turns OFF LED

		_delay_ms(TICK);
		PORTB |= (1<<PINB6); //Turns ON LED
		PORTB &= ~(1<<PINB5); //Turns OFF LED

		_delay_ms(TICK);
		PORTB |= (1<<PINB7); //Turns ON LED
		PORTB &= ~(1<<PINB6); //Turns OFF LED
		
		_delay_ms(TICK);
		PORTB |= (1<<PINB0); //Turns ON LED
		PORTB &= ~(1<<PINB7); //Turns OFF LED
    }
}