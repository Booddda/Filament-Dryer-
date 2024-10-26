/*
 * KEYPAD.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include<avr/io.h>
#include "utilities.h"

void keypad_init();
volatile uint8_t detect_sw();


#endif /* KEYPAD_H_ */
