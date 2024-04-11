################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP.c \
../DIO_PROGRAM.c \
../LED_CONFIG.c \
../LED_PROGRAM.c \
../SWITCH_CONFIG.c \
../SWITCH_PROGRAM.c 

OBJS += \
./APP.o \
./DIO_PROGRAM.o \
./LED_CONFIG.o \
./LED_PROGRAM.o \
./SWITCH_CONFIG.o \
./SWITCH_PROGRAM.o 

C_DEPS += \
./APP.d \
./DIO_PROGRAM.d \
./LED_CONFIG.d \
./LED_PROGRAM.d \
./SWITCH_CONFIG.d \
./SWITCH_PROGRAM.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


