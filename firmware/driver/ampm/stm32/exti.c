/**********************************************************************
Name: Hai Nguyen Van
Cellphone: (84) 97-8779-222
Mail:thienhaiblue@ampm.com.vn 
----------------------------------
AMPM ELECTRONICS EQUIPMENT TRADING COMPANY LIMITED.,
Add: 143/36/10 , Lien khu 5-6 street, Binh Hung Hoa B Ward, Binh Tan District , HCM City,Vietnam

*********************************************************************/
/**
* \file
*         exti driver
* \author
*         Nguyen Van Hai <blue@ambo.com.vn>
*/

#include "exti.h"
#include "low_power_mode.h"
#include "rtc.h"

void EXTI_Init(void)
{
//		//RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
		/*Congig use for EXTI0*/
		AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;	//Disable JTAG funtion, keep SWJ funtion for debug(only user when PB3,PB4,PB5,PA15 user for another funtion)
		AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;   // clear used pin
		AFIO->EXTICR[1] &= ~AFIO_EXTICR1_EXTI1;   // clear used pin
		AFIO->EXTICR[2] &= ~AFIO_EXTICR1_EXTI2;   // clear used pin
		AFIO->EXTICR[3] &= ~AFIO_EXTICR1_EXTI3;    // clear used pin
	
// 		/*Use RTC Wakeup*/
		EXTI->PR = EXTI_Line17;
		EXTI->IMR       &= ~EXTI_Line17;             // mask interrupt
    EXTI->EMR       &= ~EXTI_Line17;             // mask event
		EXTI->IMR       |= EXTI_Line17;             // mask interrupt
		EXTI->EMR       |= EXTI_Line17;             // mask event
    EXTI->RTSR      |= EXTI_Line17;            // clear rising edge

}


extern void cc1200_int_handler(uint8_t port, uint8_t pin);

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & EXTI_Line0)
	{	
		cc1200_int_handler(0,0);
		EXTI->PR = EXTI_Line0;
	}
}


void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & EXTI_Line3)
	{
		cc1200_int_handler(0,0);
		EXTI->PR = EXTI_Line3;
	}
}

void USBWakeUp_IRQHandler(void)
{
	EXTI->PR = EXTI_Line18;
}



