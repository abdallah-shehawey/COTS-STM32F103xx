/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_register.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : F103C8T6                                        **
 **                  SWC    : RCC                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_RCC_REGISTERS_H_
#define MCAL_RCC_REGISTERS_H_

typedef struct
{
  volatile uint32_t CR;           //Clock control register (RCC_CR)
  volatile uint32_t CFGR;         //Clock configuration register (RCC_CFGR)
  volatile uint32_t CIR;          //Clock interrupt register (RCC_CIR)
  volatile uint32_t APB2RSTR;     //APB2 peripheral reset register (RCC_APB2RSTR)
  volatile uint32_t APB1RSTR;     //APB1 peripheral reset register (RCC_APB1RSTR)
  volatile uint32_t AHPENR;       //AHB peripheral clock enable register (RCC_AHBENR)
  volatile uint32_t APB2ENR;      //APB2 peripheral clock enable register (RCC_APB2ENR)
  volatile uint32_t APB1ENR;      //APB1 peripheral clock enable register (RCC_APB1ENR)
  volatile uint32_t BDCR;         //Backup domain control register (RCC_BDCR)
  volatile uint32_t CSR;          //Control/status register (RCC_CSR)
}RCC_t;

#define MRCC_t ((volatile RCC_t *)0X40021000)
/* You Can Access any Regsiter using MRCC_t->RegisterName */

#endif /* MCAL_RCC_REGISTERS_H_ */
