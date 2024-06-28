#include "APP.h"
u8 array_num[16], flag1 = 0;
// A utility function to reverse a string
void reverse(char *str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[]. d is the number
// of digits required in the output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If the number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char *res, int afterpoint)
{
	if (n < 0)
		n *= -1;
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// Convert integer part to string
	int i = intToStr(ipart, res, 0);

	// Check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.'; // Add dot

		// Get the value of fraction part up to given number of points after dot.
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

void Infix_To_Postfix(u8 *array, Stack *postfix)
{
	Stack check;
	ELEMENT_TYPE top_element, poped_element, element;
	u8 flag1 = 0, flag2 = 0;
	stack_init(&check);
	if (array[0] == '-')
	{
		flag1 = 1;
		array++;
	}
	while (*array)
	{
		if (Is_digit(*array) || (*array == '.'))
		{
			element.f64_element = atof(array);
			if (flag1 == 1)
			{
				element.f64_element *= -1;
				flag1 = 0;
			}
			if (flag2 == 1)
			{
				element.f64_element *= -1;
				flag2 = 0;
			}
			while (Is_digit(*array) || (*array == '.'))
			{
				array++;
			}
			array--;
			push_stack(postfix, element);
		}
		else if (Is_unery_operator(*array))
		{
			element.u8_element = *array;
			stack_top(&check, &top_element);
			if ((Is_unery_operator(*(array - 1))) && element.u8_element == '+')
			{
				array++;
				continue;
			}
			else if ((Is_unery_operator(*(array - 1))) && element.u8_element == '-')
			{
				array++;
				flag2 = 1;
				continue;
			}
			while (!stack_empty(&check) && Precedance_element1_is_grater(top_element, element))
			{
				pop_stack(&poped_element, &check);
				push_stack(postfix, poped_element);
				stack_top(&check, &top_element);
			}
			push_stack(&check, element);
			stack_top(&check, &top_element);
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
	printf("%f  ", ch.f64_element);
}
int Is_digit(u8 ch)
{
	return (!(ch < '0' || ch > '9'));
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
			push_stack(&temp, poped_element);
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
		return (powf(poped_element1.f64_element, poped_element2.f64_element));
		break;
	default:
		break;
	}
}

u8 Mode1(void)
{
	u8 pressed_key, count = 0, *ptr1 = NULL, flag = 0;
	u8 array[16] = {0};
	u8 con[20];
	f64 res = 0;
	ELEMENT_TYPE temp;
	Stack s1, s2;
	stack_init(&s1);
	stack_init(&s2);
	if (flag1 == 1)
	{
		LCD_enuClearScreen();
		flag1 = 0;
	}
	LCD_enuSendCommand(lcd_DisplayOn_CursorOn);
	LCD_enuSetPosition(1, 1);
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while (pressed_key == 0xff);
		if (pressed_key != ' ' && pressed_key != 'M' && pressed_key != '>' && pressed_key != '<' && pressed_key != '=' && pressed_key != 'G' && pressed_key != 'C')
		{
			if ((count == 0) && (pressed_key == '+' || pressed_key == '-' ||
								 pressed_key == '*' || pressed_key == '/' || pressed_key == '^'))
			{
				LCD_enuClearScreen();
				count = strlen(con);
				for (u8 i = 0; i < count; i++)
					array[i] = con[i];
				LCD_enuSendString(con);
			}
			else if ((count == 0))
			{
				LCD_enuClearScreen();
				for (u8 i = 0; i < 16; i++)
					array[i] = 0;
				res = 0;
			}
			LCD_enuSendData(pressed_key);
			array[count++] = pressed_key;
			flag = 0;
			if (count > 15)
			{
				count = 0;
			}
		}
		else if (pressed_key == ' ')
		{
			LCD_enuClearScreen();
			clear_stack(&s1);
			clear_stack(&s2);
			res = 0;
			count = 0;
			for (u8 i = 0; i < 16; i++)
				array[i] = 0;
		}
		else if (pressed_key == '>')
		{
			if (array[count + 1] != 0 && flag == 1)
			{
				count++;
				LCD_enuSetPosition(1, count + 1);
			}
			else if ((array[count + 1] == 0 && flag == 1))
			{
				if (array[count] != 0)
				{
					count++;
					LCD_enuSetPosition(1, count + 1);
				}
			}
		}
		else if (pressed_key == '<')
		{
			if (count > 0)
			{
				count--;
				LCD_enuSetPosition(1, count + 1);
			}
			flag = 1;
		}
		else if (pressed_key == 'C')
		{

			if (count > 0)
			{
				count--;
				if (array[count + 1] == '\0')
				{
					LCD_enuSetPosition(1, count + 1);
					LCD_enuSendData('\0');
					array[count] = '\0';
					LCD_enuSetPosition(1, count + 1);
				}
				else
				{
					count++;
					LCD_enuSendData('\0');
					array[count--] = '\0';
					ptr1 = strchr(array, '\0');
					strcat(array, ptr1 + 1);
					LCD_enuClearScreen();
					LCD_enuSendString(array);
					LCD_enuSetPosition(1, count + 1);
				}
			}
		}
		else if (pressed_key == 'M')
		{
			return 1;
		}
	} while (pressed_key != '=');
	count = strlen(array);
	array[count] = '\0';
	if (count == 0)
		return 0;
	if (strlen(array) == 1)
	{
		if (array[0] == '*' || array[0] == '/' || array[0] == '^' || array[0] == '-' || array[0] == '+')
		{
			LCD_enuClearScreen();
			LCD_enuSetPosition(1, 1);
			LCD_enuSendString("SYNTAX ERROR");
			LCD_enuSetPosition(2, 1);
			LCD_enuSendString("PRESS AC");
			do
			{
				do
				{
					KPD_enu_GetPressed(&pressed_key);
				} while (pressed_key == 0xff);
			} while (pressed_key != ' ');
			LCD_enuClearScreen();
			return 0;
		}
	}
	for (u8 i = 0; i < strlen(array) - 1; i++)
	{
		if ((array[i] == '*' || array[i] == '/' || array[i] == '^') && (array[i + 1] == '*' || array[i + 1] == '/' || array[i + 1] == '^'))
		{
			LCD_enuClearScreen();
			LCD_enuSetPosition(1, 1);
			LCD_enuSendString("SYNTAX ERROR");
			LCD_enuSetPosition(2, 1);
			LCD_enuSendString("PRESS AC");
			do
			{
				do
				{
					KPD_enu_GetPressed(&pressed_key);
				} while (pressed_key == 0xff);
			} while (pressed_key != ' ');
			LCD_enuClearScreen();
			return 0;
		}
		else if (array[i] == '.')
		{

			ptr1 = strchr(array + i + 1, '.');
			if (ptr1 != NULL)
			{
				u8 j = (ptr1 - (array + i) - 1), f1 = 0;
				while (j)
				{
					if (Is_digit(array[i + j]))
						f1 = 1;
					else if (Is_unery_operator(array[i + j]))
					{
						f1 = 0;
						break;
					}
					j--;
				}
				if (f1 == 1)
				{
					LCD_enuClearScreen();
					LCD_enuSetPosition(1, 1);
					LCD_enuSendString("SYNTAX ERROR");
					LCD_enuSetPosition(2, 1);
					LCD_enuSendString("PRESS AC");
					do
					{
						do
						{
							KPD_enu_GetPressed(&pressed_key);
						} while (pressed_key == 0xff);
					} while (pressed_key != ' ');
					LCD_enuClearScreen();
					return 0;
				}
			}
		}
		else if (array[count - 1] == '*' || array[count - 1] == '/' || array[count - 1] == '^' || array[count - 1] == '-' || array[count - 1] == '+')
		{
			LCD_enuClearScreen();
			LCD_enuSetPosition(1, 1);
			LCD_enuSendString("SYNTAX ERROR");
			LCD_enuSetPosition(2, 1);
			LCD_enuSendString("PRESS AC");
			do
			{
				do
				{
					KPD_enu_GetPressed(&pressed_key);
				} while (pressed_key == 0xff);
			} while (pressed_key != ' ');
			LCD_enuClearScreen();
			return 0;
		}
		else if ((array[i] == '/') && (array[i + 1] == '0'))
		{
			LCD_enuClearScreen();
			LCD_enuSetPosition(1, 1);
			LCD_enuSendString("MATH ERROR");
			LCD_enuSetPosition(2, 1);
			LCD_enuSendString("PRESS AC");
			do
			{
				do
				{
					KPD_enu_GetPressed(&pressed_key);
				} while (pressed_key == 0xff);
			} while (pressed_key != ' ');
			LCD_enuClearScreen();
			return 0;
		}
	}
	for (s8 i = 0; i <= count - 5; i++)
	{
		if ((Is_digit(array[i]) && Is_digit(array[i + 1]) && Is_digit(array[i + 2]) && Is_digit(array[i + 3]) && Is_digit(array[i + 4]) && (array[i] > '5')))
		{
			LCD_enuClearScreen();
			LCD_enuSetPosition(1, 1);
			LCD_enuSendString("    OVERFLOW");
			LCD_enuSetPosition(2, 1);
			LCD_enuSendString("PRESS AC");
			do
			{
				do
				{
					KPD_enu_GetPressed(&pressed_key);
				} while (pressed_key == 0xff);
			} while (pressed_key != ' ');
			LCD_enuClearScreen();
			return 0;
		}
	}
	Infix_To_Postfix(array, &s1);
	for (u32 c = size_stack(&s1); c > 0; c--)
	{
		pop_stack(&temp, &s1);
		push_stack(&s2, temp);
	}
	traverse_stack(&s2, &display);
	res = Evaluate_Postfix(&s2);
	if (res < 0)
	{
		con[0] = '-';
		ftoa(res, con + 1, 4);
	}
	else
		ftoa(res, con, 4);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("result= ");
	LCD_enuSetPosition(2, 9);
	LCD_enuSendString(con);
	count = 0;
	clear_stack(&s1);
	clear_stack(&s2);
	return 1;
}
void Mode2(void)
{
	u8 pressed_key, convert_from, convert_to;
	LCD_enuClearScreen();
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("convert from : ");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("1D   2B   3H ");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != '1' && pressed_key != '2' && pressed_key != '3');
	convert_from = pressed_key;
	LCD_enuClearScreen();
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("convert to : ");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("1D   2B   3H");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != '1' && pressed_key != '2' && pressed_key != '3');
	convert_to = pressed_key;
	for (int i = 0; i < 999; i++)
		;
	switch (convert_from)
	{
	case '1':
		switch (convert_to)
		{
		case '1':
			decimal_to_decimal();
			break;
		case '2':
			decimal_to_binary();
			break;
		case '3':
			decimal_to_HEX();
			break;
		}
		break;
	case '2':
		switch (convert_to)
		{
		case '1':
			binary_to_decimal();
			break;
		case '2':
			binary_to_binary();
			break;
		case '3':
			binary_to_HEX();
			break;
		}
		break;
	case '3':
	{
		switch (convert_to)
		{
		case '1':
			HEX_to_decimal();
			break;
		case '2':
			HEX_to_binary();
			break;
		case '3':
			HEX_to_HEX();
			break;
		}
	}
	break;
	}
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("C- mode continue ");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("M- change mode ");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
	flag1 = 1;
}

void decimal_to_decimal(void)
{
	u8 pressed_key, i = 0;
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key < '0' || pressed_key > '9') && pressed_key != '=');
		if (pressed_key == '=')
			continue;
		LCD_enuSendData(pressed_key);
		array_num[i++] = pressed_key;
	} while (pressed_key != '=');
	array_num[i] = '\0';
	LCD_enuClearScreen();
	LCD_enuSendString(array_num);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void decimal_to_binary(void)
{
	u8 pressed_key, i = 0;
	u32 decimal_number = 0, index = 0;
	u8 binary_number[32] = {0}; // Assuming a maximum of 32 bits for simplicity

	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key < '0' || pressed_key > '9') && pressed_key != '=');
		if (pressed_key == '=')
			continue;
		LCD_enuSendData(pressed_key);
		array_num[i++] = pressed_key;
	} while (pressed_key != '=');
	array_num[i] = '\0';
	LCD_enuClearScreen();
	decimal_number = atoi(array_num);
	if (decimal_number == 0)
	{
		LCD_enuSendNumber(0);
		return;
	}
	while (decimal_number > 0)
	{
		binary_number[index] = decimal_number % 2;
		decimal_number = decimal_number / 2;
		index++;
	}

	// Print binary number in reverse order
	for (int i = index - 1; i >= 0; i--)
	{
		LCD_enuSendNumber(binary_number[i]);
	}
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void decimal_to_HEX(void)
{
	u8 pressed_key, i = 0, flag = 0;
	u32 decimal_number = 0, index = 0;
	u8 hex_number[32] = {0}; // Assuming a maximum of 32 bits for simplicity
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key < '0' || pressed_key > '9') && pressed_key != '=');
		if (pressed_key == '=')
			continue;
		LCD_enuSendData(pressed_key);
		array_num[i++] = pressed_key;
	} while (pressed_key != '=');
	array_num[i] = '\0';
	LCD_enuClearScreen();
	decimal_number = atoi(array_num);
	if (decimal_number == 0)
	{
		LCD_enuSendNumber(0);
		return;
	}
	while (decimal_number > 0)
	{
		u32 rem = decimal_number % 16;
		if (rem < 10)
			hex_number[index] = rem + '0';
		else
			hex_number[index] = rem - 10 + 'A';
		decimal_number = decimal_number / 16;
		index++;
	}

	// Print hex number in reverse order
	for (int i = index - 1; i >= 0; i--)
	{
		LCD_enuSendData(hex_number[i]);
	}
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void binary_to_binary(void)
{
	u8 pressed_key, i = 0;
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key != '0' && pressed_key != '1') && pressed_key != '=');
		if (pressed_key == '0')
			LCD_enuSendData('0');
		else if (pressed_key == '1')
			LCD_enuSendData('1');
		array_num[i++] = pressed_key;
	} while (pressed_key != '=');
	array_num[--i] = '\0';
	LCD_enuClearScreen();
	LCD_enuSendString(array_num);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void binary_to_decimal(void)
{
	u8 pressed_key, j = 0;
	u32 decimal_number = 0;
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key != '0' && pressed_key != '1') && pressed_key != '=');
		LCD_enuSendData(pressed_key);
		array_num[j++] = pressed_key;
	} while (pressed_key != '=');
	array_num[--j] = '\0';
	for (int i = 0; i < j; i++)
	{
		if (array_num[j - i - 1] == '1')
		{
			decimal_number += (1 << i);
		}
	}
	LCD_enuClearScreen();
	LCD_enuSendNumber(decimal_number);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void binary_to_HEX(void)
{
	u8 pressed_key, j = 0;
	u32 decimal_number = 0, index = 0;
	u8 hex_number[32] = {0}; // Assuming a maximum of 32 bits for simplicity

	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key != '0' && pressed_key != '1') && pressed_key != '=');
		LCD_enuSendData(pressed_key);
		array_num[j++] = pressed_key;
	} while (pressed_key != '=');
	array_num[--j] = '\0';
	for (int i = 0; i < j; i++)
	{
		if (array_num[j - i - 1] == '1')
		{
			decimal_number += (1 << i);
		}
	}
	while (decimal_number > 0)
	{
		u32 rem = decimal_number % 16;
		if (rem < 10)
			hex_number[index] = rem + '0';
		else
			hex_number[index] = rem - 10 + 'A';
		decimal_number = decimal_number / 16;
		index++;
	}
	LCD_enuClearScreen();
	// Print hex number in reverse order
	for (int i = index - 1; i >= 0; i--)
	{
		LCD_enuSendData(hex_number[i]);
	}
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void HEX_to_HEX(void)
{
	u8 pressed_key, i = 0, flag = 0;
	LCD_enuClearScreen();
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("G- Before NUM to");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("Write Alphabet");
	_delay_ms(500);
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key < '1' || pressed_key > '9') && pressed_key != '=' && pressed_key != 'G');
		if (pressed_key == 'G')
		{
			flag = 1;
			continue;
		}
		if (pressed_key == '=')
			continue;
		if (flag == 1)
		{
			LCD_enuSendData(pressed_key + 16);
			array_num[i++] = pressed_key + 16;
			flag = 0;
		}
		else
		{
			LCD_enuSendData(pressed_key);
			array_num[i++] = pressed_key;
		}
	} while (pressed_key != '=');
	array_num[i] = '\0';
	LCD_enuClearScreen();
	LCD_enuSendString(array_num);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}

void HEX_to_decimal(void)
{

	u8 pressed_key, j = 0, flag = 0;
	u32 decimal_number = 0;
	LCD_enuClearScreen();
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("G- Before NUM to");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("Write Alphabet");
	_delay_ms(500);
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key < '1' || pressed_key > '9') && pressed_key != '=' && pressed_key != 'G');
		if (pressed_key == 'G')
		{
			flag = 1;
			continue;
		}
		if (pressed_key == '=')
			continue;
		if (flag == 1)
		{
			LCD_enuSendData(pressed_key + 16);
			array_num[j++] = pressed_key + 16;
			flag = 0;
		}
		else
		{
			LCD_enuSendData(pressed_key);
			array_num[j++] = pressed_key;
		}
	} while (pressed_key != '=');
	array_num[j] = '\0';
	LCD_enuClearScreen();
	for (int i = 0; i < j; i++)
	{
		u8 digit = array_num[j - i - 1];
		if (Is_digit(digit))
		{
			decimal_number += (digit - '0') * (1 << (4 * i));
		}
		else if (isxdigit(digit))
		{
			decimal_number += (digit - 'A' + 10) * (1 << (4 * i));
		}
	}
	LCD_enuSendNumber(decimal_number);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}
void HEX_to_binary(void)
{
	u8 pressed_key, j = 0, flag = 0;
	u8 binary_number[128] = {0}; // Ensure enough space for binary output (4 bits per hex digit)
	u8 binary_string[5] = {0};	 // Temporary storage for binary conversion of a single hex digit
	LCD_enuClearScreen();
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("G- Before NUM to");
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("Write Alphabet");
	_delay_ms(500);
	LCD_enuClearScreen();
	do
	{
		do
		{
			KPD_enu_GetPressed(&pressed_key);
		} while ((pressed_key < '1' || pressed_key > '9') && pressed_key != '=' && pressed_key != 'G');
		if (pressed_key == 'G')
		{
			flag = 1;
			continue;
		}
		if (pressed_key == '=')
			continue;
		if (flag == 1)
		{
			LCD_enuSendData(pressed_key + 16);
			array_num[j++] = pressed_key + 16;
			flag = 0;
		}
		else
		{
			LCD_enuSendData(pressed_key);
			array_num[j++] = pressed_key;
		}
	} while (pressed_key != '=');
	array_num[j] = '\0';
	LCD_enuClearScreen();
	for (int i = 0; i < j; i++)
	{
		hex_to_binary(array_num[i], binary_string);
		strcat(binary_number, binary_string);
	}
	LCD_enuSendString(binary_number);
	LCD_enuSetPosition(2, 1);
	LCD_enuSendString("C-Finish read");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key != 'C' && pressed_key != 'M');
}
void hex_to_binary(char hex_char, char *binary_string)
{
	switch (toupper(hex_char))
	{
	case '0':
		strcpy(binary_string, "0000");
		break;
	case '1':
		strcpy(binary_string, "0001");
		break;
	case '2':
		strcpy(binary_string, "0010");
		break;
	case '3':
		strcpy(binary_string, "0011");
		break;
	case '4':
		strcpy(binary_string, "0100");
		break;
	case '5':
		strcpy(binary_string, "0101");
		break;
	case '6':
		strcpy(binary_string, "0110");
		break;
	case '7':
		strcpy(binary_string, "0111");
		break;
	case '8':
		strcpy(binary_string, "1000");
		break;
	case '9':
		strcpy(binary_string, "1001");
		break;
	case 'A':
		strcpy(binary_string, "1010");
		break;
	case 'B':
		strcpy(binary_string, "1011");
		break;
	case 'C':
		strcpy(binary_string, "1100");
		break;
	case 'D':
		strcpy(binary_string, "1101");
		break;
	case 'E':
		strcpy(binary_string, "1110");
		break;
	case 'F':
		strcpy(binary_string, "1111");
		break;
	default:
		strcpy(binary_string, "");
		break; // Handle invalid input
	}
}

void Mode3(void)
{
	// make game on lcd and keypad
	u8 pressed_key;
	LCD_enuClearScreen();
	LCD_enuSetPosition(1, 1);
	LCD_enuSendString("Game mode ");
	do
	{
		KPD_enu_GetPressed(&pressed_key);
	} while (pressed_key == 0xFF);
	flag1 = 1;
}
