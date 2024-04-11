#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_MODE 4

#define LCD_DATA_PORT DIO_u8PORTB
#define LCD_CONTROL_PORT DIO_u8PORTA

#define LCD_RS DIO_u8PIN0
#define LCD_RW DIO_u8PIN1
#define LCD_EN DIO_u8PIN2

/*

 We draw each char on website ===>> https://maxpromer.github.io/LCD-Character-Creator/

 Hint : *this website already neglect the first 3 bits in each byte = 0 (on the left side)
        *take the hex value or ad 000 on the left
*/

// دودى

u8 LCD_u8ExtraChar[] = {
    0x00, 0x07, 0x04, 0x12, 0x12, 0x1E, 0x0C, 0x00, // Char4
    0x00, 0x03, 0x03, 0x03, 0x03, 0x1F, 0x1F, 0x00, // Char3
    0x00, 0x0F, 0x09, 0x0F, 0x03, 0x06, 0x0C, 0x00, // Char2
    0x00, 0x03, 0x03, 0x03, 0x03, 0x1F, 0x1F, 0x00  // Char1

};

#endif