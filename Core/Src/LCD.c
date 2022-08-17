/*
 * LCD.c
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */



/** Put this in the src folder **/

#include "LCD.h"


#define SLAVE_ADDRESS_LCD (0x27 << 1) // change this according to ur setup

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
	HAL_Delay(1);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_clear (void)
{
	lcd_send_cmd (0x00);
	for (int i=0; i<100; i++)
	{
		lcd_send_data (' ');
	}
}

void lcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}


void Clear_LCD(){
	lcd_send_cmd(0x01);
	HAL_Delay(1);
}


/*
 * Set the cursor to the first unit of the line
 * @param num_of_line desired line
 */
void LCD_Select_Line(uint8_t num_of_line){
	switch (num_of_line){
	case 1:
		lcd_send_cmd(0x80|0x00);
		break;
	case 2:
		lcd_send_cmd(0x80|0x40);
		break;
	case 3:
		lcd_send_cmd(0x80|0x14);
		break;
	case 4:
		lcd_send_cmd(0x80|0x54);
		break;
	default:
		lcd_send_cmd(0x80|0x00);
		break;
	}
	HAL_Delay(1);
}


void LCD_Set_Cursor(uint8_t num_of_line, uint8_t poz){
	if (num_of_line > 4){
		num_of_line = 4;
	}

	if (poz > 19){
		poz = 19;
	}

	switch (num_of_line){
	case 1:
		lcd_send_cmd(0x80|(0x00+poz));
		break;
	case 2:
		lcd_send_cmd(0x80|(0x40+poz));
		break;
	case 3:
		lcd_send_cmd(0x80|(0x14+poz));
		break;
	case 4:
		lcd_send_cmd(0x80|(0x54+poz));
		break;
	default:
		lcd_send_cmd(0x80|(0x00+poz));
		break;
	}

	HAL_Delay(1);
}

void Set_DDRAM_Address(uint8_t add){
	if (add > 0x67){
		add = 0x67;
	}
	lcd_send_cmd(0x80|add);
	HAL_Delay(1);
}



