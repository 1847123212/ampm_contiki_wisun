/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
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
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         MSP430-specific rtimer code
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"

#include "sys/energest.h"
#include "sys/rtimer.h"
#include "sys/process.h"
#include "stm32f10x.h"

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define TIMER_PERIOD	1000

uint32_t tmr2Cnt = 0;
/*---------------------------------------------------------------------------*/
void TIM2_IRQHandler(void)
{
	uint16_t i;
	uint8_t c;
	if(TIM2->SR & 1)
	{
		TIM2->SR = (uint16_t)~0x0001;
		tmr2Cnt++;
		ENERGEST_ON(ENERGEST_TYPE_IRQ);
		
		rtimer_run_next();

		if(process_nevents() > 0) {
			//LPM4_EXIT;
		}
		ENERGEST_OFF(ENERGEST_TYPE_IRQ);
	}
}


void clock_delay_usec(uint32_t uS)
{
		uS *= 10;
		while(uS--);
}

/*---------------------------------------------------------------------------*/
void
rtimer_arch_init(void)
{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;                     // enable clock for TIM2
    TIM2->PSC = (uint16_t)(SystemCoreClock/1000000) - 1;            // set prescaler
    TIM2->ARR = TIMER_PERIOD;  //1000uS // set auto-reload
    TIM2->CR1 = 0;                                          // reset command register 1
    TIM2->CR2 = 0;                                          // reset command register 2
		TIM2->DIER = 1;                             
		NVIC_SetPriority (TIM2_IRQn,((0x01<<3) | 1));
		NVIC_EnableIRQ(TIM2_IRQn);// enable interrupt
    TIM2->CR1 |= 1;                              // enable timer
}
/*---------------------------------------------------------------------------*/
rtimer_clock_t
rtimer_arch_now(void)
{
  rtimer_clock_t t1, t2;
  do {
    t1 = tmr2Cnt;
    t2 = tmr2Cnt;
  } while(t1 != t2);
  return t1;
}

/*---------------------------------------------------------------------------*/
void
rtimer_arch_schedule(rtimer_clock_t t/*uS*/)
{
  PRINTF("rtimer_arch_schedule time %u\n", t);
	TIM2->ARR = t;  //us // set auto-reload
}
/*---------------------------------------------------------------------------*/
