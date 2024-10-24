################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.c \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.c \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.c \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.c \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.c \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.c \
../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.c 

OBJS += \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.o \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.o \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.o \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.o \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.o \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.o \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.o 

C_DEPS += \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.d \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.d \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.d \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.d \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.d \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.d \
./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/%.o Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/%.su Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/%.cyclo: ../Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/%.c Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Inc" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/interfazLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Colores" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Imagenes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-Dependencias-2f-Src

clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-Dependencias-2f-Src:
	-$(RM) ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/ili9341.su ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery.su ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_io.su ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_lcd.su ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_sdram.su ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stm32f429i_discovery_ts.su ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.cyclo ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.d ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.o ./Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src/stmpe811.su

.PHONY: clean-Middlewares-2f-STM32F429I-2d-DISC1-2d-LCD-2f-Dependencias-2f-Src

