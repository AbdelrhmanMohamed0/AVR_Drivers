################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../press_led_on_and_off/APP.c \
../press_led_on_and_off/DIO_PROGRAM.c \
../press_led_on_and_off/SWITCH_CONFIG.c \
../press_led_on_and_off/SWITCH_PROGRAM.c 

OBJS += \
./press_led_on_and_off/APP.o \
./press_led_on_and_off/DIO_PROGRAM.o \
./press_led_on_and_off/SWITCH_CONFIG.o \
./press_led_on_and_off/SWITCH_PROGRAM.o 

C_DEPS += \
./press_led_on_and_off/APP.d \
./press_led_on_and_off/DIO_PROGRAM.d \
./press_led_on_and_off/SWITCH_CONFIG.d \
./press_led_on_and_off/SWITCH_PROGRAM.d 


# Each subdirectory must supply rules for building sources it contributes
press_led_on_and_off/%.o: ../press_led_on_and_off/%.c press_led_on_and_off/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


