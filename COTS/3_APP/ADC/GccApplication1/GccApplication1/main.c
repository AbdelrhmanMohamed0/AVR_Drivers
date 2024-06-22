/*
 * GccApplication1.c
 *
 * Created: 05/05/2024 02:46:06 م
 * Author : Abdelrhman
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "ADC_INTERFACE.h"
#include "LM35_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include <util/delay.h>

int main(void)
{
	DIO_Enu_Init();
	ADC_voidInit();
	LCD_enuInit();
	LM35_CONFIG LM1={0,5,ADC_RESOLUTION_10_BIT};
	u8 value ;
    /* Replace with your application code */
    while (1) 
    {
		LM35_u8GetTemp(&LM1,&value);
		LCD_enuSetPosition(1,1);
		LCD_enuSendNumber(value);
    }
}

