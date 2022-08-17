/*
 * LCD.h
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_


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

void Set_DDRAM_Address(uint8_t add);


#endif /* INC_LCD_H_ */
