################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/utils/crc16_ccit.c \
../Src/utils/tm_seconds_to_date.c 

OBJS += \
./Src/utils/crc16_ccit.o \
./Src/utils/tm_seconds_to_date.o 

C_DEPS += \
./Src/utils/crc16_ccit.d \
./Src/utils/tm_seconds_to_date.d 


# Each subdirectory must supply rules for building sources it contributes
Src/utils/%.o Src/utils/%.su: ../Src/utils/%.c Src/utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/radio" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/utils" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/perif" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-utils

clean-Src-2f-utils:
	-$(RM) ./Src/utils/crc16_ccit.d ./Src/utils/crc16_ccit.o ./Src/utils/crc16_ccit.su ./Src/utils/tm_seconds_to_date.d ./Src/utils/tm_seconds_to_date.o ./Src/utils/tm_seconds_to_date.su

.PHONY: clean-Src-2f-utils

