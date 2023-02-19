cmake_minimum_required(VERSION 3.15.3)

project(freertos_demo)

enable_language(C ASM)
#set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


set(FREERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Middleware/Third_Party/FreeRTOS")
set(SEGGER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Middleware/Third_Party/SEGGER")


set(STM32CUBEMX_GENERATED_FILES

        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c
        src/Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c

        ${FREERTOS_DIR}/Source/croutine.c
        ${FREERTOS_DIR}/Source/event_groups.c
        ${FREERTOS_DIR}/Source/list.c
        ${FREERTOS_DIR}/Source/queue.c
        ${FREERTOS_DIR}/Source/stream_buffer.c
        ${FREERTOS_DIR}/Source/tasks.c
        ${FREERTOS_DIR}/Source/timers.c
        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM7/r0p1/port.c
        ${FREERTOS_DIR}/Source/portable/MemMang/heap_4.c
        ${FREERTOS_DIR}/Source/CMSIS_RTOS_V2/cmsis_os2.c

        ${SEGGER_DIR}/SEGGER_RTT.c
        ${SEGGER_DIR}/SEGGER_RTT_ASM_ARMv7M.S
        ${SEGGER_DIR}/SEGGER_RTT_printf.c
        ${SEGGER_DIR}/SEGGER_RTT_Syscalls_GCC.c
        ${SEGGER_DIR}/SEGGER_RTT_Syscalls_IAR.c
        ${SEGGER_DIR}/SEGGER_RTT_Syscalls_KEIL.c
        ${SEGGER_DIR}/SEGGER_RTT_Syscalls_SES.c
        ${SEGGER_DIR}/SEGGER_SYSVIEW.c
        ${SEGGER_DIR}/SEGGER_SYSVIEW_Config_FreeRTOS.c
        ${SEGGER_DIR}/SEGGER_SYSVIEW_FreeRTOS.c

        src/BSP/Nucleo_F767ZI_Init.c

        src/Inc/main.h
        src/Inc/stm32f7xx_hal_conf.h
        src/Inc/stm32f7xx_it.h

        src/Src/main.c
        src/Src/stm32f7xx_hal_msp.c
        src/Src/stm32f7xx_it.c
        src/Src/system_stm32f7xx.c
        src/Src/syscalls.c

        src/startup/startup_stm32f767xx.s)

set(EXECUTABLE ${PROJECT_NAME}.out)

add_executable(${EXECUTABLE} ${STM32CUBEMX_GENERATED_FILES})

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DUSE_HAL_DRIVER
        -DSTM32F767xx
        -DUSE_FULL_ASSERT=1
        "-D_packed=__attribute_((_packed_))"
        "-D_weak=__attribute_((weak))"
        )

target_include_directories(${EXECUTABLE} PRIVATE
        src/Inc
        src/Drivers/STM32F7xx_HAL_Driver/Inc
        src/Drivers/CMSIS/Device/ST/STM32F7xx/Include
        src/Drivers/CMSIS/Include

        src/BSP

        src/Middleware/Third_Party/SEGGER

        ${FREERTOS_DIR}/Source/include
        ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM7/r0p1
        ${FREERTOS_DIR}/Source/CMSIS_RTOS_V2
        )

target_compile_options(${EXECUTABLE} PRIVATE
-mcpu=cortex-m7 -std=gnu11 -g3 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb 
        # -mcpu=cortex-m7
        # -std=gnu11 
        # -g3
        # -c
        # #-mlittle-endian
        # -mthumb
        # -mfpu=fpv5-sp-d16
        # -mfloat-abi=hard

        # -fdata-sections
        # -ffunction-sections

        # -Wall

        # $<$<CONFIG:Debug>:-Og>
        )

target_link_options(${EXECUTABLE} PRIVATE
-mcpu=cortex-m7 -T${CMAKE_SOURCE_DIR}/src/STM32F767ZI_FLASH.ld --specs=nosys.specs -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
-z muldefs

        # -T${CMAKE_SOURCE_DIR}/src/STM32F767ZI_FLASH.ld
        # -mcpu=cortex-m7
        # -mlittle-endian
        # -mthumb
        # -mfpu=fpv5-sp-d16
        # -mfloat-abi=hard
        # -specs=nosys.specs
        # -lc
        # -lm
        # -lnosys
        # -Wl,-Map=${PROJECT_NAME}.map,--cref
        # -Wl,--gc-sections
        )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE})

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)