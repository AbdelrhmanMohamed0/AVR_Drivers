/*
 * GccApplication1.c
 *
 * Created: 9/14/2022 3:10:31 AM
 * Author : Abdelrhman
 */ 
#define F_CPU 1000000UL 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include <util/delay.h>

int main(void)
{
	LCD_enuInit();
	

    /* Replace with your application code */
    while (1) 
    {
			LCD_enuSetPosition(1,8);
			LCD_enuSendNumber(45);
			_delay_ms(500);
			LCD_enuSetPosition(2,3);
			LCD_enuSendString("Abdelrhman");
			_delay_ms(500);
			LCD_enuClearScreen();
			LCD_enuSendExtraChar(2,8);
			_delay_ms(500);
			LCD_enuClearScreen();
	}
}

