################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.c \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.c \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.c \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.c \
../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.c 

OBJS += \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.o \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.o \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.o \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.o \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.o 

C_DEPS += \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.d \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.d \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.d \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.d \
./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/%.o Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/%.su Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/%.cyclo: ../Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/%.c Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Inc" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/interfazLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Colores" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Imagenes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-pantallaLCD-2f-juegosCaracteres

clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-pantallaLCD-2f-juegosCaracteres:
	-$(RM) ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha13.su ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha15.su ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha17.su ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha19.su ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.cyclo ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.d ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.o ./Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres/JuegoAlpha22.su

.PHONY: clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-pantallaLCD-2f-juegosCaracteres

