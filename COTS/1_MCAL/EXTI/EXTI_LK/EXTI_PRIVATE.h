#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/*External Interrupt */
#define MCUCSR (*(v_u8 *)0x54)
#define ISC2 6

#define MCUCR (*(v_u8 *)0x55)
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define GICR (*(v_u8 *)0x5B)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR (*(v_u8 *)0x5A)
#define INTF1 7
#define INTF0 6
#define INTF2 5

/* Interrupt vectors */

/* External Interrupt Request 0 */
#define INT0_vect __vector_1
/* External Interrupt Request 1 */
#define INT1_vect __vector_2
/* External Interrupt Request 2 */
#define INT2_vect __vector_3


#define ISR_NOBLOCK __attribute__((interrupt))
#define ISR_NAKED __attribute__((naked))

#define ISR(vector, ...)                                   \
	void vector(void) __attribute__((signal)) __VA_ARGS__; \
	void vector(void)

#endif
