#include "system_config.h"
#include "lib/sys_tick.h"
#include <stdlib.h>
#include <stdio.h>
#include "rtc.h"

const uint8_t default_mac_address[8]  = {0x02, 0x10, 0x11, 0xff, 0xfe, 0xed, 0x50, 0x01};
const uint8_t default_server_name[]  = "ampm.com.vn";
CONFIG_POOL sysCfg;

uint8_t sysResetMcuFlag = MCU_RESET_NONE;

void ResetMcuSet(uint8_t resetType)
{
	sysResetMcuFlag = resetType;
}

void ResetMcuTask(void)
{
		static Timeout_Type tMcuResetTimeout;
		switch(sysResetMcuFlag)
		{
			case MCU_RESET_NONE:

			break;
			case MCU_RESET_IMMEDIATELY:
				NVIC_SystemReset();
			break;
			case MCU_RESET_AFTER_10_SEC:
				InitTimeout(&tMcuResetTimeout,SYSTICK_TIME_SEC(10));
				sysResetMcuFlag = MCU_RESET_IS_WAITING;
			break; 
			case MCU_RESET_AFTER_30_SEC:
				InitTimeout(&tMcuResetTimeout,SYSTICK_TIME_SEC(30));	
				sysResetMcuFlag = MCU_RESET_IS_WAITING;
			break;
			case MCU_RESET_IS_WAITING:
				if(CheckTimeout(&tMcuResetTimeout) == SYSTICK_TIMEOUT)
				{
					NVIC_SystemReset();
				}
			break;
			default:
				NVIC_SystemReset();
				break;
		}
}

void CFG_ReLoad(void)
{
	memcpy(&sysCfg, (void*)CONFIG_AREA_START, sizeof(CONFIG_POOL));
}
void CFG_Load(void)
{
	uint32_t i,saveFlag = 0,u32Temp = 0;
	uint8_t *u8Pt;
	float firmwareVersion;
	memcpy(&sysCfg, (void*)CONFIG_AREA_START, sizeof(CONFIG_POOL));

	u8Pt = (uint8_t *)&sysCfg;
	u32Temp = 0;
	for(i = 0;i < sizeof(CONFIG_POOL)-sizeof(sysCfg.crc);i++)
	{
		u32Temp += u8Pt[i];
	}
	
	if(u32Temp != sysCfg.crc)
	{
		memset((void*)&sysCfg, 0xFF, sizeof sysCfg);
		saveFlag = 1;
	}
	else
	{
		sscanf((const char *)sysCfg.fwVersion,"PJ2000STV%f",&firmwareVersion);
		if(firmwareVersion <= 3.02)
		{
			memset((void*)&sysCfg, 0xFF, sizeof sysCfg);
			saveFlag = 1;
		}
	}

	if(sysCfg.size != sizeof(CONFIG_POOL))
	{
		sysCfg.size = sizeof(CONFIG_POOL);
		saveFlag = 1;
	}
	if(sysCfg.firmware.saveSector != 64)
	{
		sysCfg.firmware.saveSector = 64;
		saveFlag = 1;
	}
	
	if((sysCfg.fwVersion[0] == 0xFF) || (memcmp((char *)sysCfg.fwVersion,FIRMWARE_VERSION,sizeof(FIRMWARE_VERSION))))
	{
		memcpy((char *)sysCfg.fwVersion,FIRMWARE_VERSION,sizeof(FIRMWARE_VERSION));
		saveFlag = 1;
	}
	if(sysCfg.server_name[0] == 0xff)
	{
		strcpy((char *)sysCfg.server_name,(char *)default_server_name);
		memcpy((char *)sysCfg.mac_address,default_mac_address,sizeof(sysCfg.mac_address));
		saveFlag = 1;
	}
	if(sysCfg.note_id == 0xffff)
	{
		sysCfg.note_id = 0;
		saveFlag = 1;
	}
	if(sysCfg.panaddr == 0xffff)
	{
		sysCfg.panaddr = 0;
		saveFlag = 1;
	}
	if(sysCfg.panid == 0xffff)
	{
		sysCfg.panid = 0;
		saveFlag = 1;
	}
	if(sysCfg.txpower == 0xffff)
	{
		sysCfg.txpower = 0;
		saveFlag = 1;
	}
	if(saveFlag)
	{
		CFG_Save();
	}
}


uint8_t CFG_CheckSum(CONFIG_POOL *sysCfg)
{
	uint32_t u32Temp = 0;
	int16_t i;
	uint8_t *u8Pt;
	u8Pt = (uint8_t *)sysCfg;
	u32Temp = 0;
	for(i = 0;i < sizeof(CONFIG_POOL)-sizeof(sysCfg->crc);i++)
	{
		u32Temp += u8Pt[i];
	}
	if(u32Temp != sysCfg->crc)
	{
		return 0;
	}
	return 1;
}
void CFG_Save(void)
{
	int16_t i;
	uint32_t u32Temp;
	uint8_t *u8Pt;
	uint32_t *cfgdest;
	uint16_t  FlashStatus;

	
	if(memcmp((void *)CONFIG_AREA_START,&sysCfg,sizeof(CONFIG_POOL)) == NULL)
		return;
	__disable_irq();	
	
	u8Pt = (uint8_t *)&sysCfg;
	u32Temp = 0;
	for(i = 0;i < sizeof(CONFIG_POOL)-sizeof(sysCfg.crc);i++)
	{
		u32Temp += u8Pt[i];
	}
	sysCfg.crc = u32Temp;
	
	FLASH_Unlock();
	for(i=0; i <= sizeof(CONFIG_POOL)/ PAGE_SIZE; i++) 
	{
		FlashStatus = FLASH_ErasePage((uint32_t)(CONFIG_AREA_START + i*PAGE_SIZE));
		if(FLASH_COMPLETE != FlashStatus) 
		{
			FLASH_Lock();
			__enable_irq();
			return;
		}
	}
	cfgdest = (uint32_t*)&sysCfg;
	for(i=0; i < sizeof(CONFIG_POOL); i+=4) 
	{
		FlashStatus = FLASH_ProgramWord(CONFIG_AREA_START + i, *(uint32_t*)(cfgdest + i/4));
		if(*(uint32_t*)(cfgdest + i/4) != *(uint32_t*)(CONFIG_AREA_START + i)) //check wrote data
		{
			FLASH_Lock();
		__enable_irq();
			return;
		}
	}
	FLASH_Lock();

	__enable_irq();
	RTC_SetAlarm(RTC_GetCounter() + RTC_ALARM_INTERVAL);
}
