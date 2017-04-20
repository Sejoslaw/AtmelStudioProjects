/*
 * LCD Zegar czasu dzialania.c
 *
 * Created: 11.06.2016 17:45:52
 * Author : Krzysztof
 */ 

#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>

#include "HD44780.h"

char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char* hour = "00:00:00";

char IntToChar(int x)
{
	return x + '0';
}

void Increase(int pos)
{
	if((pos != 2) || (pos != 5)) // nie licz dla ":"
	{
		if((pos == 1) || (pos == 4) || (pos == 7))
		{
			for(int i = 0; i < 10; i++)
			{
				if(i < 9)
				{
					if(hour[pos] == numbers[i])
					{
						hour[pos] = numbers[i + 1];
						break;
					}
				}
				else // zwiêkszenie po dziewiatce
				{
					hour[pos] = numbers[0];
					Increase(pos - 1);
					break;
				}
			}
		}
		else if(pos == 0)
		{
			for(int i = 0; i < 2; i++)
			{
				if(i < 9)
				{
					if(hour[pos] == numbers[i])
					{
						hour[pos] = numbers[i + 1];
						break;
					}
				}
				else // zwiêkszenie po dziewiatce
				{
					hour = "XX:XX:XX"; // tymczasowe rozwiazanie - wiecej niz 24h
					break;
				}
			}
		}
		else
		{
			for(int i = 0; i < 6; i++)
			{
				if(i < 5)
				{
					if(hour[pos] == numbers[i])
					{
						hour[pos] = numbers[i + 1];
						break;
					}
				}
				else // zwiêkszenie po dziewiatce
				{
					hour[pos] = numbers[0];
					Increase(pos - 2);
					break;
				}
			}
		}
	}
}

void AddSecond()
{
	Increase(7);
}

int main(void)
{
    LCD_Initalize(); // Inicjalizacja ekranu oraz bblioteki
	
	while(1)
	{
		LCD_Clear();
		
		LCD_GoTo(0, 0); // Ustawienie sie na pozycji x = 0, y = 0
		LCD_WriteText("Czas dzialania:"); // Pierwsza linijka tekstu
		
		LCD_GoTo(0, 1);
		LCD_WriteText(hour);
		
		AddSecond();
		
		_delay_ms(64);
	}
}