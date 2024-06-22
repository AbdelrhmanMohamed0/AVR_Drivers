#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "Timers_Services.h"


volatile u16 t1,t2,t3,flag=0;

/******************************************Set Interrupt Time******************************************************/

void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void))
{
	TIMER1_voidInit();
	TIMER1_voidSetCTCA((time*1000)-1);
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();	
}

void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void))
{
	TIMER1_voidInit();
	TIMER1_voidSetCTCA((time)-1);
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}

/**********************************************Measure PWM*********************************************************/
void PWM_Measure2(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	u8 signal;
	TIMER1_voidSetPreload(0);
	do{
	DIO_Enu_GetPinValue(SIGNAL_PORT,SIGNAL_PIN,&signal);
	}while(signal!=0);
	do{
	DIO_Enu_GetPinValue(SIGNAL_PORT,SIGNAL_PIN,&signal);
	}while(signal!=1);
	TIMER1_voidSetPreload(0);
	do{
	DIO_Enu_GetPinValue(SIGNAL_PORT,SIGNAL_PIN,&signal);
	}while(signal==1);
	Ton=TIMER1_u16GetTimerCounterValue();
	TIMER1_voidSetPreload(0);
	do{
	DIO_Enu_GetPinValue(SIGNAL_PORT,SIGNAL_PIN,&signal);
	}while(signal!=1);
	Toff=TIMER1_u16GetTimerCounterValue();
	*Pduty=((u32)Ton*100)/(Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);
}


void PWM_Measure(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	TIMER1_voidSetPreload(0);
	TIMER_u8SetCallBack(Func_ICU,TIMER1_ICU_VECTOR_ID);
	Timer1_InputCaptureEdge(ICP_RAISING_EDGE);
	TIMER_voidICUEnableInterrupt();
	flag=0;
	while(flag<3);
	Ton=t2-t1;
	Toff=t3-t2;
	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);

}

static void Func_ICU(void)
{
	if (flag==0)
	{
		t1=TIMER_u16GetICR1();
		TIMER_voidICUSetTriggerEdge(ICP_FALLING_EDGE);
		flag=1;
	}
	else if (flag==1)
	{
		t2=TIMER_u16GetICR1();
		Timer1_InputCaptureEdge(ICP_RAISING_EDGE);
		flag=2;		
	}
	else if (flag==2)
	{
		t3=TIMER_u16GetICR1();
		TIMER_voidICUDisableInterrupt();
		flag=3;
	}	
}