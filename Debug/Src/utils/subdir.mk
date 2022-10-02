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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Lib" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/radio" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/utils" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/perif" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-utils

clean-Src-2f-utils:
	-$(RM) ./Src/utils/crc16_ccit.d ./Src/utils/crc16_ccit.o ./Src/utils/crc16_ccit.su ./Src/utils/tm_seconds_to_date.d ./Src/utils/tm_seconds_to_date.o ./Src/utils/tm_seconds_to_date.su

.PHONY: clean-Src-2f-utils

