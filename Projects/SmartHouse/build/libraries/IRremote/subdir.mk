################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/IRremote.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/irPronto.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/irRecv.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/irSend.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Aiwa.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Denon.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Dish.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_JVC.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_LG.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Mitsubishi.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_NEC.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Panasonic.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_RC5_RC6.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Samsung.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Sanyo.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Sharp.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Sony.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Template.cpp \
/home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Whynter.cpp 

LINK_OBJ += \
./libraries/IRremote/IRremote.cpp.o \
./libraries/IRremote/irPronto.cpp.o \
./libraries/IRremote/irRecv.cpp.o \
./libraries/IRremote/irSend.cpp.o \
./libraries/IRremote/ir_Aiwa.cpp.o \
./libraries/IRremote/ir_Denon.cpp.o \
./libraries/IRremote/ir_Dish.cpp.o \
./libraries/IRremote/ir_JVC.cpp.o \
./libraries/IRremote/ir_LG.cpp.o \
./libraries/IRremote/ir_Mitsubishi.cpp.o \
./libraries/IRremote/ir_NEC.cpp.o \
./libraries/IRremote/ir_Panasonic.cpp.o \
./libraries/IRremote/ir_RC5_RC6.cpp.o \
./libraries/IRremote/ir_Samsung.cpp.o \
./libraries/IRremote/ir_Sanyo.cpp.o \
./libraries/IRremote/ir_Sharp.cpp.o \
./libraries/IRremote/ir_Sony.cpp.o \
./libraries/IRremote/ir_Template.cpp.o \
./libraries/IRremote/ir_Whynter.cpp.o 

CPP_DEPS += \
./libraries/IRremote/IRremote.cpp.d \
./libraries/IRremote/irPronto.cpp.d \
./libraries/IRremote/irRecv.cpp.d \
./libraries/IRremote/irSend.cpp.d \
./libraries/IRremote/ir_Aiwa.cpp.d \
./libraries/IRremote/ir_Denon.cpp.d \
./libraries/IRremote/ir_Dish.cpp.d \
./libraries/IRremote/ir_JVC.cpp.d \
./libraries/IRremote/ir_LG.cpp.d \
./libraries/IRremote/ir_Mitsubishi.cpp.d \
./libraries/IRremote/ir_NEC.cpp.d \
./libraries/IRremote/ir_Panasonic.cpp.d \
./libraries/IRremote/ir_RC5_RC6.cpp.d \
./libraries/IRremote/ir_Samsung.cpp.d \
./libraries/IRremote/ir_Sanyo.cpp.d \
./libraries/IRremote/ir_Sharp.cpp.d \
./libraries/IRremote/ir_Sony.cpp.d \
./libraries/IRremote/ir_Template.cpp.d \
./libraries/IRremote/ir_Whynter.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/IRremote/IRremote.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/IRremote.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/irPronto.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/irPronto.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/irRecv.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/irRecv.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/irSend.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/irSend.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Aiwa.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Aiwa.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Denon.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Denon.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Dish.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Dish.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_JVC.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_JVC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_LG.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_LG.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Mitsubishi.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Mitsubishi.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_NEC.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_NEC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Panasonic.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Panasonic.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_RC5_RC6.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_RC5_RC6.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Samsung.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Samsung.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Sanyo.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Sanyo.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Sharp.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Sharp.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Sony.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Sony.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Template.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Template.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/IRremote/ir_Whynter.cpp.o: /home/curiosul/Workspaces/Arduino/Libs/IRremote/ir_Whynter.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/curiosul/.Tools/IDEs/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/cores/arduino" -I"/home/curiosul/.Tools/IDEs/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.19/variants/mega" -I"/home/curiosul/Workspaces/Arduino/Libs/IRremote" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal" -I"/home/curiosul/Workspaces/Arduino/Libs/LiquidCrystal/src" -I"/home/curiosul/Workspaces/Arduino/Drivers/X113647Stepper" -I"/home/curiosul/Workspaces/Arduino/Libs/TimerOne" -I"/home/curiosul/Workspaces/Arduino/Drivers/LED" -I"/home/curiosul/Workspaces/Arduino/Drivers/HAL" -I"/home/curiosul/Workspaces/Arduino/Drivers/GpioBase" -I"/home/curiosul/Workspaces/Arduino/Drivers/BasicLCD" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


