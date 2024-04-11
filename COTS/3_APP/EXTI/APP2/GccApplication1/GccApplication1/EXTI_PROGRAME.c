#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "BIT_MATH.h"
#include "EXTI_PRIVATE.h"
#include "Global.h"
#include "EXTI_CONFIG.h"
#include "EXTI_INTERFACE.h"


static void (*INT0_Fptr)(void) = NULL;
static void (*INT1_Fptr)(void) = NULL;
static void (*INT2_Fptr)(void) = NULL;

ES_t EXTI_enuInit(EXTI_t *Copy_pstrEXTIConfig)
{
    ES_t Local_enuErrorState = ES_NOT_OK;
    if (Copy_pstrEXTIConfig != NULL)
    {
        u8 Local_u8Iter = 0;
        for (Local_u8Iter = 0; Local_u8Iter < 3; Local_u8Iter++)
        {
            if (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8State == ACTIVE)
            {
                switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_NUM)
                {
                case EX_INT0:
                    CLR_BIT(MCUCR, ISC00);
                    CLR_BIT(MCUCR, ISC01);
                    SET_BIT(GICR, INT0);
                    switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_enuSenceLevel)
                    {
                    case LOW_LEVEL:
                        CLR_BIT(MCUCR, ISC00);
                        CLR_BIT(MCUCR, ISC01);
                        break;
                    case ANY_LOGIC_CHANGE:
                        SET_BIT(MCUCR, ISC00);
                        CLR_BIT(MCUCR, ISC01);
                        break;
                    case FALLING_EDGE:
                        CLR_BIT(MCUCR, ISC00);
                        SET_BIT(MCUCR, ISC01);
                        break;
                    case RISING_EDGE:
                        SET_BIT(MCUCR, ISC00);
                        SET_BIT(MCUCR, ISC01);
                        break;
                    default:
                        Local_enuErrorState = ES_OUT_OF_RANGE;
                        break;
                    }
                    break;
                case EX_INT1:
                    CLR_BIT(MCUCR, ISC10);
                    CLR_BIT(MCUCR, ISC11);
                    SET_BIT(GICR, INT1);
                    switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_enuSenceLevel)
                    {
                    case LOW_LEVEL:
                        CLR_BIT(MCUCR, ISC10);
                        CLR_BIT(MCUCR, ISC11);
                        break;
                    case ANY_LOGIC_CHANGE:
                        SET_BIT(MCUCR, ISC10);
                        CLR_BIT(MCUCR, ISC11);
                        break;
                    case FALLING_EDGE:
                        CLR_BIT(MCUCR, ISC10);
                        SET_BIT(MCUCR, ISC11);
                        break;
                    case RISING_EDGE:
                        SET_BIT(MCUCR, ISC10);
                        SET_BIT(MCUCR, ISC11);
                        break;
                    default:
                        Local_enuErrorState = ES_OUT_OF_RANGE;
                        break;
                    }
                    break;
                case EX_INT2:
                    CLR_BIT(MCUCR, ISC2);
                    SET_BIT(GICR, INT2);
                    switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_enuSenceLevel)
                    {
                    case FALLING_EDGE:
                        CLR_BIT(MCUCSR, ISC2);
                        break;
                    case RISING_EDGE:
                        SET_BIT(MCUCSR, ISC2);
                        break;
                    default:
                        Local_enuErrorState = ES_OUT_OF_RANGE;
                        break;
                    }
                    break;
                }
            }
            else if (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_u8State == DEACTIVE)
            {
                switch (Copy_pstrEXTIConfig[Local_u8Iter].EXTI_NUM)
                {
                case EX_INT0:
                    CLR_BIT(GICR, INT0);
                    break;
                case EX_INT1:
                    CLR_BIT(GICR, INT1);
                    break;
                case EX_INT2:
                    CLR_BIT(GICR, INT2);
                    break;
                default:
                    Local_enuErrorState = ES_OUT_OF_RANGE;
                    break;
                }
            }
        }
    }
    else
    {
        Local_enuErrorState = ES_NULL_POINTER;
    }
    return Local_enuErrorState;
}
ES_t EXTI_enuSenseMode(ExInterruptSource_type Copy_enuEXTI_ID, TriggerEdge_type Copy_enuSenseLevel)
{
    ES_t Local_enuErrorState = ES_NOT_OK;
    if (Copy_enuEXTI_ID <= EX_INT2)
    {
        switch (Copy_enuEXTI_ID)
        {
        case EX_INT0:
            switch (Copy_enuSenseLevel)
            {
            case LOW_LEVEL:
                CLR_BIT(MCUCR, ISC00);
                CLR_BIT(MCUCR, ISC01);
                break;
            case ANY_LOGIC_CHANGE:
                SET_BIT(MCUCR, ISC00);
                CLR_BIT(MCUCR, ISC01);
                break;
            case FALLING_EDGE:
                CLR_BIT(MCUCR, ISC00);
                SET_BIT(MCUCR, ISC01);
                break;
            case RISING_EDGE:
                SET_BIT(MCUCR, ISC00);
                SET_BIT(MCUCR, ISC01);
                break;
            }
            break;
        case EX_INT1:
            switch (Copy_enuSenseLevel)
            {
            case LOW_LEVEL:
                CLR_BIT(MCUCR, ISC10);
                CLR_BIT(MCUCR, ISC11);
                break;
            case ANY_LOGIC_CHANGE:
                SET_BIT(MCUCR, ISC10);
                CLR_BIT(MCUCR, ISC11);
                break;
            case FALLING_EDGE:
                CLR_BIT(MCUCR, ISC10);
                SET_BIT(MCUCR, ISC11);
                break;
            case RISING_EDGE:
                SET_BIT(MCUCR, ISC10);
                SET_BIT(MCUCR, ISC11);
                break;
            }
            break;
        case EX_INT2:
            switch (Copy_enuSenseLevel)
            {
            case FALLING_EDGE:
                CLR_BIT(MCUCSR, ISC2);
                break;
            case RISING_EDGE:
                SET_BIT(MCUCSR, ISC2);
                break;
            default:
                CLR_BIT(MCUCSR, ISC2);
            }
            break;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}
ES_t EXTI_enuEnableINT(ExInterruptSource_type Copy_enuEXTI_ID)
{
    ES_t Local_enuErrorState = ES_NOT_OK;
    if (Copy_enuEXTI_ID <= EX_INT2)
    {
        switch (Copy_enuEXTI_ID)
        {
        case EX_INT0:
            SET_BIT(GICR, INT0);
            break;
        case EX_INT1:
            SET_BIT(GICR, INT1);
            break;
        case EX_INT2:
            SET_BIT(GICR, INT2);
            break;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}
ES_t EXTI_enuDisableINT(ExInterruptSource_type Copy_enuEXTI_ID)
{
    ES_t Local_enuErrorState = ES_NOT_OK;
    if (Copy_enuEXTI_ID <= EX_INT2)
    {
        switch (Copy_enuEXTI_ID)
        {
        case EX_INT0:
            CLR_BIT(GICR, INT0);
            break;
        case EX_INT1:
            CLR_BIT(GICR, INT1);
            break;
        case EX_INT2:
            CLR_BIT(GICR, INT2);
            break;
        }
    }
    else
    {
        Local_enuErrorState = ES_OUT_OF_RANGE;
    }
    return Local_enuErrorState;
}

void EXI_SetCallBack(ExInterruptSource_type Copy_enuEXTI_ID, void (*LocalPtr)(void))
{
    switch (Copy_enuEXTI_ID)
    {
    case EX_INT0:
        INT0_Fptr = LocalPtr;
        break;
    case EX_INT1:
        INT1_Fptr = LocalPtr;
        break;
    case EX_INT2:
        INT2_Fptr = LocalPtr;
        break;
    }
}

ISR(INT0_vect)
{
    if (INT0_Fptr != NULL)
    {
        INT0_Fptr();
    }
}
ISR(INT1_vect)
{
    if (INT1_Fptr != NULL)
    {
        INT1_Fptr();
    }
}
ISR(INT2_vect)
{
    if (INT2_Fptr != NULL)
    {
        INT2_Fptr();
    }
}
