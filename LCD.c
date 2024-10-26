/*
 * LCD.c
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

#include "LCD.h"
void LCD_send_cmd(unsigned char command)
{
CLEAR_BIT(RS_PORT,RS_pin); //Set RW to 0 (Connected to ground) to send commands
DATA_PORT= (0b00000111 & (command >> 4))|(0b00010000 & (command >>3));// send upper nibble of command
//send 1 ms pulse
SET_BIT(EN_PORT,EN_pin);
_delay_ms(1);
CLEAR_BIT(EN_PORT,EN_pin);
_delay_us(50);
DATA_PORT= (command & 0b00000111)|(0b00010000 & (command<<1));// send lower nibble of command
//Take only the left 4 bits, note that we still need to send the right 4 bits of command
//send 1 ms pulse
SET_BIT(EN_PORT,EN_pin);
_delay_ms(1);
CLEAR_BIT(EN_PORT,EN_pin);
_delay_us(50);
}

void LCD_send_data(unsigned char data)
{
SET_BIT(RS_PORT,RS_pin);//Set RW to 1() to indicate that we are sending data to LCD
DATA_PORT= (0b00000111 & (data >> 4))|(0b00010000 & (data >>3)); //send upper nibble of data
//send 1 ms pulse
SET_BIT(EN_PORT,EN_pin); //perform write operation
_delay_ms(1);
CLEAR_BIT(EN_PORT,EN_pin); //data transmit done
_delay_us(50);
DATA_PORT = (data & 0b00000111)|(0b00010000 & (data<<1));//send lower nibble of data
//send 1 ms pulse
SET_BIT(EN_PORT,EN_pin);//perform write operation of data
_delay_ms(1);
CLEAR_BIT(EN_PORT,EN_pin); //data transmit done no writing
_delay_us(50);
}
void LCD_init(){
DATA_DDR = 0xff;//output
EN_DDR = 0xff;//output
DATA_PORT = 0x00;//initial zero
CLEAR_BIT(EN_PORT,EN_pin); //initial ENABLE by zero
//sending commands like displaying cursor and using 4 bit mode instead of 8 bit
LCD_send_cmd(LCD_init1);
LCD_send_cmd(LCD_init2);
LCD_send_cmd(LCD_4_bit_mode);
LCD_send_cmd(LCD_display_on_cursor_blink);
LCD_send_cmd(LCD_clear);
_delay_ms(2);
LCD_send_cmd(LCD_shift_cursor_right);
_delay_ms(2);
}
void LCD_out(char data[]){
unsigned char i=0;
while (data[i] != 0){
LCD_send_data(data[i]);
i++;
}
}
void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 1 && pos<16){
	LCD_send_cmd((pos & 0x0F)|0x80);}	/* Command of first row and required position<16 */
	else if (row == 2 && pos<16){
	LCD_send_cmd((pos & 0x0F)|0xC0);}	/* Command of second row and required position<16 */
	else if (row == 3 && pos<16){
	LCD_send_cmd((pos & 0x0F)|0x94);}	/* Command of third row and required position<16 */
	else if (row == 4 && pos<16){
	LCD_send_cmd((pos & 0x0F)|0xD4);}	/* Command of Fourth row and required position<16 */
	LCD_out(str);		/* Call LCD output function */
}




