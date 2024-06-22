#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"

#include "DIO_INTERFACE.h"
#include "ADC_INTERFACE.h"

#include "LM35_INTERFACE.h"
#include "LM35_PRIVATE.h"


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function initialize the pin which connected to led as output pin
* Parameters :
            => struct has the LM35 Channel, ADC VoltageReference , ADCResolution
			=> Pointer to TEMP Variable which will return in it 
* return : Error State
*/
ES_t LM35_u8GetTemp (LM35_CONFIG * lm35 , u8 * Copy_u8TempValue)
{
	ES_t Local_u8ErrorState = ES_OK;

	u16 Local_u16ADCResult ;
	u16 Local_u16AnalogValue ;
	
	u16 Local_u8ADCReference = ( lm35->Copy_u8ADCVoltageReference ) * 1000 ;  // To Convert from ( V --> mV )
	
	
	/* ADC Digital Reading  */
	ADC_u8GetResultSync( lm35->Copy_u8LM35Channel , &Local_u16ADCResult ) ;

	/* Check for ADC Resolution  */
	if ( lm35->Copy_u8ADCResolution == ADC_RESOLUTION_10_BIT )
	{
		Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 1024UL) ;

	}
	else if ( lm35->Copy_u8ADCResolution == ADC_RESOLUTION_8_BIT )
	{
		Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 256UL) ;
	}


	/* Convert ( mv --> Temp ) */
	* Copy_u8TempValue = Local_u16AnalogValue / 10 ;

	return Local_u8ErrorState ;
}
