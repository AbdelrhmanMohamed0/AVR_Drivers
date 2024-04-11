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
#include <util/delay.h>

int main(void)
{
	DIO_Enu_Init();
	LCD_enuInit();
	u8 value,len=0;
	u8 str[50]="Abdelrhman ->>";
	u8 x=1,y=1,flag=1;
	while(str[len])
	len++;
	/* Replace with your application code */
	while (1)
	{
		//app1
		/*
		for(u8 i=len;i>1;i--){
		LCD_enuSendString(str+i-1);
		LCD_enuClearScreen();
		}
		for(u8 i=1;i<=16;i++){
		LCD_enuSetPosition(1,i);
		LCD_enuSendString(str);
		LCD_enuClearScreen();
		}
		
		for(u8 i=len;i>1;i--){
		LCD_enuSetPosition(2,1);
		LCD_enuSendString(str+i-1);
		LCD_enuClearScreen();
		}
		for(u8 i=1;i<=16;i++){
		LCD_enuSetPosition(2,i);
		LCD_enuSendString(str);
		LCD_enuClearScreen();
		}
		*/
		//app2
		LCD_enuSetPosition(x,y);
		LCD_enuSendData('A');
		
		if(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN0,&value)&&value==0)
		{

			if (flag==1)
			{
				x = 2;
				flag=0;
			}
			else{
				x = 1;
				flag=1;
			}
			while(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN0,&value)&&value==0);
			LCD_enuClearScreen();
		}
		
		
		if(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN1,&value)&&value==0)
		{
			y++;
			if(y==17)
			y=1;
			while(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN1,&value)&&value==0);
			LCD_enuClearScreen();
		}
		if(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN2,&value)&&value==0)
		{
			y--;
			if(y==0)
			y=16;
			while(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN2,&value)&&value==0);
			LCD_enuClearScreen();
		}
		if(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&value)&&value==0)
		{

			if (flag==1)
			{
				x = 2;
				flag=0;
			}
			else{
				x = 1;
				flag=1;
			}
			while(DIO_Enu_GetPinValue(DIO_u8PORTA,DIO_u8PIN3,&value)&&value==0);
			LCD_enuClearScreen();
		}
	}
}

