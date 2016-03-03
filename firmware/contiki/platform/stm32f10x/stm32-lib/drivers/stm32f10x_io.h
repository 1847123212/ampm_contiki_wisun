

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10X_IO_H
#define __STM32F10X_IO_H

#ifdef __cplusplus
 extern "C" {
#endif
                                              
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
   
   
/** @defgroup STM32L1XX_NUCLEO_Exported_Types Exported Types
  * @{
  */

typedef enum 
{  
  BUTTON_USER = 0,
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef; 

typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef;

/**
  * @}
  */ 

/** @defgroup STM32L1XX_NUCLEO_Exported_Constants Exported Constants
  * @{
  */ 

/** 
  * @brief  Define for STM32L1xx_NUCLEO board  
  */ 
#if !defined (USE_STM32F10X_IO)
 #define USE_STM32F10X_IO
#endif
 
/**
  * @}
  */ 

/** @defgroup STM32L1XX_NUCLEO_BUTTON BUTTON Constants
  * @{
  */  
#define BUTTONn                          1  

/**
  * @brief Key push-button
 */
#define USER_BUTTON_PIN                  GPIO_Pin_13
#define USER_BUTTON_GPIO_PORT            GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE)
#define USER_BUTTON_GPIO_CLK_DISABLE()   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,DISABLE)
#define USER_BUTTON_EXTI_IRQn            EXTI15_10_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)    (USER_BUTTON_GPIO_CLK_ENABLE())

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    (USER_BUTTON_GPIO_CLK_DISABLE())
/**
  * @}
  */
    
/** @addtogroup STM32L1XX_NUCLEO_BUS BUS Constants
  * @{
  */
/*###################### SPI1 ###################################*/
#define NUCLEO_SPIx                                 SPI1
#define NUCLEO_SPIx_CLK_ENABLE()                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE)

#define NUCLEO_SPIx_SCK_AF                          GPIO_AF5_SPI1
#define NUCLEO_SPIx_SCK_GPIO_PORT                   GPIOA
#define NUCLEO_SPIx_SCK_PIN                         GPIO_Pin_5
#define NUCLEO_SPIx_SCK_GPIO_CLK_ENABLE()           RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define NUCLEO_SPIx_SCK_GPIO_CLK_DISABLE()          RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE)

#define NUCLEO_SPIx_MISO_MOSI_AF                    GPIO_AF5_SPI1
#define NUCLEO_SPIx_MISO_MOSI_GPIO_PORT             GPIOA
#define NUCLEO_SPIx_MISO_MOSI_GPIO_CLK_ENABLE()     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define NUCLEO_SPIx_MISO_MOSI_GPIO_CLK_DISABLE()    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE)
#define NUCLEO_SPIx_MISO_PIN                        GPIO_Pin_6
#define NUCLEO_SPIx_MOSI_PIN                        GPIO_Pin_7
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define NUCLEO_SPIx_TIMEOUT_MAX                   1000

#define NUCLEO_I2C_SHIELDS_EV_IRQn                    I2C1_EV_IRQn
/**
  * @brief  SD Control Lines management
  */  
#define SD_CS_LOW()       GPIO_WriteBit(SD_CS_GPIO_PORT, SD_CS_PIN, Bit_RESET)
#define SD_CS_HIGH()      GPIO_WriteBit(SD_CS_GPIO_PORT, SD_CS_PIN, Bit_SET)
    


/**
  * @brief  SD Control Interface pins
  */
#define SD_CS_PIN                                 GPIO_Pin_5
#define SD_CS_GPIO_PORT                           GPIOB
#define SD_CS_GPIO_CLK_ENABLE()                   __GPIOB_CLK_ENABLE()
#define SD_CS_GPIO_CLK_DISABLE()                  __GPIOB_CLK_DISABLE()

/**
  * @brief  LCD Control Interface pins
  */
#define LCD_CS_PIN                                 GPIO_Pin_6
#define LCD_CS_GPIO_PORT                           GPIOB
#define LCD_CS_GPIO_CLK_ENABLE()                   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define LCD_CS_GPIO_CLK_DISABLE()                  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE)

/**
  * @brief  LCD Data/Command Interface pins
  */
#define LCD_DC_PIN                                 GPIO_Pin_9
#define LCD_DC_GPIO_PORT                           GPIOA
#define LCD_DC_GPIO_CLK_ENABLE()                   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)
#define LCD_DC_GPIO_CLK_DISABLE()                  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE)

/**
  * @brief  LCD Control Lines management
  */
#define LCD_CS_LOW()      GPIO_WriteBit(LCD_CS_GPIO_PORT, LCD_CS_PIN, Bit_RESET)
#define LCD_CS_HIGH()     GPIO_WriteBit(LCD_CS_GPIO_PORT, LCD_CS_PIN, Bit_SET)
#define LCD_DC_LOW()      GPIO_WriteBit(LCD_DC_GPIO_PORT, LCD_DC_PIN, Bit_RESET)
#define LCD_DC_HIGH()     GPIO_WriteBit(LCD_DC_GPIO_PORT, LCD_DC_PIN, Bit_SET)
     
/*##################### ADC1 ###################################*/
/**
  * @brief  ADC Interface pins
  *         used to detect motion of Joystick available on Adafruit 1.8" TFT shield
  */
#define NUCLEO_ADCx                                 ADC1
#define NUCLEO_ADCx_CLK_ENABLE()                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE)
    
#define NUCLEO_ADCx_GPIO_PORT                       GPIOB
#define NUCLEO_ADCx_GPIO_PIN                        GPIO_Pin_0
#define NUCLEO_ADCx_GPIO_CLK_ENABLE()               RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE)
#define NUCLEO_ADCx_GPIO_CLK_DISABLE()              RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,DISABLE)
    

/** @defgroup STM32L1XX_NUCLEO_Exported_Functions
  * @{
  */
uint32_t        BSP_GetVersion(void);
/** @addtogroup STM32L1XX_NUCLEO_LED_Functions
  * @{
  */ 



/**
  * @}
  */

/** @addtogroup STM32L1XX_NUCLEO_BUTTON_Functions
  * @{
  */

void            BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
uint32_t        BSP_PB_GetState(Button_TypeDef Button);

#ifdef HAL_ADC_MODULE_ENABLED
uint8_t          BSP_JOY_Init(void);
JOYState_TypeDef BSP_JOY_GetState(void);
#endif /* HAL_ADC_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L1XX_NUCLEO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
