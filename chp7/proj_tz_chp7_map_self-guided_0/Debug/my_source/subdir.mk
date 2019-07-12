################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../my_source/agent_mapper.cpp \
../my_source/scratch.cpp 

OBJS += \
./my_source/agent_mapper.o \
./my_source/scratch.o 

CPP_DEPS += \
./my_source/agent_mapper.d \
./my_source/scratch.d 


# Each subdirectory must supply rules for building sources it contributes
my_source/%.o: ../my_source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/takis/Identities/proftakis/accelerated-cpp/chp7/proj_tz_chp7_map_self-guided_0/my_includes" -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


