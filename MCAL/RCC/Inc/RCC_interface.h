/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<   RCC_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : F103C8T6                                        **
 **                  SWC    : RCC                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_RCC_INTERFACE_H_
#define MCAL_RCC_INTERFACE_H_

#include <stdint.h>
#include "ErrTypes.h"

/* Define Bus in uC*/
typedef enum
{
  AHB1,
  APB1,
  APB2,
} uC_BUS_t;

/* Define peripheral at AHB BUS */
typedef enum
{
  RCC_DMA1EN,
  RCC_DMA2EN,
  RCC_SRAMEN,
  RCC_FLITFE = 4,
  RCC_CRCEN = 6,
  RCC_FSMCEN = 8,
  RCC_SDIOEN = 10,
} AHB_BUS_t;

/* Define peripheral at APB2 BUS */
typedef enum
{
  AFIOEN,
  IOPAEN = 2,
  IOPBEN,
  IOPCEN = 4,
  IOPDEN,
  IOPEEN,
  IOPFEN,
  IOPGEN,
  ADC1EN,
  ADC2EN,
  TIM1EN,
  SPI1EN,
  TIM8EN,
  USART1EN,
  ADC3EN,
  TIM9EN = 19,
  TIM10EN,
  TIM11EN,
} APB2_BUS_t;

/* Define peripheral at APB1 BUS */
typedef enum
{
  TIM2EN,
  TIM3EN,
  TIM4EN,
  TIM5EN,
  TIM6EN,
  TIM7EN,
  TIM12EN,
  TIM13EN,
  TIM14EN,
  WWDGEN = 11,
  SPI2EN = 14,
  SPI3EN,
  USART2EN = 17,
  USART3EN,
  USART4EN,
  USART5EN,
  I2C1EN,
  I2C2EN,
  USBEN,
  CANEN = 25,
  BKPEN = 27,
  PWREN,
  DACEN,
} APB1_BUS_t;

/* Define Prescaller for HSE */
typedef enum
{
  HSE_NOT_DIV        ,
  HSE_DIV_2          ,
}HSE_PRE_t           ;

/* Define Division Factor To AHP */
typedef enum
{
  AHB_NOT_DIV = 7    ,
  AHB_DIV_2          ,
  AHB_DIV_4          ,
  AHB_DIV_8          ,
  AHB_DIV_16         ,
  AHB_DIV_64         ,
  AHB_DIV_128        ,
  AHB_DIV_256        ,
  AHB_DIV_512        ,
}AHB_BUS_DIV_t;

/* Define Division Factor To APB */
typedef enum
{
  APB_NOT_DIV = 3    ,
  APB_DIV_2          ,
  APB_DIV_4          ,
  APB_DIV_8          ,
  APB_DIV_16         ,
}APB_BUS_DIV_t       ;

/* Define Multiplication Factor To PLL */
typedef enum
{
  PLL_MUL_2          ,
  PLL_MUL_3          ,
  PLL_MUL_4          ,
  PLL_MUL_5          ,
  PLL_MUL_6          ,
  PLL_MUL_7          ,
  PLL_MUL_8          ,
  PLL_MUL_9          ,
  PLL_MUL_10         ,
  PLL_MUL_11         ,
  PLL_MUL_12         ,
  PLL_MUL_13         ,
  PLL_MUL_14         ,
  PLL_MUL_15         ,
  PLL_MUL_16         ,
}PLL_CLK_MUL         ;

/* Define Clock Source To PLL */
typedef enum
{
  PLL_HSI            ,
  PLL_HSE            ,
  PLL_HSE_DIV_2      ,
}PLL_CLK_SRC         ;

/* Define type of CLK source */
typedef enum
{
  HSI_CLK            ,
  HSE_CLK            ,
  PLL_CLK            ,
}CLK_SRC_t           ;

/* Define ON or OFF for CLK */
typedef enum
{
  CLK_ON             ,
  CLK_OFF            ,
}CLK_EN_t            ;

/* Define ON or OFF for Peripheral */
typedef enum
{
  PER_ON             ,
  PER_OFF            ,
}PER_EN_t            ;

/* functions defination */
ErrorState_t RCC_enumSetClkSts(uint8_t Copy_u8CLK, uint8_t Copy_u8Status);
ErrorState_t RCC_enumSetSysClk  (uint8_t Copy_u8CLK);
ErrorState_t RCC_enumPLLConfig(uint8_t Copy_u8PLLSrc, uint8_t Copy_u8PLLMul);
ErrorState_t RCC_enumAHBConfig(uint8_t Copy_u8AHPDiv);
ErrorState_t RCC_enumAPB1Config(uint8_t Copy_u8APB1Div);
ErrorState_t RCC_enumAPB2Config(uint8_t Copy_u8APB2Div);
ErrorState_t RCC_enumAHPPerSts(uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status);
ErrorState_t RCC_enumABPPerSts(uint8_t Copy_u8Bus, uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status);

#endif /* MCAL_RCC_INTERFACE_H_ */
