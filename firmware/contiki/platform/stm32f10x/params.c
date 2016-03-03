

#include "contiki.h"
#include "contiki-conf.h"
#include <stdio.h>
#include <string.h>
#include "system_config.h"


#include "contiki-net.h"
#include "params.h"

#if WITH_NODE_ID
uint16_t node_id;
#endif

#if CONTIKI_CONF_RANDOM_MAC
extern uint8_t rng_get_uint8(void);
static void
generate_new_eui64(uint8_t eui64[8]) {
  eui64[0] = 0x02;
  eui64[1] = rng_get_uint8();
  eui64[2] = rng_get_uint8();
  eui64[3] = 0xFF;
  eui64[4] = 0xFE;
  eui64[5] = rng_get_uint8();
  eui64[6] = rng_get_uint8();
  eui64[7] = rng_get_uint8();
}
#endif


/* 0 Hard coded, minmal program and eeprom usage. */
uint8_t
params_get_eui64(uint8_t *eui64) {
	memcpy(eui64,sysCfg.mac_address,8);
}


uint8_t
params_get_channel(void) {
/* Always returns a valid channel */
  return 26;
}

uint16_t
params_get_panid(void) {
  return sysCfg.panid;
}
uint16_t
params_get_panaddr(void) {
  return sysCfg.panaddr;
}
uint8_t
params_get_txpower(void)
{
  return sysCfg.txpower;
}

