
#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "SWITCH_CONFIG.h"
#include "SWITCH_INTERFACE.h"
#include <util/delay.h>
extern SW_t Switch_Arr_Stru_SwitchState [SW_NUM];
int main(void)
{
	DIO_Enu_Init();
	SWITCH_EnuInit(Switch_Arr_Stru_SwitchState);
	u8 pin_state;
	while(1)
	{
		SWITCH_EnuGetStates(&Switch_Arr_Stru_SwitchState[1], &pin_state);
		if (pin_state ==0)
		{
			DIO_Enu_SetPinValue(DIO_u8PORTA, DIO_u8PIN0 , DIO_u8HIGH);
			_delay_ms(250);
		}
		else
		{
			DIO_Enu_SetPinValue(DIO_u8PORTA, DIO_u8PIN0 , DIO_u8LOW);
			_delay_ms(250);
		}
	}
}
