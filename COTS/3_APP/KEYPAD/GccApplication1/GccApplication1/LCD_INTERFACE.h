#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define FOUR_BITS 0x28  // 4 bits mode initialization
#define EIGHT_BITS 0x38 // 8 bits mode initialization (8-bit data, 2-line display, 5 x 7 font )

#define lcd_DisplayOn_CursorOff 0x0c  // display on, cursor off, don't blink character
#define lcd_DisplayOn_CursorOn 0x0e   // display on, cursor on, don't blink character
#define lcd_DisplayOff_CursorOff 0x08 // turn display off
#define lcd_Clear 0x01                // replace all characters with ASCII 'space'
#define lcd_EntryMode 0x06            // shift cursor from left to right on read/write
#define lcd_Home 0x02                 // return cursor to first position on first line
#define lcd_CGRAM 0x40                // the first Place/Address at CGRAM
#define lcd_SetCursor 0x80            // set cursor position
#define lcd_FunctionReset 0x30        // reset the LCD

#define LCD_ROW_1 1
#define LCD_ROW_2 2

#define LCD_COL_1 1
#define LCD_COL_2 2
#define LCD_COL_3 3
#define LCD_COL_4 4
#define LCD_COL_5 5
#define LCD_COL_6 6
#define LCD_COL_7 7
#define LCD_COL_8 8
#define LCD_COL_9 9
#define LCD_COL_10 10
#define LCD_COL_11 11
#define LCD_COL_12 12
#define LCD_COL_13 13
#define LCD_COL_14 14
#define LCD_COL_15 15
#define LCD_COL_16 16

ES_t LCD_enuInit(void);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuSendData(u8 Copy_u8Data);

ES_t LCD_enuSendString(const u8 *Copy_u8ptrString);

ES_t LCD_enuSendNumber(s64 Copy_s64Number);

ES_t LCD_enuSetPosition(u8 Copy_u8Row, u8 Copy_u8Col);

ES_t LCD_enuSendExtraChar(u8 Copy_u8Row, u8 Copy_u8Col);

ES_t LCD_enuClearScreen(void);

#endif