 /*
 * GccApplication1.c
 *
 * Created: 6/19/2024 7:19:48 PM
 * Author : Abdelrhman
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "GIE_interface.h"
#include "MAPPING.h"
#include "DCMOTOR_INTERFACE.h"
#include "ADC_INTERFACE.h"
#include "TIMER_interface.h"
#include "EXTI_INTERFACE.h"
#include "SWITCH_CONFIG.h"
#include "SWITCH_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include <avr/io.h>

extern SW_t Switch_Arr_Stru_SwitchState [SW_NUM];
int main(void)
{
	GIE_VoidEnable();
	DIO_Enu_Init();
	SWITCH_EnuInit(Switch_Arr_Stru_SwitchState);
	TIMER0_voidInit();
	TIMER2_voidInit();
	TIMER1_voidInit();
	ADC_voidInit();
	LCD_enuInit();
	LCD_enuClearScreen();
	u8 pin_state1 ,pin_state2;
	u32 res=100;
	u8 ctc=100;
	MAPPING_CONFIG mapp1=
	   { 0,
		1023,
		0,
		255,
	 res};
	 	MAPPING_CONFIG mapp2=
	 	{ 0,
		 	1023,
		 	3999,
		 	7999,
	 	res};
	while(1)
	{
		SWITCH_EnuGetStates(&Switch_Arr_Stru_SwitchState[0], &pin_state1);
		if (pin_state1 ==0)
		{
			ctc+=20;
			TIMER0_voidSetCTC(ctc);
			while(pin_state1==0){
				SWITCH_EnuGetStates(&Switch_Arr_Stru_SwitchState[0], &pin_state1);
			}
		}
		SWITCH_EnuGetStates(&Switch_Arr_Stru_SwitchState[1], &pin_state2);
				if (pin_state2 ==0)
				{
					ctc-=20;
					TIMER0_voidSetCTC(ctc);
			while(pin_state2==0){
				SWITCH_EnuGetStates(&Switch_Arr_Stru_SwitchState[1], &pin_state2);
			}
				}
	ADC_u8GetResultSync(0,(u16*)&res);
	MAPPING_u32GetOutput(&mapp2);	
    	TIMER1_voidSetCTCA((u16)res);
		LCD_enuSetPosition(2,1);
		LCD_WriteNumberIn4Digits((u16)res);
	ADC_u8GetResultSync(0,(u16*)&res);
	MAPPING_u32GetOutput(&mapp1);
	TIMER2_voidSetCTC((u8)res);
	LCD_enuSetPosition(1,1);
	LCD_WriteNumberIn3Digits((u8)res);

	}
}

