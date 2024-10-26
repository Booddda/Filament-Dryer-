/*
 * actuator.c
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#include "actuator.h"
// function for powering on different actuators
void actuator_on(uint8_t actuator_port,uint8_t actuator_pin){
	SET_BIT(actuator_port,actuator_pin);
}
//function for powering off different actuators
void actuator_off(uint8_t actuator_port,uint8_t actuator_pin){
	CLEAR_BIT(actuator_port,actuator_pin);
}
