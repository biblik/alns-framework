################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/localsearch/SimpleLocalSearchManager.cpp 

OBJS += \
./trunk/src/localsearch/SimpleLocalSearchManager.o 

CPP_DEPS += \
./trunk/src/localsearch/SimpleLocalSearchManager.d 


# Each subdirectory must supply rules for building sources it contributes
trunk/src/localsearch/%.o: ../src/localsearch/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/renaud/lib/tinyxml/tinyxml -O3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


