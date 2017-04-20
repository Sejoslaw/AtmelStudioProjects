/*
 * _4Lampki_StartPB0.cpp
 *
 * Created: 2015-08-06 13:46:57
 *  Author: Krzysztof
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PINB0);
	DDRB0 |= DDRB;
	DDRB1 |= DDRB;
	DDRB2 |= DDRB;
	DDRB3 |= DDRB;
	PORTB &= ~(1 << PINB0);
	PORTB0 |= PORTB;
	PORTB1 |= PORTB;
	PORTB2 |= PORTB;
	PORTB3 |= PORTB;
	
    while(1)
    {
		PORTB ^= (1 << PINB0);
		_delay_ms(1000);
    }
}