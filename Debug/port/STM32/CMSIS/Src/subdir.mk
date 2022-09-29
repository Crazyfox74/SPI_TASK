################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../port/STM32/CMSIS/Src/system_stm32l4xx.c 

OBJS += \
./port/STM32/CMSIS/Src/system_stm32l4xx.o 

C_DEPS += \
./port/STM32/CMSIS/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
port/STM32/CMSIS/Src/%.o port/STM32/CMSIS/Src/%.su: ../port/STM32/CMSIS/Src/%.c port/STM32/CMSIS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/radio" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/utils" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/perif" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-port-2f-STM32-2f-CMSIS-2f-Src

clean-port-2f-STM32-2f-CMSIS-2f-Src:
	-$(RM) ./port/STM32/CMSIS/Src/system_stm32l4xx.d ./port/STM32/CMSIS/Src/system_stm32l4xx.o ./port/STM32/CMSIS/Src/system_stm32l4xx.su

.PHONY: clean-port-2f-STM32-2f-CMSIS-2f-Src

