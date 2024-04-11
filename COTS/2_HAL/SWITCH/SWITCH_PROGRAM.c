#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "SWITCH_PRIVATE.h"
#include "SWITCH_CONFIG.h"
#include "DIO_INTERFACE.h"

ES_t SWITCH_EnuInit(SW_t *Copy_P_Arr_Str_Switchs)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;

    if (Copy_P_Arr_Str_Switchs != NULL)
    {
        u8 Local_u8Iterator = 0;
        for (Local_u8Iterator = 0; Local_u8Iterator < SW_NUM; Local_u8Iterator++)
        {
            Local_EnuErrorState = DIO_Enu_SetPinDirection(Copy_P_Arr_Str_Switchs[Local_u8Iterator].SW_PortID, Copy_P_Arr_Str_Switchs[Local_u8Iterator].SW_PinID, DIO_u8INPUT);
            Local_EnuErrorState = DIO_Enu_SetPinValue(Copy_P_Arr_Str_Switchs[Local_u8Iterator].SW_PortID, Copy_P_Arr_Str_Switchs[Local_u8Iterator].SW_PinID, Copy_P_Arr_Str_Switchs[Local_u8Iterator].SW_Status);
        }
    }
    else
    {
        Local_EnuErrorState = ES_NULL_POINTER;
    }

    return Local_EnuErrorState;
}
ES_t SWITCH_EnuGetStates(SW_t *Copy_P_Arr_Str_Switch, u8 *Copy_pu8SwState)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;

    if (Copy_P_Arr_Str_Switch != NULL && Copy_pu8SwState != NULL)
    {
        Local_EnuErrorState = DIO_Enu_GetPinValue(Copy_P_Arr_Str_Switch->SW_PortID, Copy_P_Arr_Str_Switch->SW_PinID, Copy_pu8SwState);
    }
    else
    {
        Local_EnuErrorState = ES_NULL_POINTER;
    }

    return Local_EnuErrorState;
}