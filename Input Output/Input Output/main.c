/*
 * Input Output.c
 *
 * Created: 03.06.2016 10:54:40
 * Author : Krzysztof
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "avr/iom32a.h"

int main(void)
{
	DDRB |= (1<<PINB0); //Makes first pin of PORTB as Output
	DDRB = 0x01;
	DDRA &= ~(1<<PINA0);//Makes firs pin of PORTA as Input
	DDRA = 0x00; //Makes all pins of PORTA input
	while(1) //infinite loop
	{
		if((PINA & (1<<PINA0)) == 1) //If switch is pressed
		{
			PORTB |= (1<<PINB0); //Turns ON LED
			_delay_ms(50);
			PORTB &= ~(1<<PINB0); //Turns OFF LED
		}
	}
}

