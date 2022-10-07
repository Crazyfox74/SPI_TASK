################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.c \
../port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.c \
../port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.c 

OBJS += \
./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.o \
./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.o \
./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.o 

C_DEPS += \
./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.d \
./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.d \
./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
port/STM32/STM32L4xx_HAL_Driver/Src/%.o port/STM32/STM32L4xx_HAL_Driver/Src/%.su: ../port/STM32/STM32L4xx_HAL_Driver/Src/%.c port/STM32/STM32L4xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Lib" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/radio" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/utils" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/perif" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-port-2f-STM32-2f-STM32L4xx_HAL_Driver-2f-Src

clean-port-2f-STM32-2f-STM32L4xx_HAL_Driver-2f-Src:
	-$(RM) ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.d ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.o ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_gpio.su ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.d ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.o ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_spi.su ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.d ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.o ./port/STM32/STM32L4xx_HAL_Driver/Src/stm32l4xx_ll_utils.su

.PHONY: clean-port-2f-STM32-2f-STM32L4xx_HAL_Driver-2f-Src

