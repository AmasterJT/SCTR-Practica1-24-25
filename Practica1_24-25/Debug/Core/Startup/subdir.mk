################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f429zitx.s 

OBJS += \
./Core/Startup/startup_stm32f429zitx.o 

S_DEPS += \
./Core/Startup/startup_stm32f429zitx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Inc" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/Dependencias/Src" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/interfazLCD" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Colores" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Componentes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/Imagenes" -I"D:/@@universidad/- Clase cursos academicos/4to - Cuarto curso/Sistemas de control a tiempo real/Praticas/@@Practicas 24-25/Practica1_24-25/Practica1_23-24/Middlewares/STM32F429I-DISC1-LCD/pantallaLCD/juegosCaracteres" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f429zitx.d ./Core/Startup/startup_stm32f429zitx.o

.PHONY: clean-Core-2f-Startup

