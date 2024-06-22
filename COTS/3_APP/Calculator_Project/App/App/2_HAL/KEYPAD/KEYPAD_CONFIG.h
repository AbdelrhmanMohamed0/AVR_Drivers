#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


#define ROWS_NUM 4
#define COLS_NUM 6
                         /* C0   C1  C2  C3  */
static u8 KPD_u8Buttons[ROWS_NUM][COLS_NUM] = { {' ','7','8','9','*','/'}, /* Row0 */
						   				 		{'C','4','5','6','-','^'}, /* Row1 */
						   				 		{'>','1','2','3','+','G'}, /* Row2 */
						   				 		{'<','0','.','=','+','M'}  /* Row3 */
                           			   		  };


#define KPD_PORT  DIO_u8PORTC
#define KPD_R0    DIO_u8PIN0
#define KPD_R1    DIO_u8PIN1
#define KPD_R2    DIO_u8PIN2
#define KPD_R3    DIO_u8PIN3

#define KPD_C0    DIO_u8PIN4
#define KPD_C1    DIO_u8PIN5
#define KPD_C2    DIO_u8PIN6
#define KPD_C3    DIO_u8PIN7

#if COLS_NUM == 6
#define KPD_PORT_PLUS  DIO_u8PORTD
#define KPD_C4    DIO_u8PIN0
#define KPD_C5    DIO_u8PIN1
#endif

#endif 
