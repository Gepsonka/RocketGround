/*
 * LCD.h
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#define SLAVE_ADDRESS_LCD (0x27 << 1) // change this according to ur setup

#define LCD_NUM_OF_LINES 4
#define LCD_NUM_OF_ROWS 20


#include "gpio.h"
#include "i2c.h"
#include "string.h"
#include "stm32l4xx_hal.h"

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear (void);



// Higher level functions

void Clear_LCD();

void LCD_Select_Line(uint8_t num_of_line);

void LCD_Set_Cursor(uint8_t num_of_line, uint8_t poz);

void LCD_Set_DDRAM_Address(uint8_t add);

void LCD_Send_Middle_Aligned_String(char* string, uint8_t num_of_line);

void LCD_Send_Error_Message(char* string);



#endif /* INC_LCD_H_ */
