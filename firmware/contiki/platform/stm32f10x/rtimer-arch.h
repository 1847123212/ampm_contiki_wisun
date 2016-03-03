/**
 *\file
 *         Header file for the STM32F103-specific rtimer code
 * \author
 *         Simon Berg <ksb@users.sourceforge.net>
 */

#ifndef __RTIMER_ARCH_H__
#define __RTIMER_ARCH_H__

#include "sys/rtimer.h"
#include <stm32f10x.h>
//#define RTIMER_ARCH_SECOND 1000//(SystemCoreClock/48000)

void rtimer_arch_set(rtimer_clock_t t);

rtimer_clock_t rtimer_arch_now(void);
void clock_delay_usec(uint32_t uS);
//#define rtimer_arch_now() clock_time()
#define RTIMER_NOW() rtimer_arch_now()

#endif /* __RTIMER_ARCH_H__ */

