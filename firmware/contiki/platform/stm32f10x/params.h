#ifndef __PARAMS_H__
#define __PARAMS_H__

/* Include settings.h, then dummy out the write routines */
#include "system_config.h"

uint8_t params_get_eui64(uint8_t *eui64);
/* Parameters stored in eeprom */
uint16_t params_get_nodeid(void);
uint8_t params_get_channel(void);
uint16_t params_get_panid(void);
uint16_t params_get_panaddr(void);
uint8_t params_get_txpower(void);

#endif /* __PARAMS_H__ */
