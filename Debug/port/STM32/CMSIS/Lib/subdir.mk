################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../port/STM32/CMSIS/Lib/arm_cos_f32.c \
../port/STM32/CMSIS/Lib/arm_fir_f32.c \
../port/STM32/CMSIS/Lib/arm_fir_init_f32.c 

OBJS += \
./port/STM32/CMSIS/Lib/arm_cos_f32.o \
./port/STM32/CMSIS/Lib/arm_fir_f32.o \
./port/STM32/CMSIS/Lib/arm_fir_init_f32.o 

C_DEPS += \
./port/STM32/CMSIS/Lib/arm_cos_f32.d \
./port/STM32/CMSIS/Lib/arm_fir_f32.d \
./port/STM32/CMSIS/Lib/arm_fir_init_f32.d 


# Each subdirectory must supply rules for building sources it contributes
port/STM32/CMSIS/Lib/%.o port/STM32/CMSIS/Lib/%.su: ../port/STM32/CMSIS/Lib/%.c port/STM32/CMSIS/Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_TABLE_SIN_F32 -DARM_FAST_ALLOW_TABLES -c -I"D:/2021_1/Cube/gas/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/gas/port/STM32/CMSIS/Lib" -I"D:/2021_1/Cube/gas/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/gas/Src/libs/axsem/code" -I"D:/2021_1/Cube/gas/Src/libs/radio_lib" -I"D:/2021_1/Cube/gas/Src/libs/ufifo" -I"D:/2021_1/Cube/gas/Src/libs/axsem" -I"D:/2021_1/Cube/gas/Src/libs/boot/ext" -I"D:/2021_1/Cube/gas/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/gas/Src" -I"D:/2021_1/Cube/gas/Src/radio" -I"D:/2021_1/Cube/gas/Src/utils" -I"D:/2021_1/Cube/gas/Src/ncp_ex" -I"D:/2021_1/Cube/gas/Src/ver_build" -I"D:/2021_1/Cube/gas/Src/flow" -I"D:/2021_1/Cube/gas/Src/perif" -I"D:/2021_1/Cube/gas/Src/gui" -I"D:/2021_1/Cube/gas/Src/storage" -Os -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-port-2f-STM32-2f-CMSIS-2f-Lib

clean-port-2f-STM32-2f-CMSIS-2f-Lib:
	-$(RM) ./port/STM32/CMSIS/Lib/arm_cos_f32.d ./port/STM32/CMSIS/Lib/arm_cos_f32.o ./port/STM32/CMSIS/Lib/arm_cos_f32.su ./port/STM32/CMSIS/Lib/arm_fir_f32.d ./port/STM32/CMSIS/Lib/arm_fir_f32.o ./port/STM32/CMSIS/Lib/arm_fir_f32.su ./port/STM32/CMSIS/Lib/arm_fir_init_f32.d ./port/STM32/CMSIS/Lib/arm_fir_init_f32.o ./port/STM32/CMSIS/Lib/arm_fir_init_f32.su

.PHONY: clean-port-2f-STM32-2f-CMSIS-2f-Lib

