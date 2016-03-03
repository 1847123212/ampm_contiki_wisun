/*
 * Copyright (c) 2012, STMicroelectronics.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 */
/*---------------------------------------------------------------------------*/
/**
 * \defgroup stm32nucleo-spirit1  STM32Cube HAL APIs
 *
 * Abstraction of STM32Cube HAL APIs as per Contiki coding rules
 * @{
 *
 * \file
 * Header file for the STM32Cube HAL APIs
 */
/*---------------------------------------------------------------------------*/
#ifndef ST_LIB_H_
#define ST_LIB_H_

#include "stm32f10x_io.h"
/*---------------------------------------------------------------------------*/
/* extern global varialbles */
#define st_lib_uart_handle                       UartHandle

#define st_lib_g_x_status                        g_xStatus

#define st_lib_p_spi_handle                      pSpiHandle
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* misc */
#define st_lib_tim2_irq_handler(...)                      TIM2_IRQHandler(__VA_ARGS__)
#define st_lib_spirit_management_set_frequency_base(...)  SpiritManagementSetFrequencyBase(__VA_ARGS__)
#define st_lib_sys_tick_handler(...)                      SysTick_Handler(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* MCU_Interface.h */
#include "MCU_Interface.h"

#define st_lib_spirit_spi_init(...)              SpiritSpiInit(__VA_ARGS__)
#define st_lib_spirit_spi_read_linear_fifo(...)  SpiritSpiReadLinearFifo(__VA_ARGS__)
#define st_lib_spirit_spi_write_linear_fifo(...) SpiritSpiWriteLinearFifo(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* radio_gpio.h */
#include "radio_gpio.h"

#define st_lib_radio_gpio_interrupt_cmd(...)     RadioGpioInterruptCmd(__VA_ARGS__)
#define st_lib_radio_gpio_init(...)              RadioGpioInit(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* radio_shield_config.h */
#include "radio_shield_config.h"

#define st_lib_a_led_gpio_port                   aLED_GPIO_PORT
#define st_lib_a_led_gpio_pin                    aLED_GPIO_PIN

#define st_lib_radio_shield_led_init(...)        RadioShieldLedInit(__VA_ARGS__)
#define st_lib_radio_shield_led_off(...)         RadioShieldLedOff(__VA_ARGS__)
#define st_lib_radio_shield_led_on(...)          RadioShieldLedOn(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* radio_spi.h */
#include "radio_spi.h"

#define st_lib_radio_spi_cs_high(...)            RadioSpiCSHigh(__VA_ARGS__)
#define st_lib_radio_spi_cs_low(...)             RadioSpiCSLow(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* SPIRIT_Commands.h */
#include "SPIRIT_Commands.h"

#define st_lib_spirit_cmd_strobe_flush_rx_fifo(...) SpiritCmdStrobeFlushRxFifo(__VA_ARGS__)
#define st_lib_spirit_cmd_strobe_command(...)       SpiritCmdStrobeCommand(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* SPIRIT_Gpio.h */
#include "SPIRIT_Gpio.h"

#define st_lib_s_gpio_init                       SGpioInit

#define st_lib_spirit_gpio_init(...)             SpiritGpioInit(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32l152xe.h */
#include "stm32f10x.h"

#define st_lib_irq_n_type                        IRQn_Type
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32l1xx.h */
#include "stm32f10x.h"

#define st_lib_flag_status                       FlagStatus
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32f10x_cortex.h */
#include "core_cm3.h"

#define st_lib_hal_nvic_enable_irq(...)           NVIC_EnableIRQ(__VA_ARGS__)
#define st_lib_hal_nvic_set_priority(...)         NVIC_SetPriority(__VA_ARGS__)
#define st_lib_hal_systick_clk_source_config(...) SysTick_CLKSourceConfig(__VA_ARGS__)
#define st_lib_hal_systick_config(...)            SysTick_Config(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32f10x_rcc.h */
#include "stm32f10x_rcc.h"

#define st_lib_tim2_clk_enable(...)             // __TIM2_CLK_ENABLE(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32f10x_spi.h */
#include "stm32f10x_spi.h"

#define st_lib_spi_handle_typedef                //SPI_HandleTypeDef

#define st_lib_hal_spi_get_flag(...)             //__HAL_SPI_GET_FLAG(__VA_ARGS__)
#define st_lib_hal_spi_transmit_receive(...)     //SPI_TransmitReceive(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32f10x_tim.h */
#include "stm32f10x_tim.h"

#define st_lib_tim_handle_typedef                //TIM_HandleTypeDef
#define st_lib_tim_clock_config_typedef          //TIM_ClockConfigTypeDef
#define st_lib_tim_oc_init_typedef               //TIM_OC_InitTypeDef

#define st_lib_hal_tim_base_init(...)            //TIM_Base_Init(__VA_ARGS__)
#define st_lib_hal_tim_base_start_it(...)        //TIM_Base_Start_IT(__VA_ARGS__)
#define st_lib_hal_tim_config_clock_source(...)  //TIM_ConfigClockSource(__VA_ARGS__)
#define st_lib_hal_tim_clear_flag(...)           //__HAL_TIM_CLEAR_FLAG(__VA_ARGS__)
#define st_lib_hal_tim_clear_it(...)             //__HAL_TIM_CLEAR_IT(__VA_ARGS__)
#define st_lib_hal_tim_enable(...)               //__HAL_TIM_ENABLE(__VA_ARGS__)
#define st_lib_hal_tim_enable_it(...)            //__HAL_TIM_ENABLE_IT(__VA_ARGS__)
#define st_lib_hal_tim_oc_init(...)              //TIM_OC_Init(__VA_ARGS__)
#define st_lib_hal_tim_oc_config_channel(...)    //TIM_OC_ConfigChannel(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32f10x_uart.h */
#include "uart1.h"

#define st_lib_uart_handle_typedef               //UART_HandleTypeDef

#define st_lib_hal_uart_enable_it(...)          // __HAL_UART_ENABLE_IT(__VA_ARGS__)
#define st_lib_hal_uart_init(...)                //UART_Init(__VA_ARGS__)
#define st_lib_hal_uart_receive(...)            // UART_Receive(__VA_ARGS__)
#define st_lib_hal_uart_receive_it(...)         // UART_Receive_IT(__VA_ARGS__)
#define st_lib_hal_uart_rx_cplt_callback(...)    //UART_RxCpltCallback(__VA_ARGS__)
#define st_lib_hal_uart_transmit(...)            //UART_Transmit(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* stm32l1xx_nucleo.h */


#define st_lib_gpio_typedef                      GPIO_TypeDef
#define st_lib_gpio_port                         GPIO_PORT
#define st_lib_gpio_pin                          GPIO_PIN

#define st_lib_bsp_led_init(...)                 BSP_LED_Init(__VA_ARGS__)
#define st_lib_bsp_led_off(...)                  BSP_LED_Off(__VA_ARGS__)
#define st_lib_bsp_led_on(...)                   BSP_LED_On(__VA_ARGS__)
#define st_lib_bsp_pb_init(...)                  BSP_PB_Init(__VA_ARGS__)
#define st_lib_bsp_pb_get_state(...)             BSP_PB_GetState(__VA_ARGS__)
#define st_lib_hal_gpio_read_pin(...)            GPIO_ReadInputDataBit(__VA_ARGS__)
#define st_lib_hal_gpio_write_pin(...)           GPIO_WriteBit(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

#ifdef X_NUCLEO_IKS01A1
/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01a1.h */
#include "x_nucleo_iks01a1.h"

#define st_lib_axes_raw_typedef                  AxesRaw_TypeDef
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01a1_hum_temp.h */
#include "x_nucleo_iks01a1_hum_temp.h"

#define st_lib_bsp_hum_temp_is_initialized(...)  BSP_HUM_TEMP_isInitialized(__VA_ARGS__)
#define st_lib_bsp_hum_temp_init(...)            BSP_HUM_TEMP_Init(__VA_ARGS__)
#define st_lib_bsp_hum_temp_get_humidity(...)    BSP_HUM_TEMP_GetHumidity(__VA_ARGS__)
#define st_lib_bsp_hum_temp_get_temperature(...) BSP_HUM_TEMP_GetTemperature(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01a1_imu_6axes.h */
#include "x_nucleo_iks01a1_imu_6axes.h"

#define st_lib_bsp_imu_6axes_is_initialized(...) BSP_IMU_6AXES_isInitialized(__VA_ARGS__)
#define st_lib_bsp_imu_6axes_init(...)           BSP_IMU_6AXES_Init(__VA_ARGS__)
#define st_lib_bsp_imu_6axes_g_get_axes_raw(...) BSP_IMU_6AXES_G_GetAxesRaw(__VA_ARGS__)
#define st_lib_bsp_imu_6axes_x_get_axes_raw(...) BSP_IMU_6AXES_X_GetAxesRaw(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01a1_magneto.h */
#include "x_nucleo_iks01a1_magneto.h"

#define st_lib_bsp_magneto_m_get_axes_raw(...)   BSP_MAGNETO_M_GetAxesRaw(__VA_ARGS__)
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* x_nucleo_iks01a1_pressure.h */
#include "x_nucleo_iks01a1_pressure.h"

#define st_lib_bsp_pressure_init(...)            BSP_PRESSURE_Init(__VA_ARGS__)
#define st_lib_bsp_pressure_get_pressure(...)    BSP_PRESSURE_GetPressure(__VA_ARGS__)
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#endif /*X_NUCLEO_IKS01A1*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#endif /*ST_LIB_H_*/
/*---------------------------------------------------------------------------*/
/** @} */
