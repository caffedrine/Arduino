################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/curiosul/Workspaces/Arduino/libs/Drivers/GpioBase/GpioBase.cpp 

LINK_OBJ += \
./libraries/GpioBase/GpioBase.cpp.o 

CPP_DEPS += \
./libraries/GpioBase/GpioBase.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/GpioBase/GpioBase.cpp.o: /home/curiosul/Workspaces/Arduino/libs/Drivers/GpioBase/GpioBase.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/libs/Drivers/HC595" -I"/home/curiosul/Workspaces/Arduino/libs/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/libs/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/libs/Drivers/BasicLCD" -I"/home/curiosul/Workspaces/Arduino/libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/libs/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/libs/Drivers/Printf" -I"/home/curiosul/Workspaces/Arduino/libs/StringUtil" -I"/home/curiosul/Workspaces/Arduino/libs/StringUtil/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


