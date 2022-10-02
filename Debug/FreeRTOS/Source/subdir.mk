################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/croutine.c \
../FreeRTOS/Source/event_groups.c \
../FreeRTOS/Source/list.c \
../FreeRTOS/Source/queue.c \
../FreeRTOS/Source/stream_buffer.c \
../FreeRTOS/Source/tasks.c \
../FreeRTOS/Source/timers.c 

OBJS += \
./FreeRTOS/Source/croutine.o \
./FreeRTOS/Source/event_groups.o \
./FreeRTOS/Source/list.o \
./FreeRTOS/Source/queue.o \
./FreeRTOS/Source/stream_buffer.o \
./FreeRTOS/Source/tasks.o \
./FreeRTOS/Source/timers.o 

C_DEPS += \
./FreeRTOS/Source/croutine.d \
./FreeRTOS/Source/event_groups.d \
./FreeRTOS/Source/list.d \
./FreeRTOS/Source/queue.d \
./FreeRTOS/Source/stream_buffer.d \
./FreeRTOS/Source/tasks.d \
./FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/%.o FreeRTOS/Source/%.su: ../FreeRTOS/Source/%.c FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -c -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/inc" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Lib" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/port/STM32/CMSIS/Include" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/radio" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/utils" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/perif" -I"D:/Nero/SPI_TASK-branch_1/SPI_TASK-branch_1/Src/storage" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-Source

clean-FreeRTOS-2f-Source:
	-$(RM) ./FreeRTOS/Source/croutine.d ./FreeRTOS/Source/croutine.o ./FreeRTOS/Source/croutine.su ./FreeRTOS/Source/event_groups.d ./FreeRTOS/Source/event_groups.o ./FreeRTOS/Source/event_groups.su ./FreeRTOS/Source/list.d ./FreeRTOS/Source/list.o ./FreeRTOS/Source/list.su ./FreeRTOS/Source/queue.d ./FreeRTOS/Source/queue.o ./FreeRTOS/Source/queue.su ./FreeRTOS/Source/stream_buffer.d ./FreeRTOS/Source/stream_buffer.o ./FreeRTOS/Source/stream_buffer.su ./FreeRTOS/Source/tasks.d ./FreeRTOS/Source/tasks.o ./FreeRTOS/Source/tasks.su ./FreeRTOS/Source/timers.d ./FreeRTOS/Source/timers.o ./FreeRTOS/Source/timers.su

.PHONY: clean-FreeRTOS-2f-Source

