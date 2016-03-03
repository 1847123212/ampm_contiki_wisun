#ifndef __SYSTEM_CONFIG_H__
#define __SYSTEM_CONFIG_H__
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "stm32f10x_flash.h"
#include "hw_config.h"


#define DEFAULT_SMS_PWD			"12345678"
#define DEFAULT_GPSR_APN		"internet"
#define DEFAULT_GPRS_USR		"mms"
#define DEFAULT_GPRS_PWD		"mms"
#define MCU_RESET_NONE				0
#define MCU_RESET_IMMEDIATELY 1
#define MCU_RESET_AFTER_10_SEC 2
#define MCU_RESET_AFTER_30_SEC 3
#define MCU_RESET_IS_WAITING 4



#define FIRMWARE_VERSION	"PJ2000STV3.03"


typedef struct __attribute__((packed)){
	uint32_t status;
	uint32_t fileSize;
	uint32_t offset;
	uint32_t saveSector;
	uint32_t crc;
}FW_UPDATE_TYPE;

typedef struct __attribute__((packed)){
	uint32_t size;
	FW_UPDATE_TYPE firmware;
	uint8_t fwVersion[16];	/**< firmware vertion>**/
	uint8_t server_name[32];
	uint8_t mac_address[8];
	uint16_t note_id;
	uint16_t panid;
	uint16_t panaddr;
	uint8_t txpower;
	uint32_t crc;
}CONFIG_POOL;

extern CONFIG_POOL sysCfg;


void CFG_Save(void);
void CFG_Load(void);
void CFG_ReLoad(void);
void CFG_Write(uint8_t *buff, uint32_t address, int offset, int length);
uint8_t CFG_CheckSum(CONFIG_POOL *sysCfg);
uint8_t CFG_Check(CONFIG_POOL *sysCfg);
void ResetMcuSet(uint8_t resetType);
void ResetMcuTask(void);
#endif
