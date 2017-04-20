/*
 * KD Temp 3.c
 *
 * Created: 23.06.2016 12:24:36
 * Author : Krzysztof
 */ 

#define F_CPU 800000UL // 8 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "HD44780.h"
#include <avr/pgmspace.h>
#include "ds1820_vars.h"

#define PIN_1Wire 0
#define PORT_1Wire PINA
#define SET_1Wire DDRA &= ~_BV(PIN_1Wire)
#define CLEAR_1Wire DDRA |= _BV(PIN_1Wire)

#define CELCIUS_CHAR_DATA 0xdf
			
float buf[8]; // bufor do przetrzymywania wartosci
float critical_temp = 30.0; // domyslna temperatura powyzej, ktorej zapala sie dioda

//reset magistrali - czeka na impuls PRESENCE
unsigned char RESET_PULSE(void)
{
	unsigned char PRESENCE;
	CLEAR_1Wire;
	_delay_us(500);
	SET_1Wire;
	_delay_us(30);
	if(bit_is_clear(PORT_1Wire, PIN_1Wire)) 
	{
		PRESENCE=1;
	} 
	else 
	{
		PRESENCE=0;
	}
	
	//1 odebrano bit PRESENCE 0 - stan nieaktywnoœæi
	_delay_us(470);
	
	//Sprawdzenie stanu linii (czu ustawiona)
	if(bit_is_set(PORT_1Wire, PIN_1Wire)) 
	{
		PRESENCE = 1;
	} 
	else 
	{
		PRESENCE = 0;
	}
	return PRESENCE;
}

//Wysy³a do uk³adu pojedynczy bit
void send(char bit)
{
	CLEAR_1Wire;
	_delay_us(5);
	if(bit == 1)
	{
		SET_1Wire;
	}
	_delay_us(80);
	SET_1Wire;
}

//odczytywanie bitu z magistrali
unsigned char read(void)
{
	unsigned char PERSENCE = 0;
	CLEAR_1Wire;
	_delay_us(2);
	SET_1Wire;
	_delay_us(15);
	if(bit_is_set(PORT_1Wire, PIN_1Wire))
	{
		PERSENCE = 1;
	}
	else
	{
		PERSENCE = 0;
	}
	return(PERSENCE);
}
//Wysyla caly bajt do ukladu
void send_byte(char wartosc)
{
	unsigned char i;
	unsigned char pom;

	for(i = 0; i < 8; i++)
	{
		pom = wartosc >> i;
		pom &= 0x01;
		send(pom);
	}
	_delay_us(100);
}

unsigned char read_byte(void)
{
	unsigned char i;
	unsigned char wartosc = 0;
	for(i = 0; i < 8; i++)
	{
		if(read()) 
		{
			wartosc |= 0x01 << i;
		}
		_delay_us(15);
	}
	return(wartosc);
}

int main (void)
{
	char temp1 = 0, temp2 = 0;
	unsigned char sprawdz;
	
	LCD_Initalize();
	LCD_Clear();
	while(1)
	{
		sprawdz = RESET_PULSE();
		if(sprawdz == 1)
		{
			send_byte(DS1820_CMD_SKIPROM);
			send_byte(DS1820_CMD_CONVERTTEMP);
			_delay_ms(750);
			sprawdz = RESET_PULSE();
			send_byte(DS1820_CMD_SKIPROM);
			send_byte(DS1820_CMD_READSCRPAD);
			temp1 = read_byte();
			temp2 = read_byte();

			sprawdz = RESET_PULSE();
			float temp = 0;
			temp=((float)(temp1 + (temp2 * 256)) / 16);
			
			LCD_Clear();
			LCD_GoTo(0, 0);
			LCD_WriteText("Temp = ");
			LCD_GoTo(7, 0);
			LCD_WriteText(dtostrf(temp, 3, 3, buf)); 
			LCD_GoTo(13, 0);
			LCD_WriteData(CELCIUS_CHAR_DATA);
			LCD_WriteText("C");
			
			if(temp >= critical_temp)
			{
				DDRB  |= (1<<DDB0);
			}
			else
			{
				DDRB  &= ~(1<<DDB0);
			}
			_delay_ms(200);
		}
		else
		{
			LCD_Clear();
			LCD_GoTo(0,0);
			LCD_WriteText("Brak odczytu.");
		}
	}
}