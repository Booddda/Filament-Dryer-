/*
 * ADC.c
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */
#include "ADC.h"

void ADC_init(){

ADMUX |=(1<<REFS0); //voltage reference from AVCC reference

ADCSRA |= (1<<ADEN); //Enable ADC

ADCSRA   |=(1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //Select 128 pre-scaler

	}
uint16_t ADC_read(uint8_t channel_number){

	ADMUX &=0xF0; //clearing the old channel that was read

	ADMUX|=channel_number; //define the new ADC channel to read

	DDRA &=~ (1<< channel_number); // set the channel pin as input

	//start conversion from analog to digital
	ADCSRA |= (1<<ADSC);

	while (  (ADCSRA & (1<<ADIF)) ==0  ); //wait to finish conversion

	uint8_t temp_L =0;// temporary variable to save Lower bits
	uint8_t temp_H =0;// temporary variable to save Higher bits
	uint16_t temp_full=0;//temporary variable to save the whole value of the conversion
	//put value in digital volt value

	temp_L = ADCL; //Read Lower First
	temp_H = ADCH;

	temp_full = temp_H; // put Hight to the first 2 bits in the 16-bit variable called digital_volt_value
	temp_full = temp_full << 8 ; // move the 2-bit to the left by 8
	temp_full |= temp_L ; //put the lower 8-bit values then


	ADCSRA |= (1<<ADIF); //clear the flag
	return temp_full;
}
uint16_t mapping(uint16_t x){
	//mapping (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
	return ((((x - 0)*(100UL - 40UL))/(1024UL - 0)) + 40UL);
}


