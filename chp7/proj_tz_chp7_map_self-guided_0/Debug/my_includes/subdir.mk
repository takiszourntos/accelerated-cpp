################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../my_includes/agentlib.cpp 

OBJS += \
./my_includes/agentlib.o 

CPP_DEPS += \
./my_includes/agentlib.d 


# Each subdirectory must supply rules for building sources it contributes
my_includes/%.o: ../my_includes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/takis/Identities/takiszourntos/accelerated-cpp/chp7/proj_tz_chp7_map_self-guided_0/my_includes" -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


