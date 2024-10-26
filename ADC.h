/*
 * ADC.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h> //including digital IO liberary
void ADC_init();//to intialize the ADC
uint16_t ADC_read(uint8_t channel_number);//returns the the digital reading value from the ADC and takes the channel number as input
uint16_t mapping(uint16_t x);//mapping between the ADC value and the temperatures used


#endif /* ADC_H_ */
