################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.c \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.c 

OBJS += \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.o \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.o 

C_DEPS += \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.d \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/%.o Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/%.su Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/%.cyclo: ../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/%.c Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Inc" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/interfazLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Colores" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Imagenes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-pantallaLCD-2f-Componentes

clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-pantallaLCD-2f-Componentes:
	-$(RM) ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/Componentes.su ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes/graph.su

.PHONY: clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-pantallaLCD-2f-Componentes

