################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/wordstats.cpp 

OBJS += \
./source/wordstats.o 

CPP_DEPS += \
./source/wordstats.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/takis/Identities/takiszourntos/accelerated-cpp/ese2025_homework/proj_tz_ese2025_hwk_1/my_includes" -include"/home/takis/Identities/takiszourntos/accelerated-cpp/ese2025_homework/proj_tz_ese2025_hwk_1/my_includes/wordy.h" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


