/*
 * KEYPAD.c
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#include"KEYPAD.h"

void keypad_init(){
	// defining that following pins are input pins by giving the bit register zero using clear bit function
	DDRC=0b00111100; //make all rows as output (c5,c4,c3,c2)
	DDRD=0x00; //make all columns input (target: D7,D6,D5,D3)
	PORTD=0b11101000; // make sure that all switches are turned off (pull up)
}
volatile uint8_t detect_sw(){
	volatile uint8_t sw;
	CLEAR_BIT(PORTC,5);
	PORTC|=(1<<4)|(1<<3)|(1<<2);
	if(!(GET_BIT(PIND,7))){sw=1;}
	if(!(GET_BIT(PIND,6))){sw=2;}
	if(!(GET_BIT(PIND,5))){sw=3;}
	if(!(GET_BIT(PIND,3))){sw=4;}
	CLEAR_BIT(PORTC,4);
	PORTC|=(1<<5)|(1<<3)|(1<<2);
	if(!(GET_BIT(PIND,7))){sw=5;}
	if(!(GET_BIT(PIND,6))){sw=6;}
	if(!(GET_BIT(PIND,5))){sw=7;}
	if(!(GET_BIT(PIND,3))){sw=8;}
	CLEAR_BIT(PORTC,3);
	PORTC|=(1<<5)|(1<<4)|(1<<2);
	if(!(GET_BIT(PIND,7))){sw=9;}
	if(!(GET_BIT(PIND,6))){sw=10;}
	if(!(GET_BIT(PIND,5))){sw=11;}
	if(!(GET_BIT(PIND,3))){sw=12;}
	CLEAR_BIT(PORTC,2);
	PORTC|=(1<<5)|(1<<3)|(1<<4);
	if(!(GET_BIT(PIND,7))){sw=13;}
	if(!(GET_BIT(PIND,6))){sw=14;}
	if(!(GET_BIT(PIND,5))){sw=15;}
	if(!(GET_BIT(PIND,3))){sw=16;}
	return sw;
}






