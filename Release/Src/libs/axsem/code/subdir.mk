################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/libs/axsem/code/ax5043.c \
../Src/libs/axsem/code/ax5043_sw_freqw.c \
../Src/libs/axsem/code/axtrx.c 

OBJS += \
./Src/libs/axsem/code/ax5043.o \
./Src/libs/axsem/code/ax5043_sw_freqw.o \
./Src/libs/axsem/code/axtrx.o 

C_DEPS += \
./Src/libs/axsem/code/ax5043.d \
./Src/libs/axsem/code/ax5043_sw_freqw.d \
./Src/libs/axsem/code/axtrx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/libs/axsem/code/%.o Src/libs/axsem/code/%.su: ../Src/libs/axsem/code/%.c Src/libs/axsem/code/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-libs-2f-axsem-2f-code

clean-Src-2f-libs-2f-axsem-2f-code:
	-$(RM) ./Src/libs/axsem/code/ax5043.d ./Src/libs/axsem/code/ax5043.o ./Src/libs/axsem/code/ax5043.su ./Src/libs/axsem/code/ax5043_sw_freqw.d ./Src/libs/axsem/code/ax5043_sw_freqw.o ./Src/libs/axsem/code/ax5043_sw_freqw.su ./Src/libs/axsem/code/axtrx.d ./Src/libs/axsem/code/axtrx.o ./Src/libs/axsem/code/axtrx.su

.PHONY: clean-Src-2f-libs-2f-axsem-2f-code

