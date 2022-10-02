################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/MemMang/%.o FreeRTOS/Source/portable/MemMang/%.su: ../FreeRTOS/Source/portable/MemMang/%.c FreeRTOS/Source/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Lib" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/radio" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/utils" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/perif" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-Source-2f-portable-2f-MemMang

clean-FreeRTOS-2f-Source-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS/Source/portable/MemMang/heap_4.d ./FreeRTOS/Source/portable/MemMang/heap_4.o ./FreeRTOS/Source/portable/MemMang/heap_4.su

.PHONY: clean-FreeRTOS-2f-Source-2f-portable-2f-MemMang

