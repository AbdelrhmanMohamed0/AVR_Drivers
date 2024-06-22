#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "DCMOTOR_INTERFACE.h"

ES_t DCMOTOR_uint8Control(DCMOTOR_CONFIG *DcMotor, u8 Copy_u8State)
{
	ES_t Local_u8ErrorState = ES_OK;

	switch (Copy_u8State)
	{
	case DCMOTOR_CW:
		DIO_Enu_SetPinValue(DcMotor->Copy_u8DcMotorPort, DcMotor->Copy_u8DcMotorPinA, DIO_u8LOW);
		DIO_Enu_SetPinValue(DcMotor->Copy_u8DcMotorPort, DcMotor->Copy_u8DcMotorPinB, DIO_u8HIGH);
		break;
	case DCMOTOR_CCW:
		DIO_Enu_SetPinValue(DcMotor->Copy_u8DcMotorPort, DcMotor->Copy_u8DcMotorPinB, DIO_u8LOW);
		DIO_Enu_SetPinValue(DcMotor->Copy_u8DcMotorPort, DcMotor->Copy_u8DcMotorPinA, DIO_u8HIGH);
		break;
	case DCMOTOR_STOP:
		DIO_Enu_SetPinValue(DcMotor->Copy_u8DcMotorPort, DcMotor->Copy_u8DcMotorPinA, DIO_u8LOW);
		DIO_Enu_SetPinValue(DcMotor->Copy_u8DcMotorPort, DcMotor->Copy_u8DcMotorPinB, DIO_u8LOW);
		break;
	default:
		Local_u8ErrorState = ES_NOT_OK;
	}

	return Local_u8ErrorState;
}
