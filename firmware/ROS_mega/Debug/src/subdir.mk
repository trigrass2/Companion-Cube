################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/Main.cc 

OBJS += \
./src/Main.o 

CC_DEPS += \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/rbtying/robot/firmware/Arduino1.0/Debug" -I"/home/rbtying/robot/firmware/Arduino1.0/EEPROM" -I"/home/rbtying/robot/firmware/Arduino1.0/Ethernet" -I"/home/rbtying/robot/firmware/Arduino1.0/Firmata" -I"/home/rbtying/robot/firmware/Arduino1.0/LiquidCrystal" -I"/home/rbtying/robot/firmware/Arduino1.0/SD" -I"/home/rbtying/robot/firmware/Arduino1.0/Servo" -I"/home/rbtying/robot/firmware/Arduino1.0/SoftwareSerial" -I"/home/rbtying/robot/firmware/Arduino1.0/SPI" -I"/home/rbtying/robot/firmware/Arduino1.0/Stepper" -I"/home/rbtying/robot/firmware/Arduino1.0/Wire" -I"/home/rbtying/robot/firmware/ROS_mega/src/ros_lib" -I"/home/rbtying/robot/firmware/ROS_mega/src/lib" -I"/home/rbtying/robot/firmware/Arduino1.0" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


