#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATES.h"
#include "DIO_INTERFACE.h"
#include "LCD_INTERFACE.h"
#include "LCD_PRIVATE.h"
#include "LCD_CONFIG.h"
#define F_CPU 8000000UL
#include <util/delay.h>

ES_t LCD_enuInit(void)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;

#if LCD_MODE == 8

    // 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
    _delay_ms(50);

    // All Pins as OutPut pins
    DIO_Enu_SetPortDirection(LCD_DATA_PORT, DIO_u8PORT_OUTPUT);
    DIO_Enu_SetPinDirection(LCD_CONTROL_PORT, LCD_RS, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_CONTROL_PORT, LCD_RW, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_CONTROL_PORT, LCD_EN, DIO_u8OUTPUT);

    /* Return cursor to the first position on the first line  */
    LCD_enuSendCommand(lcd_Home);
    _delay_ms(1);

    /*FUNCTION SET Command : 2 lines , 5*8 font size */
    LCD_enuSendCommand(EIGHT_BITS); // 8 Bit Mode ==> 0x38
    _delay_ms(1);                   // wait more than 39 Ms

    /* DISPLAY & Cursor (ON / OFF) Control */
    LCD_enuSendCommand(lcd_DisplayOn_CursorOff);
    _delay_ms(1);

    /* DISPLAY CLEAR */
    LCD_enuClearScreen();

    /* ENTRY MODE  SET*/
    LCD_enuSendCommand(lcd_EntryMode);
    _delay_ms(1);

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#elif LCD_MODE == 4

    // 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
    _delay_ms(50);
    DIO_Enu_SetPinDirection(LCD_DATA_PORT, DIO_u8PIN4, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_DATA_PORT, DIO_u8PIN5, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_DATA_PORT, DIO_u8PIN6, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_DATA_PORT, DIO_u8PIN7, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_CONTROL_PORT, LCD_RS, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_CONTROL_PORT, LCD_RW, DIO_u8OUTPUT);
    DIO_Enu_SetPinDirection(LCD_CONTROL_PORT, LCD_EN, DIO_u8OUTPUT);

    /*return home*/
    LCD_enuSendCommand(lcd_Home);
    _delay_ms(30);

    /*FUNCTION SET Command*/
    LCD_enuSendCommand(FOUR_BITS); // 4 Bit Mode
    _delay_ms(1);

    /* DISPLAY & Cursor (ON / OFF) Control */
    LCD_enuSendCommand(lcd_DisplayOn_CursorOff);
    _delay_ms(1);

    /* DISPLAY CLEAR */
    LCD_enuClearScreen();

    /* ENTRY MODE  Set*/
    LCD_enuSendCommand(lcd_EntryMode);
    _delay_ms(1);

#else
    Local_EnuErrorState = ES_NOT_CORRECT_MODE;
#endif

    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;
#if LCD_MODE == 8

    DIO_Enu_SetPortValue(LCD_DATA_PORT, Copy_u8Command);
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RS, DIO_u8LOW);
    // RW always connect to GND to Write
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RW, DIO_u8LOW);
    LCD_voidSendFallingEdge();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif LCD_MODE == 4

    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RS, DIO_u8LOW);
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RW, DIO_u8LOW);
    DIO_Enu_WriteHighNibbles(LCD_DATA_PORT, Copy_u8Command >> 4); // send the most 4 bits of data to high nibbles
    LCD_voidSendFallingEdge();
    DIO_Enu_WriteHighNibbles(LCD_DATA_PORT, Copy_u8Command); // send the least 4 bits of data to high nibbles
    LCD_voidSendFallingEdge();

#endif

    _delay_ms(1);

    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}
ES_t LCD_enuSendData(u8 Copy_u8Data)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;
#if LCD_MODE == 8

    DIO_Enu_SetPortValue(LCD_DATA_PORT, Copy_u8Data);
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RS, DIO_u8HIGH);
    // RW always connect to GND to Write
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RW, DIO_u8LOW);
    LCD_voidSendFallingEdge();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif LCD_MODE == 4

    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RS, DIO_u8HIGH);
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_RW, DIO_u8LOW);
    DIO_Enu_WriteHighNibbles(LCD_DATA_PORT, Copy_u8Data >> 4); // send the most 4 bits of data to high nibbles
    LCD_voidSendFallingEdge();
    DIO_Enu_WriteHighNibbles(LCD_DATA_PORT, Copy_u8Data); // send the least 4 bits of data to high nibbles
    LCD_voidSendFallingEdge();

#endif

    _delay_ms(1);

    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

ES_t LCD_enuSendString(const u8 *Copy_u8ptrString)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;

    u8 LOC_u8Iterator = 0;

    while (Copy_u8ptrString[LOC_u8Iterator] != '\0')
    {

        LCD_enuSendData(Copy_u8ptrString[LOC_u8Iterator]);
        LOC_u8Iterator++;
    }
    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

ES_t LCD_enuSendNumber(u64 Copy_u64Number)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;
    u64 LOC_u64Reversed = 1;

    if (Copy_u64Number == 0)
    {
        LCD_enuSendData('0');
    }

    else
    {

        while (Copy_u64Number != 0)
        {

            LOC_u64Reversed = (LOC_u64Reversed * 10) + (Copy_u64Number % 10);
            Copy_u64Number /= 10;
        }
        while (LOC_u64Reversed != 1)
        {

            LCD_enuSendData((LOC_u64Reversed % 10) + 48);
            LOC_u64Reversed /= 10;
        }
    }

    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

ES_t LCD_enuSetPosition(u8 Copy_u8Row, u8 Copy_u8Col)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;

    u8 LOC_u8data;

    /* In These cases will set at (0,0) ==> if the user enter invalid location */
    if (Copy_u8Row > 2 || Copy_u8Row < 1 || Copy_u8Col > 16 || Copy_u8Col < 1) // check
    {
        LOC_u8data = lcd_SetCursor; // first location
        Local_EnuErrorState = ES_OUT_OF_RANGE;
    }

    else if (Copy_u8Row == LCD_ROW_1)
    {

        LOC_u8data = ((lcd_SetCursor) + (Copy_u8Col - 1)); // Row1 -> 0x80+col-1
    }

    else if (Copy_u8Row == LCD_ROW_2)
    {

        LOC_u8data = ((lcd_SetCursor) + (64) + (Copy_u8Col - 1)); // Row2 -> 0xc0+col-1
    }
    LCD_enuSendCommand(LOC_u8data);
    _delay_ms(1);

    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

ES_t LCD_enuSendExtraChar(u8 Copy_u8Row, u8 Copy_u8Col)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;

    u8 LOC_u8Iterator = 0;
    /* 1- Go To CGRAM            */
    LCD_enuSendCommand(lcd_CGRAM); // Make AC refers to the first Place/Address at CGRAM

    /* 2- Draw Character in CGRAM        */
    /* Hint : it will be copied to DDRAM automatically */
    for (LOC_u8Iterator = 0; LOC_u8Iterator < sizeof(LCD_u8ExtraChar) / sizeof(LCD_u8ExtraChar[0]); LOC_u8Iterator++)
    {

        LCD_enuSendData(LCD_u8ExtraChar[LOC_u8Iterator]);
    }

    /* 3- Back (AC) To DDRAM          */
    LCD_enuSetPosition(Copy_u8Row, Copy_u8Col);

    /* 4- Send Character Address */
    for (LOC_u8Iterator = 0; LOC_u8Iterator < 8; LOC_u8Iterator++)
    {

        LCD_enuSendData(LOC_u8Iterator);
    }
    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

ES_t LCD_enuClearScreen(void)
{
    ES_t Local_EnuErrorState = ES_NOT_OK;
    LCD_enuSendCommand(lcd_Clear);
    _delay_ms(10); // wait more than 1.53 ms

    Local_EnuErrorState = ES_OK;

    return Local_EnuErrorState;
}

static void LCD_voidSendFallingEdge(void)
{
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_EN, DIO_u8HIGH);
    _delay_ms(1);
    DIO_Enu_SetPinValue(LCD_CONTROL_PORT, LCD_EN, DIO_u8LOW);
    _delay_ms(1);
}
