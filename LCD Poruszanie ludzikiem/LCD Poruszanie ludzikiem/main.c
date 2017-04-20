/*
 * LCD Poruszanie ludzikiem.c
 *
 * Created: 11.06.2016 21:48:46
 * Author : Krzysztof
 */ 

#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>

#include "HD44780.h"
/*
unsigned char icons[]=
{
	0x0A, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, //Char0
	0x0E, 0x1F, 0x0E, 0x04, 0x1F, 0x04, 0x0A, 0x11, //Char1
};
*/
int main(void)
{
    LCD_Initalize();
	
    while (1) 
    {
    }
}

