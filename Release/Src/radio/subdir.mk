################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/radio/SpiManager.c \
../Src/radio/TimerManager.c \
../Src/radio/radio.c \
../Src/radio/water5_proto.c 

OBJS += \
./Src/radio/SpiManager.o \
./Src/radio/TimerManager.o \
./Src/radio/radio.o \
./Src/radio/water5_proto.o 

C_DEPS += \
./Src/radio/SpiManager.d \
./Src/radio/TimerManager.d \
./Src/radio/radio.d \
./Src/radio/water5_proto.d 


# Each subdirectory must supply rules for building sources it contributes
Src/radio/%.o Src/radio/%.su: ../Src/radio/%.c Src/radio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-radio

clean-Src-2f-radio:
	-$(RM) ./Src/radio/SpiManager.d ./Src/radio/SpiManager.o ./Src/radio/SpiManager.su ./Src/radio/TimerManager.d ./Src/radio/TimerManager.o ./Src/radio/TimerManager.su ./Src/radio/radio.d ./Src/radio/radio.o ./Src/radio/radio.su ./Src/radio/water5_proto.d ./Src/radio/water5_proto.o ./Src/radio/water5_proto.su

.PHONY: clean-Src-2f-radio

