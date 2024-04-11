/*
 * GccApplication1.c
 *
 * Created: 10/04/2024 03:19:16 م
 * Author : CRIZMA MEGA STORE
 */ 

#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include "EXTI_INTERFACE.h"
void FUN(void);
int main(void)
{

	CGI();
	DIO_Enu_Init();
	EXI_TriggerEdge(EX_INT0,RISING_EDGE);
	EXI_TriggerEdge(EX_INT1,ANY_LOGIC_CHANGE);
	EXI_TriggerEdge(EX_INT2,FALLING_EDGE);
	EXI_Enable(EX_INT0);
	EXI_Enable(EX_INT1);
	EXI_Enable(EX_INT2);
	SGI();
	EXI_SetCallBack(EX_INT0,FUN);
	EXI_SetCallBack(EX_INT1,FUN);
	EXI_SetCallBack(EX_INT2,FUN);
	while(1)
	{
	
	}
}

void FUN(void){
	DIO_Enu_TogPinValue(DIO_u8PORTD,DIO_u8PIN7);
}
