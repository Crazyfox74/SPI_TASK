################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gui/LCD_ML1001.c \
../Src/gui/LCD_ML1001_interface.c \
../Src/gui/finger.c \
../Src/gui/gui.c \
../Src/gui/gui_hal.c \
../Src/gui/led.c \
../Src/gui/tsc.c 

OBJS += \
./Src/gui/LCD_ML1001.o \
./Src/gui/LCD_ML1001_interface.o \
./Src/gui/finger.o \
./Src/gui/gui.o \
./Src/gui/gui_hal.o \
./Src/gui/led.o \
./Src/gui/tsc.o 

C_DEPS += \
./Src/gui/LCD_ML1001.d \
./Src/gui/LCD_ML1001_interface.d \
./Src/gui/finger.d \
./Src/gui/gui.d \
./Src/gui/gui_hal.d \
./Src/gui/led.d \
./Src/gui/tsc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/gui/%.o Src/gui/%.su: ../Src/gui/%.c Src/gui/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-gui

clean-Src-2f-gui:
	-$(RM) ./Src/gui/LCD_ML1001.d ./Src/gui/LCD_ML1001.o ./Src/gui/LCD_ML1001.su ./Src/gui/LCD_ML1001_interface.d ./Src/gui/LCD_ML1001_interface.o ./Src/gui/LCD_ML1001_interface.su ./Src/gui/finger.d ./Src/gui/finger.o ./Src/gui/finger.su ./Src/gui/gui.d ./Src/gui/gui.o ./Src/gui/gui.su ./Src/gui/gui_hal.d ./Src/gui/gui_hal.o ./Src/gui/gui_hal.su ./Src/gui/led.d ./Src/gui/led.o ./Src/gui/led.su ./Src/gui/tsc.d ./Src/gui/tsc.o ./Src/gui/tsc.su

.PHONY: clean-Src-2f-gui

