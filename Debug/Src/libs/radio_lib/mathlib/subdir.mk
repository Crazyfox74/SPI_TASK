################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/libs/radio_lib/mathlib/aes.c \
../Src/libs/radio_lib/mathlib/crc.c \
../Src/libs/radio_lib/mathlib/xtea.c 

OBJS += \
./Src/libs/radio_lib/mathlib/aes.o \
./Src/libs/radio_lib/mathlib/crc.o \
./Src/libs/radio_lib/mathlib/xtea.o 

C_DEPS += \
./Src/libs/radio_lib/mathlib/aes.d \
./Src/libs/radio_lib/mathlib/crc.d \
./Src/libs/radio_lib/mathlib/xtea.d 


# Each subdirectory must supply rules for building sources it contributes
Src/libs/radio_lib/mathlib/%.o Src/libs/radio_lib/mathlib/%.su: ../Src/libs/radio_lib/mathlib/%.c Src/libs/radio_lib/mathlib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/libs/axsem/code" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/libs/radio_lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/libs/ufifo" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/libs/axsem" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/libs/boot/ext" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/libs/boot/bl_user" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/radio" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/utils" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/ncp_ex" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/ver_build" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/perif" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-libs-2f-radio_lib-2f-mathlib

clean-Src-2f-libs-2f-radio_lib-2f-mathlib:
	-$(RM) ./Src/libs/radio_lib/mathlib/aes.d ./Src/libs/radio_lib/mathlib/aes.o ./Src/libs/radio_lib/mathlib/aes.su ./Src/libs/radio_lib/mathlib/crc.d ./Src/libs/radio_lib/mathlib/crc.o ./Src/libs/radio_lib/mathlib/crc.su ./Src/libs/radio_lib/mathlib/xtea.d ./Src/libs/radio_lib/mathlib/xtea.o ./Src/libs/radio_lib/mathlib/xtea.su

.PHONY: clean-Src-2f-libs-2f-radio_lib-2f-mathlib

