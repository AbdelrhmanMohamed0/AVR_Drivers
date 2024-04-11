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
#include "Global.h"
#include "EXTI_CONFIG.h"
#include "EXTI_INTERFACE.h"

void FUN(void);
EXTI_t EXTI_AstrEXTIConfig[3];
int main(void)
{

	CGI();
	DIO_Enu_Init();
	EXTI_enuInit(EXTI_AstrEXTIConfig);
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
