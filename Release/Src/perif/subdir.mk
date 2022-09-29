################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/perif/adc_sens.c \
../Src/perif/clock.c \
../Src/perif/rtc.c \
../Src/perif/spi.c \
../Src/perif/spiFlash.c \
../Src/perif/uart.c 

OBJS += \
./Src/perif/adc_sens.o \
./Src/perif/clock.o \
./Src/perif/rtc.o \
./Src/perif/spi.o \
./Src/perif/spiFlash.o \
./Src/perif/uart.o 

C_DEPS += \
./Src/perif/adc_sens.d \
./Src/perif/clock.d \
./Src/perif/rtc.d \
./Src/perif/spi.d \
./Src/perif/spiFlash.d \
./Src/perif/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/perif/%.o Src/perif/%.su: ../Src/perif/%.c Src/perif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-perif

clean-Src-2f-perif:
	-$(RM) ./Src/perif/adc_sens.d ./Src/perif/adc_sens.o ./Src/perif/adc_sens.su ./Src/perif/clock.d ./Src/perif/clock.o ./Src/perif/clock.su ./Src/perif/rtc.d ./Src/perif/rtc.o ./Src/perif/rtc.su ./Src/perif/spi.d ./Src/perif/spi.o ./Src/perif/spi.su ./Src/perif/spiFlash.d ./Src/perif/spiFlash.o ./Src/perif/spiFlash.su ./Src/perif/uart.d ./Src/perif/uart.o ./Src/perif/uart.su

.PHONY: clean-Src-2f-perif

