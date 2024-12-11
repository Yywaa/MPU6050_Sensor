################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MPU6050_Read.c 

OBJS += \
./src/MPU6050_Read.o 

C_DEPS += \
./src/MPU6050_Read.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\BeagleboneBlack\BBBWorkSpace\MPU6050_Read\MPU6050_Dev\Inc" -include"D:\BeagleboneBlack\BBBWorkSpace\MPU6050_Read\MPU6050_Dev\Inc\MPU6050.h" -include"D:\BeagleboneBlack\BBBWorkSpace\MPU6050_Read\MPU6050_Dev\Src\MPU6050.c" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


