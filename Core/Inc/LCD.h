/*
 * LCD.h
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32l4xx_hal.h"
#include "gpio.h"

#define LCD_CMD_PIN_PORT GPIOC

#define LCD_DATA_PIN_PORT GPIOB


typedef enum{
	DISPLAY_ON,
	DISPLAY_OFF
}Display_Power;

typedef enum{
	BIT_MODE_8,
	BIT_MODE_4
}Data_Transfer_Mode; // Usually 8-bit

typedef enum{
	ONE_LINE,
	TWO_LINES
}Num_Of_Display_Line;


typedef enum{
	FONT_5X10,
	FONT_5X8
}Font_Type;


// Low level functions

void Clear_LCD();

void Cursor_Return_Home();

void Entry_Mode_Set();

void Display_Control(Display_Power dsp_pwr);

void Curson_Shift();

void Display_Shift();

void Interface_Init(); // Setting font, data transfer mode and line mode

void Set_CGRAM_Address(uint8_t add);

void Set_DDRAM_Address(uint8_t add);

void Write_Data_to_RAM(uint8_t data);

void Read_Data_From_Ram(uint8_t* dest);


// Higher level functions

void Write_String_to_LCD(char* str);

void Write_Line_to_LCD(char* str);


// For predefined behavior

void Print_Welcome_Message();

void Print_LoRa_Search();

void Print_Rocket_Init();

void Print_Rocket_Ready_to_Launch();

void Print_Rocket_In_Flight_Data(); // TODO: specify arguments later...




#endif /* INC_LCD_H_ */
