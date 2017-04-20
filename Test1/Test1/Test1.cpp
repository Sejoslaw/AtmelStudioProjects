/*
 * Test1.cpp
 *
 * Created: 2015-08-04 19:22:15
 *  Author: Krzysztof
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PINB0);
	PORTB0 &= ~(1 << PINB0);
	
    while(1)
    {
        PORTB0 ^= (1 << PINB0);
		_delay_ms(500);
    }
}