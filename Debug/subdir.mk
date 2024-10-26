################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../I2C_Master_C_file.c \
../KEYPAD.c \
../LCD.c \
../actuator.c \
../main.c 

OBJS += \
./ADC.o \
./I2C_Master_C_file.o \
./KEYPAD.o \
./LCD.o \
./actuator.o \
./main.o 

C_DEPS += \
./ADC.d \
./I2C_Master_C_file.d \
./KEYPAD.d \
./LCD.d \
./actuator.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


