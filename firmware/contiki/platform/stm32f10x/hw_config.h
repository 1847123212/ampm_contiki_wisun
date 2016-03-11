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
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H
/*---------------------------------------------------------------------------*/

#include "stm32f10x.h"
#include <stdint.h>
 #include "stm32l-spirit1-config.h"
 #include "exti.h"
/*---------------------------------------------------------------------------*/
#define UART_RxBufferSize    512
/*---------------------------------------------------------------------------*/
#define I2Cx                            I2C1
#define I2Cx_CLK_ENABLE()               __I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
/*---------------------------------------------------------------------------*/
#define I2Cx_FORCE_RESET()              __I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __I2C1_RELEASE_RESET()
/*---------------------------------------------------------------------------*/
/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

#define I2Cx                            I2C1
#define I2Cx_CLK_ENABLE()               __I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()

#define I2Cx_FORCE_RESET()              __I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __USART2_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                __DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA

#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

#define USARTx_TX_AF                     GPIO_AF7_USART2
#define USARTx_RX_AF                     GPIO_AF7_USART2

/* Enable sensor mask */
#define PRESSURE_SENSOR                         0x00000001
#define TEMPERATURE_SENSOR                      0x00000002
#define HUMIDITY_SENSOR                         0x00000004
#define UV_SENSOR                               0x00000008
#define ACCELEROMETER_SENSOR                    0x00000010
#define GYROSCOPE_SENSOR                        0x00000020
#define MAGNETIC_SENSOR                         0x00000040

#define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
#define FLASH_SIZE                        (0x20000)  /* 128 KBytes */

#define ApplicationAddress    0x8003000
#define EEPROM_START_ADDRESS ((uint32_t)(0x8060000 - PAGE_SIZE*2)) /* EEPROM emulation start address: after 64KByte of used Flash memory */

#define CONFIG_AREA_SIZE		0x400
#define CONFIG_AREA_START ((uint32_t)(0x08000000 + FLASH_SIZE - PAGE_SIZE*(CONFIG_AREA_SIZE/PAGE_SIZE)))		



/*
	PRIORITY CONFIG
*/

#define GSM_PRIORITY  				1
#define RTC_ALARM_PRIORITY		1
#define TICK_PRIORITY 				1
#define RTCALARM_PRIORITY 		4
#define MODEMRI_PRIORITY 			1
#define TMR2_PRIORITY					4


#define LED1_PORT	GPIOB
#define LED1_PIN	GPIO_BSRR_BS6
#define LED1_SET_OUTPUT		LED1_PORT->CRL	&= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6); LED1_PORT->CRL	|= (GPIO_CRL_MODE6_0)
#define LED1_SET_INPUT		LED1_PORT->CRL	&= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6); LED1_PORT->CRL	|= (GPIO_CRL_CNF6_0)
#define LED1_PIN_SET					LED1_PORT->BRR = LED1_PIN
#define LED1_PIN_CLR					LED1_PORT->BSRR = LED1_PIN
#define LED1_PIN_GET() 	(LED1_PORT->IDR & LED1_PIN)

#define LED2_PORT	GPIOB
#define LED2_PIN	GPIO_BSRR_BS7
#define LED2_SET_OUTPUT		LED2_PORT->CRL	&= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7); LED2_PORT->CRL	|= (GPIO_CRL_MODE7_0)
#define LED2_SET_INPUT		LED2_PORT->CRL	&= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7); LED2_PORT->CRL	|= (GPIO_CRL_CNF7_0)
#define LED2_PIN_SET					LED2_PORT->BRR = LED2_PIN
#define LED2_PIN_CLR					LED2_PORT->BSRR = LED2_PIN
#define LED2_PIN_GET() 	(LED2_PORT->IDR & LED2_PIN)


#define CC1200_CSN_PORT_BASE	GPIOA
#define CC1200_CSN_PIN_MASK	GPIO_BSRR_BS4
#define CC1200_CSN_OUTPUT		CC1200_CSN_PORT_BASE->CRL	&= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4); CC1200_CSN_PORT_BASE->CRL	|= (GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1)
#define CC1200_CSN_INPUT		CC1200_CSN_PORT_BASE->CRL	&= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
#define CC1200_CSN_CLR					CC1200_CSN_PORT_BASE->BRR = CC1200_CSN_PIN_MASK
#define CC1200_CSN_SET					CC1200_CSN_PORT_BASE->BSRR = CC1200_CSN_PIN_MASK

#define CC1200_GDO2_PORT_BASE	GPIOB
#define CC1200_GDO2_PIN_MASK	GPIO_BSRR_BS0
#define CC1200_GDO2_INPUT_FLOAT		CC1200_GDO2_PORT_BASE->CRL	&= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);CC1200_GDO2_PORT_BASE->CRL	|=  GPIO_CRL_CNF0_0
#define CC1200_GDO2_GET() 	(CC1200_GDO2_PORT_BASE->IDR & CC1200_GDO2_PIN_MASK)
#define	CC1200_GDO2_INT_EN \
		NVIC_SetPriority(EXTI0_IRQn, ((0x01<<3)| 1));\
		NVIC_EnableIRQ(EXTI0_IRQn)
#define	CC1200_GDO2_INT_RISING EXTI->PR = EXTI_Line0;\
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB; /*set pin to use*/ \
		EXTI->IMR       &= ~EXTI_Line0;/*mask interrupt*/\
    EXTI->EMR       &= ~EXTI_Line0; /*mask event*/\
		EXTI->IMR       |= 	EXTI_Line0; /*mask interrupt*/\
		EXTI->EMR       |= EXTI_Line0; /*mask event*/\
    EXTI->RTSR      |= EXTI_Line0; /*clear rising edge*/\
    EXTI->FTSR      &= ~EXTI_Line0
#define	CC1200_GDO2_INT_FALLING EXTI->PR = EXTI_Line0;\
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB; /*set pin to use*/ \
		EXTI->IMR       &= ~EXTI_Line0;/*mask interrupt*/\
    EXTI->EMR       &= ~EXTI_Line0; /*mask event*/\
		EXTI->IMR       |= 	EXTI_Line0; /*mask interrupt*/\
		EXTI->EMR       |= EXTI_Line0; /*mask event*/\
    EXTI->RTSR      &= ~EXTI_Line0; /*clear rising edge*/\
    EXTI->FTSR      |= EXTI_Line0
#define	CC1200_GDO2_INT_DIS	NVIC_DisableIRQ(EXTI0_IRQn)

#define CC1200_GDO0_PORT_BASE	GPIOA
#define CC1200_GDO0_PIN_MASK	GPIO_BSRR_BS3
#define CC1200_GDO0_INPUT_FLOAT		CC1200_GDO0_PORT_BASE->CRL	&= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);CC1200_GDO0_PORT_BASE->CRL	|=  GPIO_CRL_CNF3_0
#define CC1200_GDO0_GET() 	(CC1200_GDO0_PORT_BASE->IDR & CC1200_GDO0_PIN_MASK)
#define	CC1200_GDO0_INT_EN \
		NVIC_SetPriority(EXTI3_IRQn, ((0x01<<3)| 1));\
		NVIC_EnableIRQ(EXTI3_IRQn)
#define	CC1200_GDO0_INT_RISING EXTI->PR = EXTI_Line3;\
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI3_PA; /*set pin to use*/ \
		EXTI->IMR       &= ~EXTI_Line3;/*mask interrupt*/\
    EXTI->EMR       &= ~EXTI_Line3; /*mask event*/\
		EXTI->IMR       |= 	EXTI_Line3; /*mask interrupt*/\
		EXTI->EMR       |= EXTI_Line3; /*mask event*/\
    EXTI->RTSR      |= EXTI_Line3; /*clear rising edge*/\
    EXTI->FTSR      &= ~EXTI_Line3
#define	CC1200_GDO0_INT_FALLING EXTI->PR = EXTI_Line3;\
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI3_PA; /*set pin to use*/ \
		EXTI->IMR       &= ~EXTI_Line3;/*mask interrupt*/\
    EXTI->EMR       &= ~EXTI_Line3; /*mask event*/\
		EXTI->IMR       |= 	EXTI_Line3; /*mask interrupt*/\
		EXTI->EMR       |= EXTI_Line3; /*mask event*/\
    EXTI->RTSR      &= ~EXTI_Line3; /*clear rising edge*/\
    EXTI->FTSR      |= EXTI_Line3
#define	CC1200_GDO0_INT_DIS	NVIC_DisableIRQ(EXTI3_IRQn)

#define CC1200_RESET_PORT_BASE	GPIOB
#define CC1200_RESET_PIN_MASK	GPIO_BSRR_BS1
#define CC1200_RESET_OUTPUT		CC1200_RESET_PORT_BASE->CRL	&= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); CC1200_RESET_PORT_BASE->CRL	|= (GPIO_CRL_MODE1_0)
#define CC1200_RESET_INPUT		CC1200_RESET_PORT_BASE->CRL	&= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1); CC1200_RESET_PORT_BASE->CRL	|= (GPIO_CRL_CNF1_0)
#define CC1200_RESET_CLR					CC1200_RESET_PORT_BASE->BRR = CC1200_RESET_PIN_MASK
#define CC1200_RESET_SET					CC1200_RESET_PORT_BASE->BSRR = CC1200_RESET_PIN_MASK


#define CC1200_CLK_PORT_BASE	GPIOA
#define CC1200_CLK_PIN_MASK	GPIO_BSRR_BS5
#define CC1200_CLK_GET() 	(CC1200_CLK_PORT_BASE->IDR & CC1200_CLK_PIN_MASK)
#define CC1200_CLK_ALT_MODE 	CC1200_CLK_PORT_BASE->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);CC1200_CLK_PORT_BASE->CRL |= GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1


#define CC1200_MISO_PORT_BASE	GPIOA
#define CC1200_MISO_PIN_MASK	GPIO_BSRR_BS6
#define CC1200_MISO_GET() 	(CC1200_MISO_PORT_BASE->IDR & CC1200_MISO_PIN_MASK)
#define CC1200_MISO_ALT_MODE 	CC1200_MISO_PORT_BASE->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);CC1200_MISO_PORT_BASE->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1

#define CC1200_MOSI_PORT_BASE	GPIOA
#define CC1200_MOSI_PIN_MASK	GPIO_BSRR_BS7
#define CC1200_MOSI_GET() 	(CC1200_MOSI_PORT_BASE->IDR & CC1200_MOSI_PIN_MASK)
#define CC1200_MOSI_ALT_MODE 	CC1200_MOSI_PORT_BASE->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);CC1200_MOSI_PORT_BASE->CRL |= GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1



 typedef enum{
	SYS_INIT = 0xA5A5,
	SYS_DEINIT = 0x5A5A,
	SYS_OK = 0
}SYS_STATUS;

/*---------------------------------------------------------------------------*/
#endif /*__HW_CONFIG_H*/
/*---------------------------------------------------------------------------*/
