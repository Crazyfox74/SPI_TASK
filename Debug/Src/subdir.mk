################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/radio" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/utils" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/perif" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.d ./Src/main.o ./Src/main.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

