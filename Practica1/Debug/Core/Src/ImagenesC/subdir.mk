################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ImagenesC/FondoImagen240x320.c \
../Core/Src/ImagenesC/imagenAlarma11_70x70.c \
../Core/Src/ImagenesC/imagenBotonNo50x50.c \
../Core/Src/ImagenesC/imagenCircuito240x320.c 

OBJS += \
./Core/Src/ImagenesC/FondoImagen240x320.o \
./Core/Src/ImagenesC/imagenAlarma11_70x70.o \
./Core/Src/ImagenesC/imagenBotonNo50x50.o \
./Core/Src/ImagenesC/imagenCircuito240x320.o 

C_DEPS += \
./Core/Src/ImagenesC/FondoImagen240x320.d \
./Core/Src/ImagenesC/imagenAlarma11_70x70.d \
./Core/Src/ImagenesC/imagenBotonNo50x50.d \
./Core/Src/ImagenesC/imagenCircuito240x320.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ImagenesC/%.o Core/Src/ImagenesC/%.su Core/Src/ImagenesC/%.cyclo: ../Core/Src/ImagenesC/%.c Core/Src/ImagenesC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ImagenesC

clean-Core-2f-Src-2f-ImagenesC:
	-$(RM) ./Core/Src/ImagenesC/FondoImagen240x320.cyclo ./Core/Src/ImagenesC/FondoImagen240x320.d ./Core/Src/ImagenesC/FondoImagen240x320.o ./Core/Src/ImagenesC/FondoImagen240x320.su ./Core/Src/ImagenesC/imagenAlarma11_70x70.cyclo ./Core/Src/ImagenesC/imagenAlarma11_70x70.d ./Core/Src/ImagenesC/imagenAlarma11_70x70.o ./Core/Src/ImagenesC/imagenAlarma11_70x70.su ./Core/Src/ImagenesC/imagenBotonNo50x50.cyclo ./Core/Src/ImagenesC/imagenBotonNo50x50.d ./Core/Src/ImagenesC/imagenBotonNo50x50.o ./Core/Src/ImagenesC/imagenBotonNo50x50.su ./Core/Src/ImagenesC/imagenCircuito240x320.cyclo ./Core/Src/ImagenesC/imagenCircuito240x320.d ./Core/Src/ImagenesC/imagenCircuito240x320.o ./Core/Src/ImagenesC/imagenCircuito240x320.su

.PHONY: clean-Core-2f-Src-2f-ImagenesC

