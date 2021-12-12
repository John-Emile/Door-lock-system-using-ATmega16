################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../application_micro1_test.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main1_test.c \
../timer.c \
../timer_delay.c \
../uart.c 

OBJS += \
./application_micro1_test.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main1_test.o \
./timer.o \
./timer_delay.o \
./uart.o 

C_DEPS += \
./application_micro1_test.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main1_test.d \
./timer.d \
./timer_delay.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


