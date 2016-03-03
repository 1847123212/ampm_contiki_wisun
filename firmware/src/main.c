
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "contiki.h"
#include "contiki-net.h"
#include "contiki-lib.h"

#include "sys/process.h"
#include "sys/procinit.h"
#include "sys/autostart.h"

#include "lib/list.h"
#include "lib/random.h"

#include "dev/button-sensor.h"
#include "dev/leds.h"

#include "debug-uart.h"

#include "etimer.h"
#include "rtimer.h"
#include "clock.h"


//#include "radio/rf230bb/rf230bb.h"
#include "net/mac/frame802154.h"
#include "net/mac/framer-802154.h"
#include "net/ipv6/sicslowpan.h"
#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"

#include "net/rime/rime.h"


#include "hello-world1.h"

#include "uart1.h"
#include "rtc.h"
#include "adc.h"
#include "dev/watchdog.h"

#include "params.h"
#define PRINTF(...) printf(__VA_ARGS__)
/* Get periodic prints from idle loop, from clock seconds or rtimer interrupts */
/* Use of rtimer will conflict with other rtimer interrupts such as contikimac radio cycling */
/* STAMPS will print ENERGEST outputs if that is enabled. */
#define PERIODICPRINTS 1
#if PERIODICPRINTS
//#define PINGS 64
#define ROUTES 600
#define STAMPS 60
#define STACKMONITOR 1024
uint32_t clocktime;
#define TESTRTIMER 0
#if TESTRTIMER
uint8_t rtimerflag=1;
struct rtimer rt;
void rtimercycle(void) {rtimerflag=1;}
#endif
#endif


extern void example_function(void);
extern void macroExample(void);
unsigned int idle_count = 0;

/* Get a pseudo random number using the ADC */
uint8_t rng_get_uint8(void) {
	uint8_t i, j,value;
	AMPM_ADC_Init();
	for (i = 0, j = 0; i < 4; i++) {
		//toggle reference to increase noise
		//Select AREF as reference, measure 1.1 volt bandgap reference.
		StartADC(); //Start conversion
		//while((ADC1->SR & (1<<2)) == 0); //Wait till done
		value = ADC1->DR;
		ADC1->SR &= ~(1<<2);
		j = (j << 2) + value;
	}
	//Disable ADC
	printf("rng issues %d\n", j);
	return j;
}

#if ROUTES && NETSTACK_CONF_WITH_IPV6
static void
ipaddr_add(const uip_ipaddr_t *addr)
{
	uint16_t a;
	int8_t i, f;
	for(i = 0, f = 0; i < sizeof(uip_ipaddr_t); i += 2) {
		a = (addr->u8[i] << 8) + addr->u8[i + 1];
		if(a == 0 && f >= 0) {
			if(f++ == 0) PRINTF("::");
		} else {
			if(f > 0) {
				f = -1;
			} else if(i > 0) {
				PRINTF(":");
			}
			PRINTF("%x",a);
		}
	}
}
#endif

static void
print_processes(struct process * const processes[])
{
  /*  const struct process * const * p = processes;*/
  printf("Starting");
  while(*processes != NULL) {
    printf(" '%s'", (*processes)->name);
    processes++;
  }
  putchar('\n');
}

void initialize(void) {
	SystemInit();
	RTC_Init();
	
	USART1_Init(SystemCoreClock,115200);
  //	PRINTA("\n*******Booting %s*******\n", CONTIKI_VERSION_STRING);
	printf("\n*** Booting %s (%s %s) ***\n", CONTIKI_VERSION_STRING, __DATE__, __TIME__);
	/* init LEDs */
  leds_init();
  clock_init();
	/* rtimers needed for radio cycling */
	rtimer_init();
	/* Initialize process subsystem */
  process_init();
	/* etimers must be started before ctimer_init */
  process_start(&etimer_process, NULL);
	
	ctimer_init();
	/* Start radio and radio receive process */
	//NETSTACK_RADIO.init();
	/* Get a random seed for the 802.15.4 packet sequence number.
	 * Some layers will ignore duplicates found in a history (e.g. Contikimac)
	 * causing the initial packets to be ignored after a short-cycle restart.
	 */
	random_init(rng_get_uint8());
	
	linkaddr_t addr;
	if (params_get_eui64(addr.u8)) {
		printf("Random EUI64 address generated\n");
	}
	
#if NETSTACK_CONF_WITH_IPV6 
  memcpy(&uip_lladdr.addr, &addr.u8, sizeof(linkaddr_t));
#elif WITH_NODE_ID
  node_id=get_panaddr_from_eeprom();
  addr.u8[1]=node_id&0xff;
  addr.u8[0]=(node_id&0xff00)>>8;
  PRINTA("Node ID from eeprom: %X\n",node_id);
#endif  
  linkaddr_set_node_addr(&addr); 

	printf("EUI-64 MAC: %x-%x-%x-%x-%x-%x-%x-%x\n",addr.u8[0],addr.u8[1],addr.u8[2],addr.u8[3],addr.u8[4],addr.u8[5],addr.u8[6],addr.u8[7]);
	/* Initialize stack protocols */
	queuebuf_init();
	NETSTACK_RDC.init();
	NETSTACK_MAC.init();
	NETSTACK_NETWORK.init();
	
	//process_start(&mac_process, NULL);
	process_start(&tcpip_process, NULL);
	
	process_start(&hello_world_process1, NULL);
	/* Start autostart processes (defined in Contiki application) */
 // print_processes(autostart_processes);
  //autostart_start(autostart_processes);
  printf("Processes running\n");
}


int main(void)
{
#if NETSTACK_CONF_WITH_IPV6
  uip_ds6_nbr_t *nbr;
#endif /* NETSTACK_CONF_WITH_IPV6 */
	initialize();
  while(1) {
    process_run();
		watchdog_periodic();
    idle_count++;
		
#if PERIODICPRINTS
#if TESTRTIMER
	/* Timeout can be increased up to 8 seconds maximum.
	 * A one second cycle is convenient for triggering the various debug printouts.
	 * The triggers are staggered to avoid printing everything at once.
	 */
		if (rtimerflag) {
			rtimer_set(&rt, RTIMER_NOW()+ RTIMER_ARCH_SECOND*1UL, 1,(void *) rtimercycle, NULL);
			rtimerflag=0;
#else
				if (clocktime!=clock_seconds()) {
					 clocktime=clock_seconds();
#endif
#if STAMPS
			if ((clocktime%STAMPS)==0) {
#if ENERGEST_CONF_ON
#include "lib/print-stats.h"
				print_stats();
#elif RADIOSTATS
			extern volatile unsigned long radioontime;
				PRINTF("%u(%u)s\n",clocktime,radioontime);
#else
				PRINTF("%us\n",clocktime);
#endif

			}
#endif
#if TESTRTIMER
						clocktime+=1;
#endif
#if PINGS && NETSTACK_CONF_WITH_IPV6
							extern void raven_ping6(void);
							if ((clocktime%PINGS)==1) {
								printf("**Ping\n");
								raven_ping6();
							}
#endif

#if ROUTES && NETSTACK_CONF_WITH_IPV6
			if ((clocktime%ROUTES)==2) {
						
			extern uip_ds6_netif_t uip_ds6_if;

				uint8_t i,j;
				PRINTF("\nAddresses [%u max]\n",UIP_DS6_ADDR_NB);
				for (i=0;i<UIP_DS6_ADDR_NB;i++) {
					if (uip_ds6_if.addr_list[i].isused) {
						ipaddr_add(&uip_ds6_if.addr_list[i].ipaddr);
						PRINTF("\n");
					}
				}
				PRINTF("\nNeighbors [%u max]\n",NBR_TABLE_MAX_NEIGHBORS);

				for(nbr = nbr_table_head(ds6_neighbors);
						nbr != NULL;
						nbr = nbr_table_next(ds6_neighbors, nbr)) {
					ipaddr_add(&nbr->ipaddr);
					PRINTF("\n");
					j=0;
				}
				if (j) PRINTF("  <none>");
				PRINTF("\nRoutes [%u max]\n",UIP_DS6_ROUTE_NB);
				{
					uip_ds6_route_t *r;
					PRINTF("\nRoutes [%u max]\n",UIP_DS6_ROUTE_NB);
					j = 1;
					for(r = uip_ds6_route_head();
							r != NULL;
							r = uip_ds6_route_next(r)) {
						ipaddr_add(&r->ipaddr);
						PRINTF("/%u (via ", r->length);
						ipaddr_add(uip_ds6_route_nexthop(r));
						PRINTF(") %lus\n", r->state.lifetime);
						j = 0;
					}
				}
				if (j) PRINTF("  <none>");
				PRINTF("\n---------\n");
			}
#endif

#if STACKMONITOR
			//	if ((clocktime%STACKMONITOR)==3) {
			//		extern uint16_t __bss_end;
			//		uint16_t p=(uint16_t)&__bss_end;
			//		do {
			//			if (*(uint16_t *)p != 0x4242) {
			//				PRINTF("Never-used stack > %d bytes\n",p-(uint16_t)&__bss_end);
			//				break;
			//			}
			//			p+=10;
			//		} while (p<RAMEND-10);
			//	}
#endif
		}
#endif /* PERIODICPRINTS */
  }
}





