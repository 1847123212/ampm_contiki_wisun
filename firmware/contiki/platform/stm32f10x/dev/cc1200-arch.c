/*
 * Copyright (c) 2015, Zolertia
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
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*---------------------------------------------------------------------------*/
/**
 * \addtogroup zoul
 * @{
 *
 * \defgroup zoul-cc1200 Zoul CC1200 arch
 *
 * CC1200 Zoul arch specifics
 * @{
 *
 * \file
 * CC1200 Zoul arch specifics
 */
/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "contiki-net.h"
#include "dev/leds.h"
#include "spi.h"
#include <stdio.h>
#include "hw_config.h"
#define SPI_WAITFORTx_BEFORE() halSpiBegin()
#ifndef DEBUG_CC1200_ARCH
#define DEBUG_CC1200_ARCH 1
#endif
/*---------------------------------------------------------------------------*/
#if DEBUG_CC1200_ARCH > 0
#define PRINTF(...) printf(__VA_ARGS__)
#define BUSYWAIT_UNTIL(cond, max_time)                                  \
  do {                                                                  \
    rtimer_clock_t t0;                                                  \
    t0 = RTIMER_NOW();                                                  \
    while(!(cond) && RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + (max_time))) {} \
    if(!(RTIMER_CLOCK_LT(RTIMER_NOW(), t0 + (max_time)))) { \
      printf("ARCH: Timeout exceeded in line %d!\n", __LINE__); \
    } \
  } while(0)
#else
#define PRINTF(...)
#define BUSYWAIT_UNTIL(cond, max_time) while(!cond)
#endif
/*---------------------------------------------------------------------------*/
extern int cc1200_rx_interrupt(void);
/*---------------------------------------------------------------------------*/
void
cc1200_int_handler(uint8_t port, uint8_t pin)
{
  /* To keep the gpio_register_callback happy */
  cc1200_rx_interrupt();
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_spi_select(void)
{
  /* Set CSn to low (0) */
  CC1200_CSN_CLR;
  /* The MISO pin should go low before chip is fully enabled. */
  BUSYWAIT_UNTIL(
	CC1200_MISO_GET() == 0,
    RTIMER_SECOND / 100);
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_spi_deselect(void)
{
  /* Set CSn to high (1) */
  CC1200_CSN_SET;
}


/*---------------------------------------------------------------------------*/
int
cc1200_arch_spi_rw_byte(uint8_t c)
{
  SPI_WAITFORTx_BEFORE();
  c = halSpiWriteByte(SPI1,c);
  return c;
}
/*---------------------------------------------------------------------------*/
int
cc1200_arch_spi_rw(uint8_t *inbuf, const uint8_t *write_buf, uint16_t len)
{
  int i;
  uint8_t c;

  if((inbuf == NULL && write_buf == NULL) || len <= 0) {
    return 1;
  } else if(inbuf == NULL) {
    for(i = 0; i < len; i++) {
      SPI_WAITFORTx_BEFORE();
			c = halSpiWriteByte(SPI1,write_buf[i]);
      /* read and discard to avoid "variable set but not used" warning */
      (void)c;
    }
  } else if(write_buf == NULL) {
    for(i = 0; i < len; i++) {
      SPI_WAITFORTx_BEFORE();
			inbuf[i] = halSpiWriteByte(SPI1,0);
    }
  } else {
    for(i = 0; i < len; i++) {
      SPI_WAITFORTx_BEFORE();
			inbuf[i] = halSpiWriteByte(SPI1,write_buf[i]);
    }
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_gpio0_setup_irq(int rising)
{
	if(rising) {
    CC1200_GDO0_INT_RISING;
  } else {
    CC1200_GDO0_INT_FALLING;
  }
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_gpio2_setup_irq(int rising)
{
  if(rising) {
    CC1200_GDO2_INT_RISING;
  } else {
    CC1200_GDO2_INT_FALLING;
  }
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_gpio0_enable_irq(void)
{
  CC1200_GDO0_INT_EN;
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_gpio0_disable_irq(void)
{
  CC1200_GDO0_INT_DIS;
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_gpio2_enable_irq(void)
{
	CC1200_GDO2_INT_EN;
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_gpio2_disable_irq(void)
{
  CC1200_GDO2_INT_DIS;
}
/*---------------------------------------------------------------------------*/
int
cc1200_arch_gpio0_read_pin(void)
{
  return CC1200_GDO0_GET();
}
/*---------------------------------------------------------------------------*/
int
cc1200_arch_gpio2_read_pin(void)
{
  return CC1200_GDO2_GET();
}
/*---------------------------------------------------------------------------*/
int
cc1200_arch_gpio3_read_pin(void)
{
  return 0x00;
}
/*---------------------------------------------------------------------------*/
void
cc1200_arch_init(void)
{
	SPI_InitHighFreq(1);
	CC1200_CSN_OUTPUT;
	CC1200_CLK_ALT_MODE;
	CC1200_MISO_ALT_MODE;
	CC1200_MOSI_ALT_MODE;
	
  /* First leave RESET high */
  CC1200_RESET_OUTPUT;
	CC1200_RESET_CLR;
	clock_delay(10000);
  CC1200_RESET_SET;
	
  /* Initialize CSn, enable CSn and then wait for MISO to go low*/
  SPI_WAITFORTx_BEFORE();

  /* Configure GPIOx */
  CC1200_GDO2_INPUT_FLOAT;
	CC1200_GDO0_INPUT_FLOAT;

  /* Leave CSn as default */
  cc1200_arch_spi_deselect();

  /* Ensure MISO is high */
  BUSYWAIT_UNTIL(
    CC1200_MISO_GET(),
    RTIMER_SECOND / 10);
}
/*---------------------------------------------------------------------------*/
/**
 * @}
 * @}
 */

