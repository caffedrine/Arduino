################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../USB_to_I2C.ino 

CPP_SRCS += \
../.ino.cpp 

LINK_OBJ += \
./.ino.cpp.o 

INO_DEPS += \
./USB_to_I2C.ino.d 

CPP_DEPS += \
./.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/eightanaloginputs" -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/libraries/Wire" -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/libraries/Wire/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

USB_to_I2C.o: ../USB_to_I2C.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/eightanaloginputs" -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/libraries/Wire" -I"/home/curiosul/.tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/libraries/Wire/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


