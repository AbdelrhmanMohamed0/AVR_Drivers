#include "ultrasonic.h"

static volatile u16 t1,t2,flag=0,c=0;

void ULTRASONIC_Init(void)
{
	/****you can use timer in another mode except modes using ICR as top put take care dont reset timer****/
	// TIMER1_NORMAL_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED
	TIMER1_voidInit();
	TIMER_u8SetCallBack(Func_OVF,TIMER1_OVF_VECTOR_ID);
	TIMER_u8SetCallBack(Func_ICU,TIMER1_ICU_VECTOR_ID);
}

u8 ULTRASONIC_GetDistance(ULTRASONIC_type ultrasonic_pin)
{
	u8 distance;
	u16 time;
	//TCNT1=0;
	c=0;
	flag=0;
		DIO_Enu_SetPinValue(ultrasonic_pin,DIO_u8HIGH);
		_delay_us(10);
		DIO_Enu_SetPinValue(ultrasonic_pin,DIO_u8LOW);
		Timer1_InputCaptureEdge(ICP_RAISING_EDGE);
		TIMER_voidICUEnableInterrupt();
		Timer1_OVF_InterruptEnable();
	while (flag<2);
	time=t2-t1+((u32)c*65535);
	distance=time/58;
	TIMER_voidICUDisableInterrupt();
	return distance;
	
}
void ULTRASONIC_Start(ULTRASONIC_type ultrasonic_pin)
{
		if(flag==0)
		{
			DIO_Enu_SetPinValue(ultrasonic_pin,DIO_u8HIGH);
			_delay_us(10);
			DIO_Enu_SetPinValue(ultrasonic_pin,DIO_u8LOW);
			Timer1_InputCaptureEdge(ICP_RAISING_EDGE);
			TIMER_voidICUEnableInterrupt();
			Timer1_OVF_InterruptEnable();
		}
	
}
u8 ULTRASONIC_GetDistanceNoBlock(u8*Pdistance)
{
	u8 distance;
	u16 time;
	if (flag==2)
	{
		time=t2-t1+((u32)c*65535);
		distance=time/58;
		*Pdistance=distance;
		Timer1_OVF_InterruptEnable();
		flag=0;
		return 1;
	}
	return 0;
}
u8 ULTRASONIC_GetDistance2(ULTRASONIC_type ultrasonic_pin)
{
	u8 distance,res;
	u16 time;
		DIO_Enu_SetPinValue(ultrasonic_pin,DIO_u8HIGH);
		_delay_us(10);
		DIO_Enu_SetPinValue(ultrasonic_pin,DIO_u8LOW);
		do{
		DIO_Enu_GetPinValue(DIO_u8PORTD,DIO_u8PIN6,&res);
		}while(res==0);
		TIMER1_voidSetPreload(0);
		do{
		DIO_Enu_GetPinValue(DIO_u8PORTD,DIO_u8PIN6,&res);
		}while(res==1);
	time=TIMER1_u16GetTimerCounterValue();
	time+=((u32)c*65535);
	distance=time/58;
	return distance;
	
}

static void Func_ICU(void)
{
	if(flag==0)
	{
		c=0;
		t1=TIMER_u16GetICR();
		flag=1;
		TIMER_voidICUSetTriggerEdge(ICP_FALLING_EDGE);
	}
	else if (flag==1)
	{
		t2=TIMER_u16GetICR1();
		flag=2;
		Timer1_InputCaptureEdge(ICP_RAISING_EDGE);
		Timer1_OVF_InterruptDisable();
		TIMER_voidICUDisableInterrupt();
	}
}

static void Func_OVF(void)
{
	c++;
}