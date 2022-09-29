################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/flow/adc.c \
../Src/flow/approx_correct.c \
../Src/flow/gmm_manager.c \
../Src/flow/gmm_storage.c \
../Src/flow/kalman.c \
../Src/flow/phase.c \
../Src/flow/queue.c \
../Src/flow/sequencer.c \
../Src/flow/zero_offset.c 

OBJS += \
./Src/flow/adc.o \
./Src/flow/approx_correct.o \
./Src/flow/gmm_manager.o \
./Src/flow/gmm_storage.o \
./Src/flow/kalman.o \
./Src/flow/phase.o \
./Src/flow/queue.o \
./Src/flow/sequencer.o \
./Src/flow/zero_offset.o 

C_DEPS += \
./Src/flow/adc.d \
./Src/flow/approx_correct.d \
./Src/flow/gmm_manager.d \
./Src/flow/gmm_storage.d \
./Src/flow/kalman.d \
./Src/flow/phase.d \
./Src/flow/queue.d \
./Src/flow/sequencer.d \
./Src/flow/zero_offset.d 


# Each subdirectory must supply rules for building sources it contributes
Src/flow/%.o Src/flow/%.su: ../Src/flow/%.c Src/flow/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-flow

clean-Src-2f-flow:
	-$(RM) ./Src/flow/adc.d ./Src/flow/adc.o ./Src/flow/adc.su ./Src/flow/approx_correct.d ./Src/flow/approx_correct.o ./Src/flow/approx_correct.su ./Src/flow/gmm_manager.d ./Src/flow/gmm_manager.o ./Src/flow/gmm_manager.su ./Src/flow/gmm_storage.d ./Src/flow/gmm_storage.o ./Src/flow/gmm_storage.su ./Src/flow/kalman.d ./Src/flow/kalman.o ./Src/flow/kalman.su ./Src/flow/phase.d ./Src/flow/phase.o ./Src/flow/phase.su ./Src/flow/queue.d ./Src/flow/queue.o ./Src/flow/queue.su ./Src/flow/sequencer.d ./Src/flow/sequencer.o ./Src/flow/sequencer.su ./Src/flow/zero_offset.d ./Src/flow/zero_offset.o ./Src/flow/zero_offset.su

.PHONY: clean-Src-2f-flow

