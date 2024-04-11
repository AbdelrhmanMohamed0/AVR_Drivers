#include "STD_TYPES.h"
#include "ERROR_STATES.h"

#include "DIO_INTERFACE.h"
#include "LED_CONFIG.h"
#include "LED_INTERFACE.h"
#include "SWITCH_CONFIG.h"
#include "SWITCH_INTERFACE.h"
#include <util/delay.h>

extern LED_t LED_Arr_Str_LedConfig [LED_NUM];
extern SW_t Switch_Arr_Stru_SwitchState [SW_NUM];
int main(void)
{
	DIO_Enu_Init();
	LED_EnuInit(LED_Arr_Str_LedConfig);
	SWITCH_EnuInit(Switch_Arr_Stru_SwitchState);
	u8 pinstate=0;
	while (1)
	{
		SWITCH_EnuGetStates(&Switch_Arr_Stru_SwitchState[1] , &pinstate);
		if (pinstate==0){
			LED_EnuTurnON(&LED_Arr_Str_LedConfig[1]);
			_delay_ms(50);
		}
		else{
			LED_EnuTurnOFF(&LED_Arr_Str_LedConfig[1]);
			_delay_ms(50);
		}
	}
}
