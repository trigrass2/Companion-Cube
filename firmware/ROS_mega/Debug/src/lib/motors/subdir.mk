################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lib/motors/RoboClaw.cpp 

CC_SRCS += \
../src/lib/motors/Sabertooth.cc \
../src/lib/motors/ServoMotor.cc 

OBJS += \
./src/lib/motors/RoboClaw.o \
./src/lib/motors/Sabertooth.o \
./src/lib/motors/ServoMotor.o 

CC_DEPS += \
./src/lib/motors/Sabertooth.d \
./src/lib/motors/ServoMotor.d 

CPP_DEPS += \
./src/lib/motors/RoboClaw.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/motors/%.o: ../src/lib/motors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/rbtying/robot/firmware/Arduino-2560/Debug" -I"/home/rbtying/robot/firmware/ROS_mega/src/ros_lib" -I"/home/rbtying/robot/firmware/ROS_mega/src/lib" -I"/home/rbtying/robot/firmware/Arduino-2560" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/lib/motors/%.o: ../src/lib/motors/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/rbtying/robot/firmware/Arduino-2560/Debug" -I"/home/rbtying/robot/firmware/ROS_mega/src/ros_lib" -I"/home/rbtying/robot/firmware/ROS_mega/src/lib" -I"/home/rbtying/robot/firmware/Arduino-2560" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


