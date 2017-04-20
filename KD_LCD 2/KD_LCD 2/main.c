/*
 * KD_LCD 2.c
 *
 * Created: 11.06.2016 17:03:25
 * Author : Krzysztof
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"


int main(void)
{
    LCD_Initalize();   //inicjalizacja LCD
    LCD_GoTo(0, 0);      //Ustawienie kursora w pozycji (0,0)
    LCD_WriteText("Natalio pokazuje");
	LCD_GoTo(0, 1);
	LCD_WriteText("tekst xD");
}