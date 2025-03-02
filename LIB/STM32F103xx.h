/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    STM32F103xx.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : LIB                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : STM32F103xx                                     **
 **                                                                           **
 **===========================================================================**
 */

#ifndef STM32F103xx_H
#define STM32F103xx_H

#include <stdint.h>

/**************************************         Various Memories Base Adresses          ******************************************/
#define FLASH_BASEADDR 0x08000000UL
#define SRAM_BASEADDR  0x20000000UL
#define ROM_BASEADDR   0x1FFFF000UL

/**************************************         AHB Peripheral Base Adresses          ******************************************/
#define GPIOA_BASEADDR 0x40010800UL
#define GPIOB_BASEADDR 0x40010C00UL
#define GPIOC_BASEADDR 0x40011000UL
#define GPIOD_BASEADDR 0x40011400UL
#define GPIOE_BASEADDR 0x40011800UL

#define RCC_BASEADDR   0x40021000UL

#define SYSTIC_BASEADDR 0xE000E010UL

/**************************************         APB1 Peripheral Base Adresses          ******************************************/
/**************************************         APB2 Peripheral Base Adresses          ******************************************/

/**************************************         SYSTIC Peripheral Definitions       *********************************************/

typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
} SYSTIC_RegDef_t;

#define MSYSTIC ((SYSTIC_RegDef_t *)SYSTIC_BASEADDR)

/**************************************       GPIO Register Definition Structure       ******************************************/
typedef struct
{
  volatile uint32_t CRL;  /* Port configuration register low  */
  volatile uint32_t CRH;  /* Port configuration register high */
  volatile uint32_t IDR;  /* Port input data register        */
  volatile uint32_t ODR;  /* Port output data register       */
  volatile uint32_t BSRR; /* Port bit set/reset register     */
  volatile uint32_t BRR;  /* Port bit reset register         */
  volatile uint32_t LCKR; /* Port configuration lock register*/
} GPIO_REGDEF_t;

/**************************************       RCC Register Definitions Structure       ******************************************/
typedef struct
{
  volatile uint32_t CR;       /* Clock control register */
  volatile uint32_t CFGR;     /* Clock configuration register */
  volatile uint32_t CIR;      /* Clock interrupt register */
  volatile uint32_t APB2RSTR; /* APB2 peripheral reset register */
  volatile uint32_t APB1RSTR; /* APB1 peripheral reset register */
  volatile uint32_t AHBENR;   /* AHB peripheral clock enable register */
  volatile uint32_t APB2ENR;  /* APB2 peripheral clock enable register */
  volatile uint32_t APB1ENR;  /* APB1 peripheral clock enable register */
  volatile uint32_t BDCR;     /* Backup domain control register */
  volatile uint32_t CSR;      /* Control/status register */
} RCC_RegDef_t;

/**************************************         GPIO Peripheral Definitions       ******************************************/

#define MGPIOA ((GPIO_REGDEF_t *)GPIOA_BASEADDR)
#define MGPIOB ((GPIO_REGDEF_t *)GPIOB_BASEADDR)
#define MGPIOC ((GPIO_REGDEF_t *)GPIOC_BASEADDR)
#define MGPIOD ((GPIO_REGDEF_t *)GPIOD_BASEADDR)
#define MGPIOE ((GPIO_REGDEF_t *)GPIOE_BASEADDR)

/**************************************         RCC Peripheral Definitions       *********************************************/

#define MRCC ((RCC_RegDef_t *)RCC_BASEADDR)

#endif /* STM32F103xx_H */
