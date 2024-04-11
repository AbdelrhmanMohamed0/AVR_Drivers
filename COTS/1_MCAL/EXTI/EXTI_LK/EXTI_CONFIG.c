#include "STD_TYPES.h"
#include "ERROR_STATES.h"
#include "EXTI_PRIVATE.h"
#include "Global.h"
#include "EXTI_CONFIG.h"


// ExInterruptSource_type can be EX_INT0,EX_INT1,EX_INT2
// EXTI_u8State can be ACTIVE,DEACTIVE
// TriggerEdge_type can be LOW_LEVEL,ANY_LOGIC_CHANGE,FALLING_EDGE,RISING_EDGE

EXTI_t EXTI_AstrEXTIConfig[3] =
    {
        {EX_INT0 ,ACTIVE, FALLING_EDGE},
        {EX_INT1 ,ACTIVE, ANY_LOGIC_CHANGE},
        {EX_INT2 ,ACTIVE, FALLING_EDGE}
	};
