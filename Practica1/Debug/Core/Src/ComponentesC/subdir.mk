################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ComponentesC/Componentes.c 

OBJS += \
./Core/Src/ComponentesC/Componentes.o 

C_DEPS += \
./Core/Src/ComponentesC/Componentes.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ComponentesC/%.o Core/Src/ComponentesC/%.su Core/Src/ComponentesC/%.cyclo: ../Core/Src/ComponentesC/%.c Core/Src/ComponentesC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ComponentesC

clean-Core-2f-Src-2f-ComponentesC:
	-$(RM) ./Core/Src/ComponentesC/Componentes.cyclo ./Core/Src/ComponentesC/Componentes.d ./Core/Src/ComponentesC/Componentes.o ./Core/Src/ComponentesC/Componentes.su

.PHONY: clean-Core-2f-Src-2f-ComponentesC

