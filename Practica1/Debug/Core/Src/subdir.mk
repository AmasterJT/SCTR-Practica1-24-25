################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/freertos.c \
../Core/Src/ili9341.c \
../Core/Src/interfazLCD.c \
../Core/Src/main.c \
../Core/Src/pantallaLCD.c \
../Core/Src/stm32f429i_discovery.c \
../Core/Src/stm32f429i_discovery_io.c \
../Core/Src/stm32f429i_discovery_lcd.c \
../Core/Src/stm32f429i_discovery_sdram.c \
../Core/Src/stm32f429i_discovery_ts.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/stmpe811.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/freertos.o \
./Core/Src/ili9341.o \
./Core/Src/interfazLCD.o \
./Core/Src/main.o \
./Core/Src/pantallaLCD.o \
./Core/Src/stm32f429i_discovery.o \
./Core/Src/stm32f429i_discovery_io.o \
./Core/Src/stm32f429i_discovery_lcd.o \
./Core/Src/stm32f429i_discovery_sdram.o \
./Core/Src/stm32f429i_discovery_ts.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/stmpe811.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/freertos.d \
./Core/Src/ili9341.d \
./Core/Src/interfazLCD.d \
./Core/Src/main.d \
./Core/Src/pantallaLCD.d \
./Core/Src/stm32f429i_discovery.d \
./Core/Src/stm32f429i_discovery_io.d \
./Core/Src/stm32f429i_discovery_lcd.d \
./Core/Src/stm32f429i_discovery_sdram.d \
./Core/Src/stm32f429i_discovery_ts.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/stmpe811.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/ili9341.cyclo ./Core/Src/ili9341.d ./Core/Src/ili9341.o ./Core/Src/ili9341.su ./Core/Src/interfazLCD.cyclo ./Core/Src/interfazLCD.d ./Core/Src/interfazLCD.o ./Core/Src/interfazLCD.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pantallaLCD.cyclo ./Core/Src/pantallaLCD.d ./Core/Src/pantallaLCD.o ./Core/Src/pantallaLCD.su ./Core/Src/stm32f429i_discovery.cyclo ./Core/Src/stm32f429i_discovery.d ./Core/Src/stm32f429i_discovery.o ./Core/Src/stm32f429i_discovery.su ./Core/Src/stm32f429i_discovery_io.cyclo ./Core/Src/stm32f429i_discovery_io.d ./Core/Src/stm32f429i_discovery_io.o ./Core/Src/stm32f429i_discovery_io.su ./Core/Src/stm32f429i_discovery_lcd.cyclo ./Core/Src/stm32f429i_discovery_lcd.d ./Core/Src/stm32f429i_discovery_lcd.o ./Core/Src/stm32f429i_discovery_lcd.su ./Core/Src/stm32f429i_discovery_sdram.cyclo ./Core/Src/stm32f429i_discovery_sdram.d ./Core/Src/stm32f429i_discovery_sdram.o ./Core/Src/stm32f429i_discovery_sdram.su ./Core/Src/stm32f429i_discovery_ts.cyclo ./Core/Src/stm32f429i_discovery_ts.d ./Core/Src/stm32f429i_discovery_ts.o ./Core/Src/stm32f429i_discovery_ts.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/stmpe811.cyclo ./Core/Src/stmpe811.d ./Core/Src/stmpe811.o ./Core/Src/stmpe811.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

