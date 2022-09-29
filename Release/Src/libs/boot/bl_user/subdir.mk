################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/libs/boot/bl_user/archive_user.c \
../Src/libs/boot/bl_user/bl_AppUser.c \
../Src/libs/boot/bl_user/bl_archive_user.c \
../Src/libs/boot/bl_user/bl_key_table.c \
../Src/libs/boot/bl_user/bl_user.c \
../Src/libs/boot/bl_user/bl_user_func_table.c 

OBJS += \
./Src/libs/boot/bl_user/archive_user.o \
./Src/libs/boot/bl_user/bl_AppUser.o \
./Src/libs/boot/bl_user/bl_archive_user.o \
./Src/libs/boot/bl_user/bl_key_table.o \
./Src/libs/boot/bl_user/bl_user.o \
./Src/libs/boot/bl_user/bl_user_func_table.o 

C_DEPS += \
./Src/libs/boot/bl_user/archive_user.d \
./Src/libs/boot/bl_user/bl_AppUser.d \
./Src/libs/boot/bl_user/bl_archive_user.d \
./Src/libs/boot/bl_user/bl_key_table.d \
./Src/libs/boot/bl_user/bl_user.d \
./Src/libs/boot/bl_user/bl_user_func_table.d 


# Each subdirectory must supply rules for building sources it contributes
Src/libs/boot/bl_user/%.o Src/libs/boot/bl_user/%.su: ../Src/libs/boot/bl_user/%.c Src/libs/boot/bl_user/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -DSTM32L412xx -DUSE_FULL_LL_DRIVER -DARM_MATH_CM4 -c -I"D:/2021_1/Cube/mm215_gcc/port/STM32/STM32L4xx_HAL_Driver/Inc" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem/code" -I"D:/2021_1/Cube/mm215_gcc/Src/radio" -I"D:/2021_1/Cube/mm215_gcc/Src/utils" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/radio_lib" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/axsem" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/bl_user" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/boot/ext" -I"D:/2021_1/Cube/mm215_gcc/Src/libs/ufifo" -I"D:/2021_1/Cube/mm215_gcc/Src/ncp_ex" -I"D:/2021_1/Cube/mm215_gcc/Src" -I"D:/2021_1/Cube/mm215_gcc/port/STM32/CMSIS/Include" -I"D:/2021_1/Cube/mm215_gcc/Src/ver_build" -I"D:/2021_1/Cube/mm215_gcc/Src/flow" -I"D:/2021_1/Cube/mm215_gcc/Src/perif" -I"D:/2021_1/Cube/mm215_gcc/Src/gui" -I"D:/2021_1/Cube/mm215_gcc/Src/storage" -Os -ffunction-sections -fdata-sections -Wall -flto -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-libs-2f-boot-2f-bl_user

clean-Src-2f-libs-2f-boot-2f-bl_user:
	-$(RM) ./Src/libs/boot/bl_user/archive_user.d ./Src/libs/boot/bl_user/archive_user.o ./Src/libs/boot/bl_user/archive_user.su ./Src/libs/boot/bl_user/bl_AppUser.d ./Src/libs/boot/bl_user/bl_AppUser.o ./Src/libs/boot/bl_user/bl_AppUser.su ./Src/libs/boot/bl_user/bl_archive_user.d ./Src/libs/boot/bl_user/bl_archive_user.o ./Src/libs/boot/bl_user/bl_archive_user.su ./Src/libs/boot/bl_user/bl_key_table.d ./Src/libs/boot/bl_user/bl_key_table.o ./Src/libs/boot/bl_user/bl_key_table.su ./Src/libs/boot/bl_user/bl_user.d ./Src/libs/boot/bl_user/bl_user.o ./Src/libs/boot/bl_user/bl_user.su ./Src/libs/boot/bl_user/bl_user_func_table.d ./Src/libs/boot/bl_user/bl_user_func_table.o ./Src/libs/boot/bl_user/bl_user_func_table.su

.PHONY: clean-Src-2f-libs-2f-boot-2f-bl_user

