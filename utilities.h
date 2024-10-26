/*
 * utilities.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_
// the used macros
#define SET_BIT(REGISTER,BIT_NUMBER) REGISTER|=(1<<BIT_NUMBER)
#define CLEAR_BIT(REGISTER,BIT_NUMBER) REGISTER&=(~(1<<BIT_NUMBER))
#define TOGGLE_BIT(REGISTER,BIT_NUMBER) REGISTER^=(1<<BIT_NUMBER)
#define GET_BIT(REGISTER,BIT_NUMBER) ((REGISTER>>BIT_NUMBER)&1)

#endif /* UTILITIES_H_ */
