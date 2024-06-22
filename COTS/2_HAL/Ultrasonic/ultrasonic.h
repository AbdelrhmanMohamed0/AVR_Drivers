#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 8000000
#define ICP_FALLING_EDGE                   0
#define ICP_RAISING_EDGE                   1

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "TIMER_interface.h"
#include <util/delay.h>




typedef enum{
	ULTRASONIC_1=DIO_u8PIN0,
	ULTRASONIC_2=DIO_u8PIN1,
	ULTRASONIC_3=DIO_u8PIN2,
	ULTRASONIC_4=DIO_u8PIN3
	}ULTRASONIC_type;

void ULTRASONIC_Init(void);
u8 ULTRASONIC_GetDistance(ULTRASONIC_type ultrasonic_pin);
u8 ULTRASONIC_GetDistance2(ULTRASONIC_type ultrasonic_pin);
void ULTRASONIC_Start(ULTRASONIC_type ultrasonic_pin);
u8 ULTRASONIC_GetDistanceNoBlock(u8*Pdistance);

static void Func_ICU(void);
static void Func_OVF(void);
#endif /* ULTRASONIC_H_ */