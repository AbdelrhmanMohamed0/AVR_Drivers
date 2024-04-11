#include "STD_TYPES.h"
#include "ERROR_STATES.h"

#include "DIO_INTERFACE.h"

#include "Seven_segment_CONFIG.h"
#include "Seven_segment_PRIVATE.h"

extern SEG_t SEVSEG_AstrSegConfig [SEG_NUM];

ES_t Seven_Segment_enuInit(SEG_t * Copy_pstrSegConfig)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	u8 Local_u8Iter =0;
	for (Local_u8Iter=0; Local_u8Iter < SEG_NUM; Local_u8Iter++)
	{
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8APort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8APin, DIO_u8OUTPUT);
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8BPort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8BPin, DIO_u8OUTPUT);
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8CPort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8CPin, DIO_u8OUTPUT);
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8DPort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8DPin, DIO_u8OUTPUT);
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8EPort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8EPin, DIO_u8OUTPUT);
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8FPort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8FPin, DIO_u8OUTPUT);
		DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8GPort,Copy_pstrSegConfig[Local_u8Iter].SEG_u8GPin, DIO_u8OUTPUT);

		if (Copy_pstrSegConfig[Local_u8Iter].SEG_u8CMN_Port != NOT_CONNECTED &&
				Copy_pstrSegConfig[Local_u8Iter].SEG_u8CMN_Pin != NOT_CONNECTED)
		{
			DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8CMN_Port ,Copy_pstrSegConfig[Local_u8Iter].SEG_u8CMN_Pin , DIO_u8OUTPUT );
		}

		if (Copy_pstrSegConfig[Local_u8Iter].SEG_u8DOT_Port != NOT_CONNECTED &&
				Copy_pstrSegConfig[Local_u8Iter].SEG_u8DOT_Pin != NOT_CONNECTED)
		{
			DIO_Enu_SetPinDirection(Copy_pstrSegConfig[Local_u8Iter].SEG_u8DOT_Port ,Copy_pstrSegConfig[Local_u8Iter].SEG_u8DOT_Pin , DIO_u8OUTPUT );
		}
	}

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8SegID,u8 Copy_u8Num)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_u8Num <10 && Copy_u8SegID < SEG_NUM)
	{
		if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_CATHODE)
		{
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APin , ((SEG_Au8NumDisplay[Copy_u8Num]>>0) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPin , ((SEG_Au8NumDisplay[Copy_u8Num]>>1) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPin , ((SEG_Au8NumDisplay[Copy_u8Num]>>2) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPin , ((SEG_Au8NumDisplay[Copy_u8Num]>>3) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPin , ((SEG_Au8NumDisplay[Copy_u8Num]>>4) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPin , ((SEG_Au8NumDisplay[Copy_u8Num]>>5) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPin , ((SEG_Au8NumDisplay[Copy_u8Num]>>6) &1) );

		}
		else if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_ANODE)
		{
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APin , !((SEG_Au8NumDisplay[Copy_u8Num]>>0) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPin , !((SEG_Au8NumDisplay[Copy_u8Num]>>1) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPin , !((SEG_Au8NumDisplay[Copy_u8Num]>>2) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPin , !((SEG_Au8NumDisplay[Copy_u8Num]>>3) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPin , !((SEG_Au8NumDisplay[Copy_u8Num]>>4) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPin , !((SEG_Au8NumDisplay[Copy_u8Num]>>5) &1) );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPin , !((SEG_Au8NumDisplay[Copy_u8Num]>>6) &1) );

		}
	}

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuEnableCommon(u8 Copy_u8SegID)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_u8SegID < SEG_NUM)
	{
		if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Port != NOT_CONNECTED &&
				SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Pin != NOT_CONNECTED)
		{
			if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_CATHODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Pin , DIO_u8LOW);
			}
			else if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_ANODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Pin , DIO_u8HIGH);
			}
		}
	}

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisableCommon(u8 Copy_u8SegID)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_u8SegID < SEG_NUM)
	{
		if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Port != NOT_CONNECTED &&
				SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Pin != NOT_CONNECTED)
		{
			if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_CATHODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Pin , DIO_u8HIGH);
			}
			else if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_ANODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CMN_Pin , DIO_u8LOW);
			}
		}
	}

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuEnableDot(u8 Copy_u8SegID)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_u8SegID < SEG_NUM)
	{
		if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Port != NOT_CONNECTED &&
				SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Pin != NOT_CONNECTED)
		{
			if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_CATHODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Pin , DIO_u8HIGH);
			}
			else if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_ANODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Pin , DIO_u8LOW);
			}
		}
	}


	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisableDot(u8 Copy_u8SegID)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_u8SegID < SEG_NUM)
	{
		if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Port != NOT_CONNECTED &&
				SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Pin != NOT_CONNECTED)
		{
			if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_CATHODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Pin , DIO_u8LOW);
			}
			else if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_ANODE)
			{
				DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Port, SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DOT_Pin , DIO_u8HIGH);
			}
		}
	}

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuClearDisplay(u8 Copy_u8SegID)
{
	ES_t Local_enuErrorState = ES_NOT_OK;

	if (Copy_u8SegID < SEG_NUM)
	{
		if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_CATHODE)
		{
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APin , DIO_u8LOW );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPin , DIO_u8LOW );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPin , DIO_u8LOW );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPin , DIO_u8LOW );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPin , DIO_u8LOW );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPin , DIO_u8LOW );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPin , DIO_u8LOW );

		}
		else if (SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8Type == COMMON_ANODE)
		{
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8APin , DIO_u8HIGH );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8BPin , DIO_u8HIGH );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8CPin , DIO_u8HIGH );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8DPin , DIO_u8HIGH );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8EPin , DIO_u8HIGH );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8FPin , DIO_u8HIGH );
			DIO_Enu_SetPinValue(SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPort ,SEVSEG_AstrSegConfig[Copy_u8SegID].SEG_u8GPin , DIO_u8HIGH );

		}
	}

	return Local_enuErrorState;
}



