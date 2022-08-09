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
#include "string.h"

#define LCD_CMD_PIN_PORT GPIOC

#define LCD_DATA_PIN_PORT GPIOB

#define LCD_WRITE_DELAY 1


/*
 * Used in entry mode funtion
 * For further details take a look
 * into the datasheet
 */
typedef enum{
	CURSOR_DIRECTION_RIGHT,
	CURSOR_DIRECTION_LEFT
}DDRAMAddressDirection;

typedef enum{
	DISPLAY_NO_SHIFT,
	DISPLAY_SHIFT_RIGHT,
	DISPLAY_SHIFT_LEFT
}ShiftDisplayDirection;

typedef enum{
	DISPLAY_ON,
	DISPLAY_OFF
}DisplayPower;

typedef enum {
	CURSOR_ON,
	CURSOR_OFF
}CursorMode;

typedef enum {
	CURSOR_BLINK,
	CURSOR_NO_BLINK
} CursorBlinkMode;


typedef enum{
	BIT_MODE_8,
	BIT_MODE_4
}DataTransferMode; // Usually 8-bit

typedef enum{
	ONE_LINE,
	TWO_LINES
}NumOfDisplayLine;


typedef enum{
	FONT_5X10,
	FONT_5X8
}FontType;

// Low level functions

void Clear_LCD();

void Cursor_Return_Home();

void Entry_Mode_Set(DDRAMAddressDirection cursor_direction, ShiftDisplayDirection shift_direction);

void Display_Control(DisplayPower dsp_pwr, CursorMode cursor_mode, CursorBlinkMode cursor_blink_mode);

void Cursor_Shift(DDRAMAddressDirection cursor_dir);

void Display_Shift(ShiftDisplayDirection display_shift_direction);

void Interface_Init(DataTransferMode data_transfer_mode, NumOfDisplayLine num_of_display_line, FontType font_type); // Setting font, data transfer mode and line mode

void Set_CGRAM_Address(uint8_t add);

void Set_DDRAM_Address(uint8_t add);

void Write_Data_to_RAM(uint8_t data);

void Read_Data_From_Ram(uint8_t* dest);


// Higher level functions

void Power_On_LCD_8_Bit_Mode();

void Init_LCD();

void Write_String_to_LCD(char* str);

void Write_Line_to_LCD(char* str);


// For predefined behavior

void Print_Welcome_Message();

void Print_LoRa_Search();

void Print_Rocket_Init();

void Print_Rocket_Ready_to_Launch();

void Print_Rocket_In_Flight_Data(); // TODO: specify arguments later...


void Print_Char();

#endif /* INC_LCD_H_ */
