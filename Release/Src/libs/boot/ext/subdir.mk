################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Src/libs/boot/ext/bl_vectors.s 

OBJS += \
./Src/libs/boot/ext/bl_vectors.o 

S_DEPS += \
./Src/libs/boot/ext/bl_vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Src/libs/boot/ext/%.o: ../Src/libs/boot/ext/%.s Src/libs/boot/ext/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -flto -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Src-2f-libs-2f-boot-2f-ext

clean-Src-2f-libs-2f-boot-2f-ext:
	-$(RM) ./Src/libs/boot/ext/bl_vectors.d ./Src/libs/boot/ext/bl_vectors.o

.PHONY: clean-Src-2f-libs-2f-boot-2f-ext

