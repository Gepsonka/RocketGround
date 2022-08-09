/*
 * LCD.c
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */


// 2004A LCD datasheet: https://uk.beta-layout.com/download/rk/RK-10290_410.pdf

#include "LCD.h"

// Enable LCD pin toggle macros
#define ENABLE_WRITE() HAL_GPIO_WritePin(LCD_CMD_PIN_PORT, LCD_E_Pin, GPIO_PIN_SET)
#define DISABLE_WRITE() HAL_GPIO_WritePin(LCD_CMD_PIN_PORT, LCD_E_Pin, GPIO_PIN_RESET)
#define WRITE_DELAY() HAL_Delay(LCD_WRITE_DELAY);


/*
 * Repeated functionality.
 * Before each command pull all the LCD pins low.
 */
static void _pull_data_and_cmd_pins_low(){
	// Pull all the ctrl pins low
	HAL_GPIO_WritePin(LCD_CMD_PIN_PORT, LCD_RS_Pin|LCD_RW_Pin|LCD_E_Pin, GPIO_PIN_RESET);


	// Pull all the datapins low
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
						|LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin, GPIO_PIN_RESET);
}


/*
 * Enables Write on the LCD and creates a delay needed
 * specified in the datasheet.
 */
static void _write_and_delay(){
	ENABLE_WRITE();
	HAL_Delay(LCD_WRITE_DELAY);
	DISABLE_WRITE();
}





/*
 * Clear contents on LCD and return cursor to starting position
 */
void Clear_LCD(){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, GPIO_PIN_SET);
	DISABLE_WRITE();
}

/*
 * Return cursor to starting position
 */
void Cursor_Return_Home(){
	_pull_data_and_cmd_pins_low();
	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, GPIO_PIN_SET);
	DISABLE_WRITE();
}


/*
 * Datasheet...
 */
void Entry_Mode_Set(DDRAMAddressDirection cursor_direction, ShiftDisplayDirection shift_direction){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_SET);
	switch(cursor_direction){
	case CURSOR_DIRECTION_RIGHT:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, GPIO_PIN_SET);
	case CURSOR_DIRECTION_LEFT:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, GPIO_PIN_RESET);
	}

	switch(shift_direction){
	case DISPLAY_NO_SHIFT:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, GPIO_PIN_RESET);
	default:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, GPIO_PIN_SET);
	}
	DISABLE_WRITE();
}

void Display_Control(DisplayPower dsp_pwr, CursorMode cursor_mode, CursorBlinkMode cursor_blink_mode){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, GPIO_PIN_SET);
	switch(dsp_pwr){
	case DISPLAY_ON:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_SET);
	case DISPLAY_OFF:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_RESET);
	}

	switch(cursor_mode){
	case CURSOR_ON:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, GPIO_PIN_SET);
	case CURSOR_OFF:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, GPIO_PIN_RESET);
	}

	switch(cursor_blink_mode){
	case CURSOR_BLINK:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, GPIO_PIN_SET);
	case CURSOR_NO_BLINK:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, GPIO_PIN_RESET);
	}
	DISABLE_WRITE();
}

/*
 * Shifting cursor
 * @param cursor_dir direction to move the cursor to
 */
void Cursor_Shift(DDRAMAddressDirection cursor_dir){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, GPIO_PIN_RESET);
	switch(cursor_dir){
	case CURSOR_DIRECTION_RIGHT:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_SET);
	case CURSOR_DIRECTION_LEFT:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_RESET);
	}
	DISABLE_WRITE();
}

void Display_Shift(ShiftDisplayDirection display_shift_direction){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, GPIO_PIN_SET);
	switch(display_shift_direction){
	case DISPLAY_SHIFT_RIGHT:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_SET);
	default:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_RESET);
	}
	DISABLE_WRITE();
}


void Interface_Init(DataTransferMode data_transfer_mode, NumOfDisplayLine num_of_display_line, FontType font_type){
	_pull_data_and_cmd_pins_low();


	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, GPIO_PIN_SET);

	switch(data_transfer_mode){
	case BIT_MODE_8:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_SET);
	case BIT_MODE_4:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_RESET);
	}

	switch(num_of_display_line){
	case ONE_LINE:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, GPIO_PIN_RESET);
	case TWO_LINES:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, GPIO_PIN_SET);
	}

	switch(font_type){
	case FONT_5X10:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_SET);
	case FONT_5X8:
		HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, GPIO_PIN_RESET);
	}
	DISABLE_WRITE();
}



void Set_CGRAM_Address(uint8_t add){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D6_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, ((add>>5)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, ((add>>4)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, ((add>>3)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, ((add>>2)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, ((add>>1)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, ((add>>0)&0x01));

	DISABLE_WRITE();
}

void Set_DDRAM_Address(uint8_t add){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D7_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D6_Pin, ((add>>6)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, ((add>>5)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, ((add>>4)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, ((add>>3)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, ((add>>2)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, ((add>>1)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, ((add>>0)&0x01));

	DISABLE_WRITE();
}


void Write_Data_to_RAM(uint8_t data){
	_pull_data_and_cmd_pins_low();

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_CMD_PIN_PORT, LCD_RS_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D7_Pin, ((data>>7)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D6_Pin, ((data>>6)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, ((data>>5)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, ((data>>4)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D3_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D2_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D1_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D0_Pin, ((data>>0)&0x01));

	DISABLE_WRITE();
}


// Higher level functions

// LCD startup sequence
void Power_On_LCD_8_Bit_Mode(){
	HAL_Delay(30);


	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_SET);
	DISABLE_WRITE();

	HAL_Delay(8);

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_SET);
	DISABLE_WRITE();

	HAL_Delay(1);

	ENABLE_WRITE();
	WRITE_DELAY();
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_DATA_PIN_PORT, LCD_D4_Pin, GPIO_PIN_SET);
	DISABLE_WRITE();

	HAL_Delay(1);


	Interface_Init(BIT_MODE_8, ONE_LINE, FONT_5X10);
	Display_Control(DISPLAY_ON, CURSOR_ON, CURSOR_BLINK);
	Clear_LCD();
	Entry_Mode_Set(CURSOR_DIRECTION_RIGHT, DISPLAY_NO_SHIFT);

}

void Init_LCD(){
	HAL_Delay(100);
	Clear_LCD();
	HAL_Delay(10);
	Interface_Init(BIT_MODE_8, ONE_LINE, FONT_5X10);
	HAL_Delay(100);
	Display_Control(DISPLAY_ON, CURSOR_ON, CURSOR_BLINK);
	HAL_Delay(10);
	Entry_Mode_Set(CURSOR_DIRECTION_RIGHT, DISPLAY_NO_SHIFT);
	HAL_Delay(10);
	Cursor_Return_Home();

}

void Write_String_to_LCD(char* str){
	for(int i=0;i<strlen(str);i++){
		Write_Data_to_RAM(str[i]);
	}
}




