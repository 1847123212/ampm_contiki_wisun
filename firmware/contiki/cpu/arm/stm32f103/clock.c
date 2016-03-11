#include <stm32f10x.h>
#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>
#include <debug-uart.h>
#include "lib/sys_tick.h"
static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;


void
SysTick_Handler(void)
{
  (void)SysTick->CTRL;
  SCB->ICSR = SCB_ICSR_PENDSTCLR;
  current_clock++;
  if(etimer_pending() && etimer_next_expiration_time() <= current_clock) {
    etimer_request_poll();
    /* printf("%d,%d\n", clock_time(),etimer_next_expiration_time  	()); */

  }
  if (--second_countdown == 0) {
    current_seconds++;
    second_countdown = CLOCK_SECOND;
  }
	//SysTick_Task();
}


void
clock_init()
{
	SysTick->LOAD  = ((SystemCoreClock/CLOCK_SECOND) - 1);      // set reload register
	/* preemption = TICK_PRIORITY, sub-priority = 1 */
	NVIC_SetPriority(SysTick_IRQn, ((0x01<<3)| 1));
  SysTick->VAL   =  0;                                          // clear  the counter
  SysTick->CTRL = 0x07;      
}

clock_time_t
clock_time(void)
{
  return current_clock;
}

/* The inner loop takes 4 cycles. The outer 5+SPIN_COUNT*4. */

void clock_delay(unsigned int t)
{
	for(; t > 0; t--) {
    unsigned int j;
    for(j = 50; j > 0; j--) {
    }
  }
}



unsigned long
clock_seconds(void)
{
  return current_seconds;
}
