#include "..\4_LIB\STD_TYPES.h"
#include "..\4_LIB\ERROR_STATES.h"
#include "..\4_LIB\BIT_MATH.h"
#include "..\5_SERVICE\STACK\Stack.h"
#include "..\1_MCAL\DIO\DIO_INTERFACE.h"
#include "..\2_HAL\LCD\LCD_INTERFACE.h"
#include "..\2_HAL\KEYPAD\KEYPAD_INTERFACE.h"
#include <math.h>
#include <string.h>
#define F_CPU 8000000
#include <util/delay.h>
void Infix_To_Postfix(u8 *array, Stack *postfix);
void display(ELEMENT_TYPE ch);
int Is_digit(u8 ch);
int Is_unery_operator(u8 op);
int Precedance_element1_is_grater(ELEMENT_TYPE element_1, ELEMENT_TYPE element_2);
f64 Evaluate_Postfix(Stack *postfix);
f64 DO_operation(ELEMENT_TYPE poped_element1, ELEMENT_TYPE poped_element2, ELEMENT_TYPE poped_element);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
u8 Mode1(void);
void decimal_to_binary(void);
void decimal_to_decimal(void);
void decimal_to_HEX(void);
void binary_to_decimal(void);
void binary_to_binary(void);
void binary_to_HEX(void);
void HEX_to_decimal(void);
void HEX_to_binary(void);
void HEX_to_HEX(void);
void hex_to_binary(char hex_char, char *binary_string);
void Mode2(void);
void Mode3(void);