################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include core/core/libb64/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/arduino.ar \

ELF += \
DRV8835_ESP32_MotorsDriver.elf \

HEX += \
DRV8835_ESP32_MotorsDriver.hex \


# All Target
all: DRV8835_ESP32_MotorsDriver

# Tool invocations
DRV8835_ESP32_MotorsDriver: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/curiosul/Arduino/hardware/espressif/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-size" -A "/home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/DRV8835_ESP32_MotorsDriver.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/curiosul/Arduino/hardware/espressif/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-ar" cru "/home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/arduino.ar"    /home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

DRV8835_ESP32_MotorsDriver.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/curiosul/Arduino/hardware/espressif/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc" -nostdlib "-L/home/curiosul/Arduino/hardware/espressif/esp32/tools/sdk/lib" "-L/home/curiosul/Arduino/hardware/espressif/esp32/tools/sdk/ld" -T esp32_out.ld -T esp32.common.ld -T esp32.rom.ld -T esp32.peripherals.ld -u call_user_start_cpu0 -Wl,--gc-sections -Wl,-static -Wl,--undefined=uxTopUsedPriority -Wl,--start-group   $(LINK_OBJ) $(AR)  "/home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/arduino.ar" -lgcc -lstdc++ -lapp_update -lbootloader_support -lbt -lbtdm_app -lc -lc_nano -lcoap -lcoexist -lcore -lcxx -ldriver -lesp32 -lethernet -lexpat -lfatfs -lfreertos -lhal -ljsmn -ljson -llog -llwip -lm -lmbedtls -lmdns -lmicro-ecc -lnet80211 -lnewlib -lnghttp -lnvs_flash -lopenssl -lphy -lpp -lrtc -lsdmmc -lsmartconfig -lsoc -lspi_flash -ltcpip_adapter -lulp -lvfs -lwear_levelling -lwpa -lwpa2 -lwpa_supplicant -lwps -lxtensa-debug-module -Wl,--end-group -Wl,-EL -o "/home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/DRV8835_ESP32_MotorsDriver.elf" /home/curiosul/Workspaces/sloeber/DRV8835_ESP32_MotorsDriver/Release/arduino.ar
	@echo 'Finished building: $@'
	@echo ' '

DRV8835_ESP32_MotorsDriver.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
