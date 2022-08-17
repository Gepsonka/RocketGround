/*
 * sysinit.c
 *
 *  Created on: Aug 17, 2022
 *      Author: gepsonka
 */

#include "sysinit.h"


/**
 * Running checks on the pheriperials
 */
void Run_Checks(){
	if (!Is_LCD_Available()){
		Error_Handler(); // Without LCD the program won't start
	}

	if (!Is_BMP280_Available()){
		Clear_LCD();
		LCD_Send_Middle_Aligned_String("BMP280 is not", 1);
		LCD_Send_Middle_Aligned_String("available on i2c.", 2);
		HAL_Delay(4000);
		Clear_LCD();
	}

	if (!Is_Relay_Available()){
		Clear_LCD();
		LCD_Send_Middle_Aligned_String("Relay is not", 1);
		LCD_Send_Middle_Aligned_String("available.", 2);
		LCD_Send_Middle_Aligned_String("Device Won't start", 4);
		HAL_Delay(4000);
	}

	// Will need one for the LoRa module
}

bool Is_LCD_Available(){
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c2, SLAVE_ADDRESS_LCD, 50, 10);
	if (status == HAL_OK){
		return 1;
	}
	return 0;
}


bool Is_BMP280_Available(){
	uint8_t data;
	HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, BMP280_I2C_ADDRESS_0 << 1, 50, 10);

	if (status == HAL_OK){
		return 1;
	}

	return 0;
}

/**
 * Only availabel through manual testing.
 * User has watch if the relay turns on and off
 */
bool Is_Relay_Available(){
	for (int i=0;i<6; i++){
		Toggle_Relay();
		HAL_Delay(1000);
	}
	Turn_Relay_Off();

	// Will need verification from user after the buttons push
	// (Currently buttons are not ready)
	return 1; // temporary
}
