/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
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
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"

#include <stdio.h> /* For printf() */
#include "dev/button-sensor.h"
int helloTaskCnt1 = 0;
static struct etimer timer1,timer2;
SENSORS(&button_sensor);

PROCESS(hello_world_process2, "Hello world process2");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process2, ev, data)
{
	PROCESS_BEGIN();
	/*
   * Loop for ever.
   */
  while(1) {
    /*
     * We set a timer that wakes us up once every second. 
     */
    etimer_set(&timer1, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer1));
		printf("Hello world process2\n");
  }
	PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process1, "Hello world process1");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process1, ev, data)
{
	
  PROCESS_BEGIN();
	process_start(&hello_world_process2, NULL);
	SENSORS_ACTIVATE(button_sensor);
  while(1)
	{
		etimer_set(&timer2, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer2));
		printf("Hello world process1\n");
		PROCESS_PAUSE();
	}
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
