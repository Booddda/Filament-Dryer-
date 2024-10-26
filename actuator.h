/*
 * actuator.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_


#include <avr/io.h>
#include "utilities.h"

void actuator_on(uint8_t actuator_port,uint8_t actuator_pin);//for powering on different actuators

void actuator_off(uint8_t actuator_port,uint8_t actuator_pin);//for powering off different actuators




#endif /* ACTUATOR_H_ */
