################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/FreeRTOS/croutine.c \
../Src/FreeRTOS/event_groups.c \
../Src/FreeRTOS/list.c \
../Src/FreeRTOS/queue.c \
../Src/FreeRTOS/stream_buffer.c \
../Src/FreeRTOS/tasks.c \
../Src/FreeRTOS/timers.c 

OBJS += \
./Src/FreeRTOS/croutine.o \
./Src/FreeRTOS/event_groups.o \
./Src/FreeRTOS/list.o \
./Src/FreeRTOS/queue.o \
./Src/FreeRTOS/stream_buffer.o \
./Src/FreeRTOS/tasks.o \
./Src/FreeRTOS/timers.o 

C_DEPS += \
./Src/FreeRTOS/croutine.d \
./Src/FreeRTOS/event_groups.d \
./Src/FreeRTOS/list.d \
./Src/FreeRTOS/queue.d \
./Src/FreeRTOS/stream_buffer.d \
./Src/FreeRTOS/tasks.d \
./Src/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/FreeRTOS/%.o Src/FreeRTOS/%.su: ../Src/FreeRTOS/%.c Src/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Lib" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/port/STM32/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/radio" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/utils" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/perif" -I"C:/Users/User/STM32CubeIDE/workspace_1.10.1/mm215_gccMy/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-FreeRTOS

clean-Src-2f-FreeRTOS:
	-$(RM) ./Src/FreeRTOS/croutine.d ./Src/FreeRTOS/croutine.o ./Src/FreeRTOS/croutine.su ./Src/FreeRTOS/event_groups.d ./Src/FreeRTOS/event_groups.o ./Src/FreeRTOS/event_groups.su ./Src/FreeRTOS/list.d ./Src/FreeRTOS/list.o ./Src/FreeRTOS/list.su ./Src/FreeRTOS/queue.d ./Src/FreeRTOS/queue.o ./Src/FreeRTOS/queue.su ./Src/FreeRTOS/stream_buffer.d ./Src/FreeRTOS/stream_buffer.o ./Src/FreeRTOS/stream_buffer.su ./Src/FreeRTOS/tasks.d ./Src/FreeRTOS/tasks.o ./Src/FreeRTOS/tasks.su ./Src/FreeRTOS/timers.d ./Src/FreeRTOS/timers.o ./Src/FreeRTOS/timers.su

.PHONY: clean-Src-2f-FreeRTOS

