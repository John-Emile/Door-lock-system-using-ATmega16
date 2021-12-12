################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application_micro2_test.c \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../lcd.c \
../main2_test.c \
../motor.c \
../pwm_timer.c \
../timer.c \
../timer_delay.c \
../twi.c \
../uart.c 

OBJS += \
./application_micro2_test.o \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./lcd.o \
./main2_test.o \
./motor.o \
./pwm_timer.o \
./timer.o \
./timer_delay.o \
./twi.o \
./uart.o 

C_DEPS += \
./application_micro2_test.d \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./lcd.d \
./main2_test.d \
./motor.d \
./pwm_timer.d \
./timer.d \
./timer_delay.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


