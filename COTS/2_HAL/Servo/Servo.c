#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "Servo.h"


void SERVO_Init(void)
{
	TIMER1_voidInit();
	TIMER1_voidSetICR1((u16)19999);
	TIMER1_voidSetCTCA((u16)599);
}
void SERVO_SetAngle(u8 angle)
{
	TIMER1_voidSetCTCA((((u32)angle * 2000) / 180)  + 600 - 1) ; 
	
}