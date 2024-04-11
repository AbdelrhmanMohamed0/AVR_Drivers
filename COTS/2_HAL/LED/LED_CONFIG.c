
#include "STD_TYPES.h"
#include "ERROR_STATES.h"

#include "DIO_INTERFACE.h"
#include "LED_CONFIG.h"
#include "LED_PRIVATE.h"

LED_t LED_Arr_Str_LedConfig [LED_NUM] =
{
		{DIO_u8PORTA, DIO_u8PIN5, LED_SINK, LED_OFF},
		{DIO_u8PORTB, DIO_u8PIN2, LED_SOURCE, LED_ON},
		{DIO_u8PORTC, DIO_u8PIN1, LED_SOURCE, LED_OFF}
};
