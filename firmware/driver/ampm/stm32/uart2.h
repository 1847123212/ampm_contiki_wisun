#ifndef __UART2_H__
#define __UART2_H__

#include "stm32f10x.h"
#include <stdint.h>
#include "lib/ringbuf.h"
#include "hw_config.h"
#include "stm32f10x_usart.h"

#define UART2_USE_TX_RINGBUFF

void USART2_Init(uint32_t pclk1,uint32_t baudrate,uint16_t databits,uint16_t stopbits,uint16_t parity);
void USART2_DeInit(void);
uint8_t USART2_PutChar (uint8_t ch);
void USART2_PutString (char *s);
uint8_t USART2_GetChar (void) ;

extern   RINGBUF USART2_RxRingBuff;
#ifdef UART3_USE_TX_RINGBUFF
extern RINGBUF USART2_TxRingBuff;
#endif

#define __USART2_BAUDRATE         115200			
#define __USART2_DATABITS         0x00000000
#define __USART2_STOPBITS         0x00000000
#define __USART2_PARITY           0x00000000
#define __USART2_FLOWCTRL         0x00000000

#endif

