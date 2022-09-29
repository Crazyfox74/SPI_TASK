################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../port/STM32/startup_stm32l412cbtx.s 

OBJS += \
./port/STM32/startup_stm32l412cbtx.o 

S_DEPS += \
./port/STM32/startup_stm32l412cbtx.d 


# Each subdirectory must supply rules for building sources it contributes
port/STM32/%.o: ../port/STM32/%.s port/STM32/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-port-2f-STM32

clean-port-2f-STM32:
	-$(RM) ./port/STM32/startup_stm32l412cbtx.d ./port/STM32/startup_stm32l412cbtx.o

.PHONY: clean-port-2f-STM32

