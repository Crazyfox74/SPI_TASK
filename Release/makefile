################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include port/STM32/STM32L4xx_HAL_Driver/Src/subdir.mk
-include port/STM32/CMSIS/Src/subdir.mk
-include port/STM32/subdir.mk
-include Src/utils/subdir.mk
-include Src/tests/subdir.mk
-include Src/storage/subdir.mk
-include Src/radio/subdir.mk
-include Src/perif/subdir.mk
-include Src/ncp_ex/subdir.mk
-include Src/libs/ufifo/subdir.mk
-include Src/libs/radio_lib/mathlib/subdir.mk
-include Src/libs/radio_lib/subdir.mk
-include Src/libs/boot/ext/subdir.mk
-include Src/libs/boot/bl_user/subdir.mk
-include Src/libs/axsem/code/subdir.mk
-include Src/libs/axsem/subdir.mk
-include Src/gui/subdir.mk
-include Src/flow/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := mm215_gcc
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
mm215_gcc.elf \

MAP_FILES += \
mm215_gcc.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
mm215_gcc.list \

OBJCOPY_HEX += \
mm215_gcc.hex \


# All Target
all: main-build

# Main-build Target
main-build: mm215_gcc.elf secondary-outputs

# Tool invocations
mm215_gcc.elf mm215_gcc.map: $(OBJS) $(USER_OBJS) D:\2021_1\Cube\mm215_gcc\STM32L412CBUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "mm215_gcc.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\2021_1\Cube\mm215_gcc\STM32L412CBUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="mm215_gcc.map" -Wl,--gc-sections -static -L"D:\2021_1\Cube\mm215_gcc\port\STM32\CMSIS\Lib\GCC" -L"D:\2021_1\Cube\mm215_gcc\Src\libs\boot\ext" -fno-zero-initialized-in-bss --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

mm215_gcc.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "mm215_gcc.list"
	@echo 'Finished building: $@'
	@echo ' '

mm215_gcc.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "mm215_gcc.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout mm215_gcc.elf mm215_gcc.hex mm215_gcc.list mm215_gcc.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
