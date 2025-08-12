################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/st7735/fonts.c \
../Drivers/st7735/st7735.c 

OBJS += \
./Drivers/st7735/fonts.o \
./Drivers/st7735/st7735.o 

C_DEPS += \
./Drivers/st7735/fonts.d \
./Drivers/st7735/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/st7735/%.o Drivers/st7735/%.su Drivers/st7735/%.cyclo: ../Drivers/st7735/%.c Drivers/st7735/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/amer/Work/Elebel/11aug25/code/teseST7735TFT_Proteus/Drivers/st7735" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-st7735

clean-Drivers-2f-st7735:
	-$(RM) ./Drivers/st7735/fonts.cyclo ./Drivers/st7735/fonts.d ./Drivers/st7735/fonts.o ./Drivers/st7735/fonts.su ./Drivers/st7735/st7735.cyclo ./Drivers/st7735/st7735.d ./Drivers/st7735/st7735.o ./Drivers/st7735/st7735.su

.PHONY: clean-Drivers-2f-st7735

