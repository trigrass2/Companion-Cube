################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/lib/devices/CD74HC4067.cc \
../src/lib/devices/LCD.cc \
../src/lib/devices/ShiftBrite.cc \
../src/lib/devices/StrongDriveOutput.cc 

OBJS += \
./src/lib/devices/CD74HC4067.o \
./src/lib/devices/LCD.o \
./src/lib/devices/ShiftBrite.o \
./src/lib/devices/StrongDriveOutput.o 

CC_DEPS += \
./src/lib/devices/CD74HC4067.d \
./src/lib/devices/LCD.d \
./src/lib/devices/ShiftBrite.d \
./src/lib/devices/StrongDriveOutput.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/devices/%.o: ../src/lib/devices/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/rbtying/robot/firmware/Arduino-2560/Debug" -I"/home/rbtying/robot/firmware/ROS_mega/src/ros_lib" -I"/home/rbtying/robot/firmware/ROS_mega/src/lib" -I"/home/rbtying/robot/firmware/Arduino-2560" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


