################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/utils/crc16_ccit.c \
../Src/utils/errors.c \
../Src/utils/hardfault.c \
../Src/utils/service.c \
../Src/utils/sleep.c \
../Src/utils/time_trckng.c \
../Src/utils/tm_seconds_to_date.c \
../Src/utils/uart_prot.c \
../Src/utils/uart_prot_new.c 

OBJS += \
./Src/utils/crc16_ccit.o \
./Src/utils/errors.o \
./Src/utils/hardfault.o \
./Src/utils/service.o \
./Src/utils/sleep.o \
./Src/utils/time_trckng.o \
./Src/utils/tm_seconds_to_date.o \
./Src/utils/uart_prot.o \
./Src/utils/uart_prot_new.o 

C_DEPS += \
./Src/utils/crc16_ccit.d \
./Src/utils/errors.d \
./Src/utils/hardfault.d \
./Src/utils/service.d \
./Src/utils/sleep.d \
./Src/utils/time_trckng.d \
./Src/utils/tm_seconds_to_date.d \
./Src/utils/uart_prot.d \
./Src/utils/uart_prot_new.d 


# Each subdirectory must supply rules for building sources it contributes
Src/utils/%.o Src/utils/%.su: ../Src/utils/%.c Src/utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-utils

clean-Src-2f-utils:
	-$(RM) ./Src/utils/crc16_ccit.d ./Src/utils/crc16_ccit.o ./Src/utils/crc16_ccit.su ./Src/utils/errors.d ./Src/utils/errors.o ./Src/utils/errors.su ./Src/utils/hardfault.d ./Src/utils/hardfault.o ./Src/utils/hardfault.su ./Src/utils/service.d ./Src/utils/service.o ./Src/utils/service.su ./Src/utils/sleep.d ./Src/utils/sleep.o ./Src/utils/sleep.su ./Src/utils/time_trckng.d ./Src/utils/time_trckng.o ./Src/utils/time_trckng.su ./Src/utils/tm_seconds_to_date.d ./Src/utils/tm_seconds_to_date.o ./Src/utils/tm_seconds_to_date.su ./Src/utils/uart_prot.d ./Src/utils/uart_prot.o ./Src/utils/uart_prot.su ./Src/utils/uart_prot_new.d ./Src/utils/uart_prot_new.o ./Src/utils/uart_prot_new.su

.PHONY: clean-Src-2f-utils

