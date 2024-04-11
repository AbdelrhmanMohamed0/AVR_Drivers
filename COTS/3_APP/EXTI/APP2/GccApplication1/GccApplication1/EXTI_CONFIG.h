#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

typedef struct EXTI_CONFIG
{
    ExInterruptSource_type EXTI_NUM;
    u8 EXTI_u8State;
    TriggerEdge_type EXTI_enuSenceLevel;

} EXTI_t;


#endif
