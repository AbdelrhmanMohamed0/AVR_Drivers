#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


/*External Interrupt */
#define MCUCSR   (*(v_u8*)0x54)
#define ISC2 6

#define MCUCR   (*(v_u8*)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR     (*(v_u8*)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR    (*(v_u8*)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5


/* Interrupt vectors */
/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect		__vector_4
/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect			__vector_5
/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect		__vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect		__vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect		__vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			__vector_9
/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect		__vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			__vector_11
/* Serial Transfer Complete */
#define SPI_STC_vect			__vector_12
/* USART, Rx Complete */
#define USART_RXC_vect			__vector_13
/* USART Data Register Empty */
#define USART_UDRE_vect			__vector_14
/* USART, Tx Complete */
#define USART_TXC_vect			__vector_15
/* ADC Conversion Complete */
#define ADC_vect			   __vector_16
/* EEPROM Ready */
#define EE_RDY_vect			   __vector_17
/* Analog Comparator */
#define ANA_COMP_vect			__vector_18
/* 2-wire Serial Interface */
#define TWI_vect			    __vector_19
/* Store Program Memory Ready */
#define SPM_RDY_vect			__vector_20

/*
__attribute__((interrupt))
This attribute is used to define an ISR (Interrupt Service Routine).
When applied to a function, it tells the compiler that the function is an ISR.
For example:
void __attribute__((interrupt)) TIMER1_COMPA_vect(void) {
    // ISR code here
}
In this case, TIMER1_COMPA_vect is an ISR for the Timer 1 Compare A interrupt.
__attribute__((naked))
This attribute is used to create a “naked” function.
A naked function does not have prologue or epilogue code (no stack setup or cleanup).
It’s often used for low-level assembly routines where you need precise control over the function’s behavior.
*/
#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))

/*
__attribute__ ((signal))__VA_ARGS__ ;
This appears to be incomplete or incorrect.
The __VA_ARGS__ is typically used in macros to represent variable arguments,
but it doesn’t make sense in this context.
If you have more context or the complete statement, I can provide a more accurate explanation.
*/
#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)


#endif
