#include "APP.h"
#include "..\1_MCAL\EXTI\EXTI_INTERFACE.h"

volatile u8 Mode = 0;
volatile u8 LOC_u8PinState = 1;
volatile u8 pressed_key;
void FUN(void)
{
	if (pressed_key == 'M')
	{
		DIO_Enu_GetPinValue(DIO_u8PORTD, DIO_u8PIN1, &LOC_u8PinState);
		if (LOC_u8PinState == 0)
		{
			Mode = (Mode % 3) + 1;
			LOC_u8PinState = 1;
		}
	}
}

int main(void)
{
	DIO_Enu_Init();
	LCD_enuInit();
	KPD_enu_Init();
	CGI();
	EXI_TriggerEdge(EX_INT0, FALLING_EDGE);
	EXI_Enable(EX_INT0);
	SGI();
	EXI_SetCallBack(EX_INT0, FUN);
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("Welcome press(M) ");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("1-CAL 2-NUM 3-GM ");
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while (pressed_key == 0xff);
	} while (pressed_key != 'M');
	Mode = 1;
	LCD_enuClearScreen();
	while (1)
	{

		switch (Mode)
		{
		case 1:
			Mode1();
			break;
		case 2:
			Mode2();
			break;
		case 3:
			Mode3();
			break;
		}
	}
}
