/*
 * sysinit.h
 *
 *  Created on: Aug 17, 2022
 *      Author: gepsonka
 */

#ifndef INC_SYSINIT_H_
#define INC_SYSINIT_H_


#include <stdbool.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "LCD.h"
#include "bmp280.h"
#include "relay.h"
#include "i2c.h"
#include "main.h"


// Checks
bool Is_LCD_Available();

bool Is_BMP280_Available();

bool Is_Relay_Available();

void Run_Checks();

// Init

void Peripherial_Init();




#endif /* INC_SYSINIT_H_ */
