
#ifndef TIMERS_SERVICES_H_
#define TIMERS_SERVICES_H_


#include "TIMER_interface.h"

#define SIGNAL_PORT DIO_u8PORTD
#define SIGNAL_PIN  DIO_u8PIN6

#define ICP_FALLING_EDGE                   0
#define ICP_RAISING_EDGE                   1

void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void));
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void));

void PWM_Measure(u32* Pfreq,u8* Pduty);
void PWM_Measure2(u32* Pfreq,u8* Pduty);
static void Func_ICU(void);


#endif /* TIMERS_SERVICES_H_ */