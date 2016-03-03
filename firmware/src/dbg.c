/**********************************************************************
Name: Hai Nguyen Van
Cellphone: (84) 97-8779-222
Mail:thienhaiblue@ampm.com.vn 
----------------------------------
AMPM ELECTRONICS EQUIPMENT TRADING COMPANY LIMITED.,
Add: 143/36/10 , Lien khu 5-6 street, Binh Hung Hoa B Ward, Binh Tan District , HCM City,Vietnam

*********************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart1.h"

/* The ITM port is used to direct the printf() output to the serial window in 
the Keil simulator IDE. */
#define mainITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define mainITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define mainDEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define mainTRCENA          0x01000000


int fputc( int iChar, FILE *pxNotUsed ) 
{
	/* Just to avoid compiler warnings. */
	( void ) pxNotUsed;

	if( mainDEMCR & mainTRCENA ) 
	{
		while( mainITM_Port32( 0 ) == 0 );
		mainITM_Port8( 0 ) = iChar;
	}
//		USART1_PutChar((uint8_t)iChar);
//  	return( iChar );
}

