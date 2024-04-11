
#include "STD_TYPES.h"
#include "ERROR_STATES.h"

#include "DIO_INTERFACE.h"
#include "LED_CONFIG.h"
#include "LED_PRIVATE.h"

ES_t LED_EnuInit(LED_t *Copy_P_Str_LedConfig)
{
    ES_t Local_enuErrorState = ES_NOT_OK;

    if (Copy_P_Str_LedConfig != NULL)
    {
        u8 Local_enuIterator = 0;
        for (Local_enuIterator = 0; Local_enuIterator < LED_NUM; Local_enuIterator++)
        {
            Local_enuErrorState = DIO_Enu_SetPinDirection(Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PortID, Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PinID, DIO_u8OUTPUT);
            if (Copy_P_Str_LedConfig[Local_enuIterator].LED_u8Connection == LED_SINK)
            {
                if (Copy_P_Str_LedConfig[Local_enuIterator].LED_u8InitState == LED_ON)
                {
                    Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PortID, Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PinID, DIO_u8LOW);
                }
                else if (Copy_P_Str_LedConfig[Local_enuIterator].LED_u8InitState == LED_OFF)
                {
                    Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PortID, Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PinID, DIO_u8HIGH);
                }
                else
                {
                    return ES_OUT_OF_RANGE;
                }
            }
            else if (Copy_P_Str_LedConfig[Local_enuIterator].LED_u8Connection == LED_SOURCE)
            {
                if (Copy_P_Str_LedConfig[Local_enuIterator].LED_u8InitState == LED_ON)
                {
                    Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PortID, Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PinID, DIO_u8HIGH);
                }
                else if (Copy_P_Str_LedConfig[Local_enuIterator].LED_u8InitState == LED_OFF)
                {
                    Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PortID, Copy_P_Str_LedConfig[Local_enuIterator].LED_u8PinID, DIO_u8LOW);
                }
                else
                {
                    return ES_OUT_OF_RANGE;
                }
            }
            else
            {
                return ES_OUT_OF_RANGE;
            }
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }

    return Local_enuErrorState;
}

ES_t LED_EnuTurnON(LED_t *Copy_P_Str_LedID)
{
    ES_t Local_enuErrorState = ES_NOT_OK;

    if (Copy_P_Str_LedID != NULL)
    {
        if (Copy_P_Str_LedID->LED_u8Connection == LED_SINK)
        {
            Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedID->LED_u8PortID, Copy_P_Str_LedID->LED_u8PinID, DIO_u8LOW);
        }
        else if (Copy_P_Str_LedID->LED_u8Connection == LED_SOURCE)
        {
            Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedID->LED_u8PortID, Copy_P_Str_LedID->LED_u8PinID, DIO_u8HIGH);
        }
        else
        {
            Local_enuErrorState = ES_OUT_OF_RANGE;
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }

    return Local_enuErrorState;
}

ES_t LED_EnuTurnOFF(LED_t *Copy_P_Str_LedID)
{
    ES_t Local_enuErrorState = ES_NOT_OK;

    if (Copy_P_Str_LedID != NULL)
    {
        if (Copy_P_Str_LedID->LED_u8Connection == LED_SINK)
        {
            Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedID->LED_u8PortID, Copy_P_Str_LedID->LED_u8PinID, DIO_u8HIGH);
        }
        else if (Copy_P_Str_LedID->LED_u8Connection == LED_SOURCE)
        {
            Local_enuErrorState = DIO_Enu_SetPinValue(Copy_P_Str_LedID->LED_u8PortID, Copy_P_Str_LedID->LED_u8PinID, DIO_u8LOW);
        }
        else
        {
            Local_enuErrorState = ES_OUT_OF_RANGE;
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }

    return Local_enuErrorState;
}
