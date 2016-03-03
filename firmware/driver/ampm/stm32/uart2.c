/**
* \file
*         uart2 driver
* \author
*         Nguyen Van Hai <blue@ambo.com.vn>
*/

#include "uart2.h"
#include "system_config.h"
#include "hw_config.h"
extern RINGBUF comRingBuf;
extern uint8_t logEnable;
extern void RFID_Input(char c);
uint32_t uart2_parity = 0;
/*----------------------------------------------------------------------------
 Define  Baudrate setting (BRR) for USART2 
 *----------------------------------------------------------------------------*/
#define __DIV(__PCLK, __BAUD)       ((__PCLK*25)/(4*__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) * 16 + 50) / 100)
#define __USART2_BRR(__PCLK, __BAUD) ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))

 uint8_t USART2_RxBuff[1024] = {0}; 
 RINGBUF USART2_RxRingBuff;

#ifdef UART2_USE_TX_RINGBUFF
 uint8_t USART2_TxBuff[512] = {0};
 RINGBUF USART2_TxRingBuff;
#endif

void USART2_Init(uint32_t pclk1,uint32_t baudrate,uint16_t databits,uint16_t stopbits,uint16_t parity)
{
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;                     // enable clock for Alternate Function
		//AFIO->MAPR   &= ~(3 << 4);                              // clear USART2 remap
		//UART2 Pin
		
		GPIOA->CRL   &= ~( GPIO_CRL_CNF2 | GPIO_CRL_MODE2);           // Clear PA2
		GPIOA->CRL   |=    GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1; // USART2 Tx (PA2)   Alternate function output Open-drain                     // USART2 Rx (PA3)  input floating
		
		GPIOA->CRL   &= ~( GPIO_CRL_CNF3 | GPIO_CRL_MODE3);           // Clear PA3
		GPIOA->CRL   |=  (GPIO_CRL_CNF3_0);                     // USART2 Rx (PA3)  input floating
		RS485_DIR_PIN_SET_OUTPUT;
		RS485_DIR_PIN_CLR;
		uart2_parity = parity;
    USART2->BRR  = __USART2_BRR(pclk1, baudrate); // set baudrate
    USART2->CR1  = databits;                       // set Data bits
    USART2->CR2  = stopbits;                       // set Stop bits
    USART2->CR1 |= USART_Parity_No;                         // set Parity
    USART2->CR3  = __USART2_FLOWCTRL;                       // Set Flow Control
	
    USART2->CR1 |= (USART_CR1_RE | USART_CR1_TE);           // RX, TX enable
		// interrupts used
		USART2->CR1 |= USART_CR1_RXNEIE;
			
		RINGBUF_Init(&USART2_RxRingBuff,USART2_RxBuff,sizeof(USART2_RxBuff));
		#ifdef UART2_USE_TX_RINGBUFF
		USART2->CR1 |= USART_CR1_TXEIE;
		RINGBUF_Init(&USART2_TxRingBuff,USART2_TxBuff,sizeof(USART2_TxBuff));
		#endif
	
		/* preemption = GPS_PRIORITY, sub-priority = 1 */
		NVIC_SetPriority(USART2_IRQn, ((0x01<<3)| 2));
		NVIC_EnableIRQ(USART2_IRQn);
    USART2->CR1 |= USART_CR1_UE;                            // USART enable
}

void USART2_DeInit(void)
{
	RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;                     // enable clock for Alternate Function
	GPIOA->CRL   &= ~( GPIO_CRL_CNF3 | GPIO_CRL_MODE3);           // Clear PA3
}

void USART2_PutString (char *s)
{
   while(*s)
	{
		USART2_PutChar(*s++);
	}
}
   

uint8_t USART2_PutChar (uint8_t ch) 
{
	uint32_t timeOut = 100000000,i = 20000;
	if(RS485_DIR_GET() == 0)
	{
		RS485_DIR_PIN_SET;
		while(RS485_DIR_GET() == 0);
		while(i--);
	}
#ifndef UART2_USE_TX_RINGBUFF
  while (!(USART2->SR & USART_SR_TXE));
	USART2->DR = ch;
#else
	while((RINGBUF_GetFill(&USART2_TxRingBuff) >= (USART2_TxRingBuff.size - 1)) && timeOut--){}
	RINGBUF_Put(&USART2_TxRingBuff,ch);
	if((USART2->CR1 & USART_CR1_TXEIE) != USART_CR1_TXEIE)
	{
		USART2->CR1 |= USART_CR1_TXEIE;
	}
#endif
	return ch;
}


uint8_t USART2_GetChar (void) 
{
  while (!(USART2->SR & USART_SR_RXNE));
  return ((uint8_t)(USART2->DR & 0x1FF));
}


void USART2_IRQHandler(void) 
{
		uint8_t c;uint32_t s,even;
	if(USART2->SR & (USART_SR_RXNE | USART_SR_ORE))
	{	  
			c = (uint8_t)(USART2->DR & 0x1FF);
			if(uart2_parity == USART_Parity_Even){
				//c &= 0x7F;
				s = c;
				even = (s & 1) + (s>>1 & 1) + (s>>2 & 1) + (s>>3 & 1) + (s>>4 & 1) + (s>>5 & 1) + (s>>6 & 1);
				if(even & 1)
				{
					if(s & 0x80)
						RINGBUF_Put(&USART2_RxRingBuff,(c & 0x7F));
				}
				else
				{
					if((s & 0x80) == 0)
						RINGBUF_Put(&USART2_RxRingBuff,(c & 0x7F));
				}
			}
			else
				RINGBUF_Put(&USART2_RxRingBuff,c);
	}

	#ifdef UART2_USE_TX_RINGBUFF
	if(USART2->SR & USART_SR_TXE)
	{
		if(RINGBUF_Get(&USART2_TxRingBuff,&c) == 0)
		{
			if(uart2_parity == USART_Parity_Even){
				s = c;
				even = (s & 1) + (s>>1 & 1) + (s>>2 & 1) + (s>>3 & 1) + (s>>4 & 1) + (s>>5 & 1) + (s>>6 & 1);
				if(even & 1)
				{
					USART2->DR = c | 0x80;
				}
				else
				{
					USART2->DR = c & 0x7F;
				}
			}else{
				USART2->DR = c;
			}
		}
		else
		{
			
			USART2->CR1 &= (~USART_CR1_TXEIE);
		}
	}
	#endif
}






/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/




