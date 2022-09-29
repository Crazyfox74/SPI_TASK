################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/header/croutine.c \
../Src/header/heap_4.c \
../Src/header/list.c \
../Src/header/port.c \
../Src/header/queue.c \
../Src/header/stream_buffer.c \
../Src/header/tasks.c \
../Src/header/timers.c 

OBJS += \
./Src/header/croutine.o \
./Src/header/heap_4.o \
./Src/header/list.o \
./Src/header/port.o \
./Src/header/queue.o \
./Src/header/stream_buffer.o \
./Src/header/tasks.o \
./Src/header/timers.o 

C_DEPS += \
./Src/header/croutine.d \
./Src/header/heap_4.d \
./Src/header/list.d \
./Src/header/port.d \
./Src/header/queue.d \
./Src/header/stream_buffer.d \
./Src/header/tasks.d \
./Src/header/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/header/%.o Src/header/%.su: ../Src/header/%.c Src/header/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/radio" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/utils" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/perif" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-header

clean-Src-2f-header:
	-$(RM) ./Src/header/croutine.d ./Src/header/croutine.o ./Src/header/croutine.su ./Src/header/heap_4.d ./Src/header/heap_4.o ./Src/header/heap_4.su ./Src/header/list.d ./Src/header/list.o ./Src/header/list.su ./Src/header/port.d ./Src/header/port.o ./Src/header/port.su ./Src/header/queue.d ./Src/header/queue.o ./Src/header/queue.su ./Src/header/stream_buffer.d ./Src/header/stream_buffer.o ./Src/header/stream_buffer.su ./Src/header/tasks.d ./Src/header/tasks.o ./Src/header/tasks.su ./Src/header/timers.d ./Src/header/timers.o ./Src/header/timers.su

.PHONY: clean-Src-2f-header

