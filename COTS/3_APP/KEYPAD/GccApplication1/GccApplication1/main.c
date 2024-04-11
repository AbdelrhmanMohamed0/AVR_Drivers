/*
* GccApplication2.c
*
* Created: 07/04/2024 05:27:34 ص
* Author : CRIZMA MEGA STORE
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "KEYPAD_INTERFACE.h"
#include <util/delay.h>

int main(void)
{
	DIO_Enu_Init();
	LCD_enuInit();
	KPD_enu_Init();
u8 pressed_key;

	while(1){
		do{
		KPD_enu_GetPressed(&pressed_key);
		}while(pressed_key==0xff);
		LCD_enuSendData(pressed_key);
	}
}

