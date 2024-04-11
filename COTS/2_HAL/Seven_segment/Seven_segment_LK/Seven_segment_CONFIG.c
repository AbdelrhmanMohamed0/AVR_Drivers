#include "STD_TYPES.h"
#include "ERROR_STATES.h"

#include "DIO_INTERFACE.h"

#include "Seven_segment_CONFIG.h"
#include "Seven_segment_PRIVATE.h"

SEG_t SEVSEG_AstrSegConfig [SEG_NUM] =
{
		{DIO_u8PORTA , DIO_u8PIN3 , //pin a
		 DIO_u8PORTB , DIO_u8PIN5 , //pin b
		 DIO_u8PORTC , DIO_u8PIN2 , //pin c
		 DIO_u8PORTA , DIO_u8PIN7 , //pin d
		 DIO_u8PORTC , DIO_u8PIN5 , //pin e
		 DIO_u8PORTD , DIO_u8PIN3 , //pin f
		 DIO_u8PORTA , DIO_u8PIN0 , //pin g
		 NOT_CONNECTED , NOT_CONNECTED , //pin cmn
		 NOT_CONNECTED , NOT_CONNECTED , //pin dot
		 COMMON_CATHODE //type
		} , //seg 0

		{DIO_u8PORTA , DIO_u8PIN1 , //pin a
		 DIO_u8PORTB , DIO_u8PIN6 , //pin b
		 DIO_u8PORTC , DIO_u8PIN4 , //pin c
		 DIO_u8PORTA , DIO_u8PIN5 , //pin d
		 DIO_u8PORTC , DIO_u8PIN7 , //pin e
		 DIO_u8PORTD , DIO_u8PIN5 , //pin f
		 DIO_u8PORTA , DIO_u8PIN4 , //pin g
		 NOT_CONNECTED , NOT_CONNECTED , //pin cmn
		 NOT_CONNECTED , NOT_CONNECTED , //pin dot
		 COMMON_ANODE //type
		} // seg 1
};
