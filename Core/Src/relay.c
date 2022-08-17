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


void Turn_Relay_On(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
}

void Toggle_Relay(){
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
}


void Write_Relay(uint8_t state){
	switch(state){
	case 0:
		Turn_Relay_Off();
		break;
	default:
		Turn_Relay_On();
		break;
	}

}
