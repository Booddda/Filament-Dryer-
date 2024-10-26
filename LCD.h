/*
 * LCD.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */
/*
 * LCD.h
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */
#ifndef LCD_H_
#define LCD_H_
#include<avr/io.h>
#include <util/delay.h>
#include "utilities.h"
//PINS definition
#define RS_PORT PORTA
#define RS_DDR DDRA
#define RS_pin 3
#define EN_PORT PORTA
#define EN_DDR DDRA
#define EN_pin 2
#define DATA_PORT PORTB //LCD connected to PORT
#define DATA_DDR DDRB
//commands HEX code
#define LCD_init1 0x33
#define LCD_init2 0x32
#define LCD_clear 0x01
#define LCD_return_home 0x02
#define LCD_shift_cursor_left 0x04
#define LCD_shift_cursor_right 0x06
#define LCD_shift_display_right 0x05
#define LCD_shift_display_left 0x07
#define LCD_display_cursor_off 0x08
#define LCD_display_off_cursor_on 0x0A
#define LCD_display_on_cursor_off 0x0C
#define LCD_display_on_cursor_blink 0x0E
#define LCD_shift_cursor_pos_left 0x10
#define LCD_shift_cursor_pos_right 0x14
#define LCD_shift_entire_display_left 0x18
#define LCD_shift_entire_display_right 0x1C
#define LCD_force_cursor_begining 0xC0
#define LCD_4_bit_mode 0x28
#define LCD_8_bit_mode 0x38

void LCD_send_cmd(unsigned char command);
void LCD_send_data(unsigned char data);
void LCD_init();
void LCD_out(char data[]);
void LCD_String_xy (char row, char pos, char *str);
#endif
