/*
 * main.c
 *
 *  Created on: Jan 7, 2024
 *      Author: Marwa
 */

// including all libraries
#include "LCD.h"
#include "ADC.h"
#include "KEYPAD.h"
#include "actuator.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <avr/interrupt.h>
#include "I2C_Master_H_file.h"
#include <avr/io.h>
#define Device_Write_address	0xD0	/* Define RTC DS1307 slave write address */
#define Device_Read_address	0xD1	/* Make LSB bit high of slave address for read */
// actuators' pins definition
#define RED_LED PB7   // device is not working indicator
#define GREEN_LED PA4 // device is working indicator
#define BUZZER PC6  // using buzzer as stop indicator
#define PELITER PC7 // using peltier as heater
#define FAN PA7  // fan actuator to circulate hot air inside our device
#define POTENTIOMETER PA0    // adjustment of temperature in manual mode
#define lm35          PA1
//global variables definition and initialization
uint8_t temperature=0;//temperature in celsius
unsigned long time=0;//time in hours
uint8_t current_temperature=0; //updating temperature variable
uint8_t state=0; // to switch between manual and automatic mode
uint8_t start=0; // initialization of a flag
uint16_t pot_reading=0;// initialization of potentiometer reading variable
uint16_t temp=0;// initialization of temperature reading variable
uint16_t digital_volt_value=0; // initialization of mapped value
char to_be_printed_first_row[20];//the string to be printed will be stored here for first row
char to_be_printed_second_row[20];//the string to be printed will be stored here for second row
char to_be_printed_third_row[20];//the string to be printed will be stored here for third row
char to_be_printed_fourth_row[20];//the string to be printed will be stored here for fourth row
volatile uint8_t switch_pressed; //to store which switch is pressed
uint8_t second,minute,hour;
uint8_t closeMM,closeSS;
unsigned long startTime= 0;
unsigned long currentTime =0;
unsigned long elapsedTime= 0;
//unsigned long COUNTDOWN_TIME;
char buffer_1[50];
//function prototypes
void automatic();
void manual();
void ext_interrupt();
int RTC_BCD2DEC(int val);
void RTC_Read_Clock(char read_clock_address);
void RTC_Count_down_Timer();

int main(){

	//complete except timer and DHT
	ADC_init();//initializing the ADC
	LCD_init();//initializing the LCD
	keypad_init();//initializing the keypad
	I2C_Init();
	ext_interrupt(); //calling the initializing of the external interrupts
	//Initializing inputs and outputs
	// all leds ,fan , buzzer and peliter are inputs
	// potentiometer is input
	SET_BIT(DDRB,RED_LED);
	SET_BIT(DDRA,GREEN_LED);
	SET_BIT(DDRC,PELITER);
	SET_BIT(DDRC,BUZZER);
	SET_BIT(DDRA,FAN);
	CLEAR_BIT(DDRA,POTENTIOMETER);

	//LCD commands
	LCD_send_cmd(LCD_force_cursor_begining);//set the cursor at the beginning of the LCD
	LCD_send_cmd(LCD_clear);//clear the LCD

	while (1){
		startTime = 0;
		currentTime =0;
		elapsedTime= 0;
		LCD_init();//initializing the LCD
		LCD_send_cmd(LCD_return_home); //return home command for the LCD
		LCD_String_xy(1,1,"WELCOME"); //print the string of the welcome message in the first row and first column
		LCD_String_xy(2,1,"Automatic press 1");//print the string of the Automatic mode  in the second row and first column
		LCD_String_xy(3,1,"Manual press 2");//print the string of the manual mode in the third row and first column
		switch_pressed=detect_sw(); //to detect which switch is pressed

		if(switch_pressed==1){    //mode automatic is selected

			automatic(); // call automatic function
		}
		else if(switch_pressed==2){//mode manual is selected

			manual(); // call manual function
		}
	}

return 0; // termination of the code

}
ISR(INT1_vect){     //when interrupt 1 is triggered change start to 0 to force the system to turn of
	start=0;
}
void automatic(){
		state=1; // set state variable to 1 for automatic mode
		LCD_send_cmd(LCD_clear);//clear LCD
		while(switch_pressed!=5||switch_pressed!=6||switch_pressed!=7||switch_pressed!=8||switch_pressed!=9){
		LCD_String_xy(1,1,"PLA 5  ABS 6  "); //display the message in the first row and first column
		LCD_String_xy(2,1,"TPU 7  ASA 8"); //display the message in the second row and first column
		LCD_String_xy(3,1,"PC 9"); //display the message in the third row and first column
		switch_pressed=detect_sw(); //to detect which switch is pressed
		if(switch_pressed==5){ //mode automatic is selected
			temperature=45;//setting the temperature
			time=360;//time in second --> 6 min
			LCD_send_cmd(LCD_clear);//clear LCD
			LCD_send_cmd(LCD_return_home);//return home
			LCD_String_xy(1,1,"switch 5 is pressed");//display the message in the first row and first column
			LCD_String_xy(2,1,"Enabling PLA mode"); //display the message in the second row and first column
			sprintf(to_be_printed_third_row,"temperature= %d C",temperature);//concatenate the strings and store them in to_be_printed_third_row global variable
			LCD_String_xy(3,1,to_be_printed_third_row);//print the string of the temperature in the third row and first column
			_delay_ms(10000); // delay for 10 seconds
			break;
		}
		else if(switch_pressed==6){//mode manual is selected
			temperature=65; //setting the temperature
			time=360; //time in second --> 6 min
			LCD_send_cmd(LCD_clear);//clear LCD
			LCD_send_cmd(LCD_return_home);//return home
			LCD_String_xy(1,1,"switch 6 is pressed");//display the message in the first row and first column
			LCD_String_xy(2,1,"Enabling ABS manual");  //display the message in the second row and first column
			sprintf(to_be_printed_third_row,"temperature= %d C",temperature);//concatenate the strings and store them in to_be_printed_third_row global variable
			LCD_String_xy(3,1,to_be_printed_third_row);//print the string of the temperature in the third row and first column
			_delay_ms(10000); // delay for 10 seconds
			break;
		}
		else if(switch_pressed==7){//mode manual is selected
			temperature=55; //setting the temperature
			time=600;   //time in second --> 10 min
			LCD_send_cmd(LCD_clear);//clear LCD
			LCD_send_cmd(LCD_return_home);//return home
			LCD_String_xy(1,1,"switch 7 is pressed"); //display the message in the first row and first column
			LCD_String_xy(2,1,"Enabling TPU manual");//display the message in the second row and first column
			sprintf(to_be_printed_third_row,"temperature= %d C",temperature);//concatenate the strings and store them in to_be_printed_third_row global variable
			LCD_String_xy(3,1,to_be_printed_third_row);//print the string of the temperature in the third row and first column
			_delay_ms(10000); // delay for 10 seconds
			break;
		}
		else if(switch_pressed==8){//mode manual is selected
			temperature=80; //setting the temperature
			time=240;  //time in second --> 4 min
			LCD_send_cmd(LCD_clear);//clear LCD
			LCD_send_cmd(LCD_return_home);//return home
			LCD_String_xy(1,1,"switch 8 is pressed");//display the message in the first row and first column
			LCD_String_xy(2,1,"Enabling ASA manual");//display the message in the second row and first column
			sprintf(to_be_printed_third_row,"temperature= %d C",temperature);//concatenate the strings and store them in to_be_printed_third_row global variable
			LCD_String_xy(3,1,to_be_printed_third_row);//print the string of the temperature in the third row and first column
			_delay_ms(10000); // delay for 10 seconds
          break;
		}
		else if(switch_pressed==9){//mode manual is selected
				temperature=85; //setting the temperature
				time=300;    //time in second --> 5 min
				LCD_send_cmd(LCD_clear);//clear LCD
				LCD_send_cmd(LCD_return_home);//return home
				LCD_String_xy(1,1,"switch 9 is pressed"); //display the message in the first row and first column
				LCD_String_xy(2,1,"Enabling PC manual");//display the message in the second row and first column
				sprintf(to_be_printed_third_row,"temperature= %d C",temperature);//concatenate the strings and store them in to_be_printed_third_row global variable
				LCD_String_xy(3,1,to_be_printed_third_row);//print the string of the temperature in the third row and first column
				_delay_ms(10000); // delay for 10 seconds
			break;
			}
	}
		LCD_send_cmd(LCD_clear);//clear LCD

		// press start button to open device
		while(switch_pressed!=3){
			LCD_String_xy(1,1,"Press start ");//display the message in the first row and column
			switch_pressed=detect_sw();//to detect which switch is pressed
			if(switch_pressed==3){
				start=1; // switch start flag to 1
				LCD_send_cmd(LCD_clear);//clear LCD
				LCD_send_cmd(LCD_return_home);//return home
				break;
			}
		}
		RTC_Read_Clock(0); //read an instance of time to represent start time
		startTime = second + (minute*60);
		while(start==1){  // if start button is pressed
					SET_BIT(PORTA,GREEN_LED); // green led will open
					//dht read
					temp=ADC_read(lm35);
					current_temperature= temp/2.01;
					//timer start
					RTC_Read_Clock(0);
					RTC_Count_down_Timer();
				sprintf(to_be_printed_second_row,"temperature= %d C",current_temperature);//concatenate the strings and store them in to_be_printed global variable
				LCD_String_xy(2,1,to_be_printed_second_row);//print the string of the temperature in the second row and first column
				LCD_String_xy(3,1,"press 4 for stop");//print the string of stopping message  in the third row and first column
				if(current_temperature<temperature-0.1*temperature){ // condition to test if dht senses temperature smaller than the setting one-temperature*tolerance
					actuator_on(PORTC,PELITER); // turn on peliter
					actuator_on(PORTA,FAN);    // turn on fan
				}
				else if(current_temperature>=temperature-0.1*temperature&&current_temperature<=temperature+0.1*temperature){ // condition to test if dht senses temperature greater than or equal the setting one-temperature*tolerance and smaller than or equal to the setting one+temperature*tolerance
					actuator_off(PORTC,PELITER); // turn off peliter
					actuator_on(PORTA,FAN); // turn on fan
				}
				else if(current_temperature== temperature-0.01*temperature){ // test if current temperature is equal to the setting temperature-temperature *tolerance
					actuator_off(PORTC,PELITER); // turn off peliter
					actuator_off(PORTA,FAN); // turn off fan
				}
			}
				 // operation is terminated
					actuator_off(PORTA,FAN);  // turn off fan
					actuator_off(PORTC,PELITER); // turn off peliter
					SET_BIT(PORTB,RED_LED); // turn on red led
					SET_BIT(PORTC,BUZZER); // turn on buzzer
					LCD_send_cmd(LCD_clear);//clear LCD
					LCD_send_cmd(LCD_return_home);//return home
					LCD_String_xy(1,1,"Finishing");//print the string of finishing message in the first row and column
					_delay_ms(10000); // delay for 10 seconds
					LCD_send_cmd(LCD_clear);//clear LCD

}
void manual(){
	state=0;
	LCD_send_cmd(LCD_clear);//clear the LCD

	while(switch_pressed!=3){

	LCD_String_xy(1,1," Use pot to set ");//display the message in the first row and first column
	LCD_String_xy(2,1,"temperature");//display the message in the second row and first column
	pot_reading=ADC_read(POTENTIOMETER);//get reading of ADC and update mapped_value which is pot reading
		    	                            //and also the ADC 10Bit reading value from 0 to 1024 according to Pot reading
	temperature=mapping(pot_reading); // mapping pot reading to temperature values in degree celsius
	sprintf(to_be_printed_third_row,"temperature= %d C",temperature); //concatenate the strings and store them in to_be_printed_third_row global variable
	LCD_String_xy(3,1,to_be_printed_third_row);//print the string of the temperature in the third row and first column
	LCD_String_xy(4,1,"Press start");//print the string of the pressing start  in the fourth row and first column
	switch_pressed=detect_sw();//to detect which switch is pressed
	if(switch_pressed==3){ // to turn on our device if switch 3 is pressed
		start=1;
		break; // get out from the main while loop
	}
}
	LCD_send_cmd(LCD_clear);//clear the LCD

	while(start==1){  // if start button is pressed
		LCD_init();//initializing the LCD
		//dht read
				SET_BIT(PORTA,GREEN_LED); // green led will open
				temp=ADC_read(lm35);
				current_temperature= temp/2.01;
			sprintf(to_be_printed_second_row,"temperature= %d C",current_temperature);//concatenate the strings and store them in to_be_printed global variable
			LCD_String_xy(2,1,to_be_printed_second_row);//print the string of the temperature in the second row and first column
			LCD_String_xy(3,1,"press 4 for stop");//print the string of stopping message  in the third row and first column
			if(current_temperature<temperature-0.1*temperature){ // condition to test if dht senses temperature smaller than the setting one-temperature*tolerance
				actuator_on(PORTC,PELITER); // turn on peliter
				actuator_on(PORTA,FAN);    // turn on fan
			}
			else if(current_temperature>=temperature-0.1*temperature&&current_temperature<=temperature+0.1*temperature){ // condition to test if dht senses temperature greater than or equal the setting one-temperature*tolerance and smaller than or equal to the setting one+temperature*tolerance
				actuator_off(PORTC,PELITER); // turn off peliter
				actuator_on(PORTA,FAN); // turn on fan
			}
			else if(current_temperature== temperature-0.01*temperature){ // test if current temperature is equal to the setting temperature-temperature *tolerance
				actuator_off(PORTC,PELITER); // turn off peliter
				actuator_off(PORTA,FAN); // turn off fan
			}

		}
			 // if timer is finished and operation is terminated
				actuator_off(PORTA,FAN);  // turn off fan
				actuator_off(PORTC,PELITER); // turn off peliter
				SET_BIT(PORTB,RED_LED); // turn on red led
				SET_BIT(PORTC,BUZZER); // turn on buzzer
				LCD_send_cmd(LCD_clear);//clear LCD
				LCD_send_cmd(LCD_return_home);//return home
				LCD_String_xy(1,1,"Finishing");//print the string of finishing message in the first row and column
				_delay_ms(10000); // delay for 10 seconds
				LCD_send_cmd(LCD_clear);//clear LCD
				CLEAR_BIT(PORTB,RED_LED); // turn on red led
				CLEAR_BIT(PORTC,BUZZER); // turn on red led
}
// external interrupt definition
void ext_interrupt(){
	SET_BIT(GICR,7);// initializing interrupt 1
	CLEAR_BIT(MCUCR,2);//The low level of INT1 (when pressing the assigned pushbutton) generates an interrupt request (bit 2,3)
	CLEAR_BIT(MCUCR,3);
	sei();//set global interrupt enable
}


int RTC_BCD2DEC(int val)
{
	return (val - 6*(val>>4));
}

void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);	/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);/* Repeated start with device read address */

	second = I2C_Read_Ack();	/* Read second */
	second = RTC_BCD2DEC(second);
	minute = I2C_Read_Ack();	/* Read minute */
	minute = RTC_BCD2DEC(minute);
	hour = I2C_Read_Nack();		/* Read hour with Nack */
	hour = RTC_BCD2DEC(hour);
	I2C_Stop();			/* Stop i2C communication */
}

void RTC_Count_down_Timer()
{
	currentTime = second + (minute*60);
	elapsedTime = (currentTime - startTime);
	if(elapsedTime <= time)
	{
		 unsigned long remainingTime = time - elapsedTime;
		 closeMM = remainingTime / 60;
		 closeSS = remainingTime % 60;
		 sprintf(buffer_1, "Timer: %d:%d", closeMM,closeSS);
		 LCD_String_xy (1, 1, buffer_1);
		 if (remainingTime == 0) {
			 start =0;
		 }
	}


}


