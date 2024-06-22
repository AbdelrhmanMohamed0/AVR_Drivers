
#include "../4_LIB/STD_TYPES.h"
#include "../4_LIB/BIT_MATH.h"
#include "../1_MCAL/DIO/DIO_interface.h"
#include "BUZ_interface.h"

void BUZ_voidInit( BUZ_Type *BUZ_Configuration )
{
	
	DIO_Enu_SetPinDirection( BUZ_Configuration->Port , BUZ_Configuration->Pin , DIO_u8OUTPUT );
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void BUZ_voidOn  ( BUZ_Type *BUZ_Configuration )
{
	
	if( BUZ_Configuration->Active_State == ACTIVE_HIGH ){
		
		DIO_Enu_SetPinValue( BUZ_Configuration->Port , BUZ_Configuration->Pin , DIO_u8HIGH );
		
	}else if( BUZ_Configuration->Active_State == ACTIVE_LOW ){
		
		DIO_Enu_SetPinValue( BUZ_Configuration->Port , BUZ_Configuration->Pin , DIO_u8LOW  );
		
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void BUZ_voidOff ( BUZ_Type *BUZ_Configuration )
{
	
	if( BUZ_Configuration->Active_State == ACTIVE_HIGH ){
		
		DIO_Enu_SetPinValue( BUZ_Configuration->Port , BUZ_Configuration->Pin , DIO_u8LOW  );
		
	}else if( BUZ_Configuration->Active_State == ACTIVE_LOW ){
		
		DIO_Enu_SetPinValue( BUZ_Configuration->Port , BUZ_Configuration->Pin , DIO_u8HIGH  );
		
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void BUZ_voidToggle  ( BUZ_Type *BUZ_Configuration )
{
	DIO_Enu_TogPinValue  ( BUZ_Configuration->Port , BUZ_Configuration->Pin );
}

