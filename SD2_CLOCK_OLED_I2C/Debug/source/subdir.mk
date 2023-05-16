################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/SD2_I2C.c \
../source/SD2_board.c \
../source/display.c \
../source/font5x7.c \
../source/key.c \
../source/main.c \
../source/mef.c \
../source/mma8451.c \
../source/mtb.c \
../source/oled.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/SD2_I2C.d \
./source/SD2_board.d \
./source/display.d \
./source/font5x7.d \
./source/key.d \
./source/main.d \
./source/mef.d \
./source/mma8451.d \
./source/mtb.d \
./source/oled.d \
./source/semihost_hardfault.d 

OBJS += \
./source/SD2_I2C.o \
./source/SD2_board.o \
./source/display.o \
./source/font5x7.o \
./source/key.o \
./source/main.o \
./source/mef.o \
./source/mma8451.o \
./source/mtb.o \
./source/oled.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=0 -DCPU_MKL46Z256VLH4_cm0plus -DCPU_MKL46Z256VLH4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/SD2_I2C.d ./source/SD2_I2C.o ./source/SD2_board.d ./source/SD2_board.o ./source/display.d ./source/display.o ./source/font5x7.d ./source/font5x7.o ./source/key.d ./source/key.o ./source/main.d ./source/main.o ./source/mef.d ./source/mef.o ./source/mma8451.d ./source/mma8451.o ./source/mtb.d ./source/mtb.o ./source/oled.d ./source/oled.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

