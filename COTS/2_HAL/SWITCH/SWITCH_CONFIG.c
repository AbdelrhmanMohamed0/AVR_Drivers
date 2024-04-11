#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "SWITCH_PRIVATE.h"
#include "SWITCH_CONFIG.h"
#include "DIO_INTERFACE.h"

// make extern from this array into your app.c extern SW_t Switch_Arr_Stru_SwitchState [SW_NUM];

SW_t Switch_Arr_Stru_SwitchState [SW_NUM] =
{
//	    u8 SW_PortID , u8 SW_PinID , u8 SW_Status 
		{DIO_u8PORTA , DIO_u8PIN4 , DIO_u8FLOAT},
		{DIO_u8PORTD , DIO_u8PIN3 , DIO_u8PULL_UP},
		{DIO_u8PORTC , DIO_u8PIN5 , DIO_u8PULL_UP}
};
