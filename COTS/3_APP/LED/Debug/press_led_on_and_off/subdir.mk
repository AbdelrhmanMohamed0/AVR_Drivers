################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../press_led_on_and_off/DIO_PROGRAM.c \
../press_led_on_and_off/KEYPAD_PROGRAME.c \
../press_led_on_and_off/LCD_PROGRAME.c \
../press_led_on_and_off/Stack.c \
../press_led_on_and_off/main.c 

OBJS += \
./press_led_on_and_off/DIO_PROGRAM.o \
./press_led_on_and_off/KEYPAD_PROGRAME.o \
./press_led_on_and_off/LCD_PROGRAME.o \
./press_led_on_and_off/Stack.o \
./press_led_on_and_off/main.o 

C_DEPS += \
./press_led_on_and_off/DIO_PROGRAM.d \
./press_led_on_and_off/KEYPAD_PROGRAME.d \
./press_led_on_and_off/LCD_PROGRAME.d \
./press_led_on_and_off/Stack.d \
./press_led_on_and_off/main.d 


# Each subdirectory must supply rules for building sources it contributes
press_led_on_and_off/%.o: ../press_led_on_and_off/%.c press_led_on_and_off/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


