/*
 * relay.c
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */


#include "relay.h"

//void Turn_Relay_On(){
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
//}


void Turn_Relay_Off(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
}
