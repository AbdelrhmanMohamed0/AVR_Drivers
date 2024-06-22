
#include"STD_TYPES.h"
#include"ERROR_STATES.h"
#include"BIT_MATH.h"
#include"Stack.h"
#include"DIO_INTERFACE.h"
#include"LCD_INTERFACE.h"
#include"KEYPAD_INTERFACE.h"
#include "math.h"

void Infix_To_Postfix(u8 *array, Stack *postfix);
void display(ELEMENT_TYPE ch);
int Is_digit(u8 ch);
int Is_unery_operator(u8 op);
int Precedance_element1_is_grater(ELEMENT_TYPE element_1, ELEMENT_TYPE element_2);
f64 Evaluate_Postfix(Stack *postfix);
f64 DO_operation(ELEMENT_TYPE poped_element1, ELEMENT_TYPE poped_element2, ELEMENT_TYPE poped_element);

// Main function
int main(void)
{
	DIO_Enu_Init();
	LCD_enuInit();
	KPD_enu_Init();
	u8 pressed_key;
	u8 array[16]={0};
	u8 count =0;
	while(1){
				LCD_enuSetPosition(1,1);	
		do{
			do{
				KPD_enu_GetPressed(&pressed_key);
			}while(pressed_key==0xff);
			if(pressed_key!=' '&&pressed_key!='M'&&pressed_key!='>'&&pressed_key!='>'
			&&pressed_key!='.'&&pressed_key!='=')
			{
				LCD_enuSendData(pressed_key);
				array[count++]=pressed_key;
				if(count>15){
					count=0;
				}
			}
		}while (pressed_key !='=');
		array[count]='\0';
		ELEMENT_TYPE temp;
		Stack s1, s2;
		stack_init(&s1);
		stack_init(&s2);
		Infix_To_Postfix(array, &s1);
		for (u32 c = size_stack(&s1); c > 0; c--)
		{
			pop_stack(&temp, &s1);
			push_stack(&s2, temp);
		}
		traverse_stack(&s2, &display);
		f64 res = Evaluate_Postfix(&s2);
		LCD_enuSetPosition(2,1);
		LCD_enuSendString("result = ");
		LCD_enuSetPosition(2,11);
		LCD_enuSendNumber(res);
	}
}
void Infix_To_Postfix(u8 *array, Stack *postfix)
{
	Stack check;
	ELEMENT_TYPE top_element, poped_element, element;
	stack_init(&check);
	while (*array)
	{
		ELEMENT_TYPE res ;
		res.f64_element=0;
		if (Is_digit(*array))
		{
			element.u8_element = *array;

						while(Is_digit(element.u8_element))
						{
							res.f64_element = (res.f64_element*(f64)10) + (f64)(poped_element.u8_element - '0');
							array++;
							element.u8_element = *array;
						}
						push_stack(postfix, res);
			//			push_stack(postfix, poped_element);
			//push_stack(postfix, element);
				 if (Is_unery_operator(element.u8_element))
				{
					//element.u8_element = poped_element;
					while (!stack_empty(&check) && Precedance_element1_is_grater(top_element, element))
					{
						pop_stack(&poped_element, &check);
						push_stack(postfix, poped_element);
						stack_top(&check, &top_element);
					}
					push_stack(&check, element);
					stack_top(&check, &top_element);
				}
				else{
					array--;
				}
		}

		array++;
	}
	while (!stack_empty(&check))
	{
		pop_stack(&poped_element, &check);
		push_stack(postfix, poped_element);
	}
}

void display(ELEMENT_TYPE ch)
{
	printf("%c", ch.u8_element);
}
int Is_digit(u8 ch)
{
	return (!(ch <= '0' || ch >= '9'));
}

int Is_unery_operator(u8 op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

int Precedance_element1_is_grater(ELEMENT_TYPE element_1, ELEMENT_TYPE element_2)
{
	if (element_1.u8_element == '^')
	return 1;
	else if (element_1.u8_element == '*' || element_1.u8_element == '/')
	{
		return (!(element_2.u8_element == '^'));
	}
	else
	{
		return (!(element_2.u8_element == '^' || element_2.u8_element == '*' || element_2.u8_element == '/'));
	}
}

f64 Evaluate_Postfix(Stack *postfix)
{
	Stack temp;
	stack_init(&temp);
	ELEMENT_TYPE poped_element;
	while (!stack_empty(postfix))
	{
		pop_stack(&poped_element, postfix);
		if (!Is_unery_operator(poped_element.u8_element))
		{
			ELEMENT_TYPE res;
			res.f64_element = poped_element.f64_element ;
			push_stack(&temp, res);
		}
		else
		{
			ELEMENT_TYPE poped_element1, poped_element2, result;
			pop_stack(&poped_element2, &temp);
			pop_stack(&poped_element1, &temp);
			result.f64_element = DO_operation(poped_element1, poped_element2, poped_element);
			push_stack(&temp, result);
		}
	}
	pop_stack(&poped_element, &temp);
	return poped_element.f64_element;
}
f64 DO_operation(ELEMENT_TYPE poped_element1, ELEMENT_TYPE poped_element2, ELEMENT_TYPE poped_element)
{
	switch (poped_element.u8_element)
	{
		case '+':
		return (poped_element1.f64_element + poped_element2.f64_element);
		break;
		case '-':
		return (poped_element1.f64_element - poped_element2.f64_element);
		break;
		case '*':
		return (poped_element1.f64_element * poped_element2.f64_element);
		break;
		case '/':
		return (poped_element1.f64_element / poped_element2.f64_element);
		break;
		case '^':
		return (pow(poped_element1.f64_element, poped_element2.f64_element));
		break;
		default:
		break;
	}
}


