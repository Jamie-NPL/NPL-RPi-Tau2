# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./src/tau2_capture.cpp 

OBJS += \
./src/tau2_capture.o 

CPP_DEPS += \
./src/tau2_capture.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_UNIX_ -D_LINUX_ -I/home/jamie/Documents/NPL/NPL-Rpi-Tau2/include -I/opt/pleora/ebus_sdk/Ubuntu-x86_64/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


