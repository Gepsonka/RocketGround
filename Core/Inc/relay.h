/*
 * relay.h
 *
 *  Created on: Aug 7, 2022
 *      Author: expel
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

#include "stm32l4xx_hal.h"

/*
 * Low level lib for controlling the relay.
 */

void Turn_Relay_Off();

void Turn_Relay_On();

void Toggle_Relay();

void Write_Relay(uint8_t state);


#endif /* INC_RELAY_H_ */
