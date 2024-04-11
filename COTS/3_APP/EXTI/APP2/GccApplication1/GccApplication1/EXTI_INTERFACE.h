#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

ES_t EXTI_enuInit(EXTI_t *Copy_pstrEXTIConfig);
ES_t EXTI_enuSenseMode(ExInterruptSource_type Copy_enuEXTI_ID, TriggerEdge_type Copy_enuSenseLevel);
ES_t EXTI_enuEnableINT(ExInterruptSource_type Copy_enuEXTI_ID);
ES_t EXTI_enuDisableINT(ExInterruptSource_type Copy_enuEXTI_ID);
void EXI_SetCallBack(ExInterruptSource_type Copy_enuEXTI_ID, void (*LocalPtr)(void));

/*interrupt functions*/
/*
__asm__ __volatile__ ("sei" ::)
sei: This instruction stands for Set Global Interrupt Flag.
When executed, it enables interrupts globally.
In other words, it allows the AVR microcontroller to respond to external interrupts.
The __asm__ __volatile__ part indicates that this is an inline assembly code snippet.
The volatile keyword ensures that the compiler does not optimize away this assembly code.
__asm__ __volatile__ ("cli" ::)
cli: This instruction stands for Clear Global Interrupt Flag.
When executed, it disables interrupts globally. 
This prevents the AVR microcontroller from responding to external interrupts.
Similar to the previous statement, the __asm__ __volatile__ part indicates inline assembly code.
__asm__ __volatile__ ("reti" ::)
reti: This instruction stands for Return from Interrupt. 
It is used at the end of an interrupt service routine (ISR)
to return control to the main program after handling an interrupt.
Again, the __asm__ __volatile__ part indicates inline assembly code.
*/
# define SGI()   __asm__ __volatile__ ("sei" ::)
# define CGI()   __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)

#endif
