/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    RCC_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : F103C8T6                                        **
 **                  SWC    : RCC                                             **
 **                                                                           **
 **===========================================================================**
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_MACROS.h"

#include <stdint.h>

#include "RCC_config.h"
#include "RCC_interface.h"
#include "RCC_register.h"
#include "RCC_private.h"

static u8 RCC_u8State = IDLE;

ErrorStatus RCC_enumSetClkSts(uint8_t Copy_u8CLK, uint8_t Copy_u8Status)
{
  u8 Local_u8ErrorState = OK;
  u32 Local_u32TimeoutCounter = 0;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8CLK == HSI_CLK)
    {

      if (Copy_u8Status == CLK_ON)
      {
        SET_BIT(MRCC_t->CR, 0);
        while(READ_BIT(MRCC_t->CR, 1) == 0 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_u8ErrorState = TIMEOUT_STATE;
        }

      }
      else if (Copy_u8Status == CLK_OFF)
      {

        CLR_BIT(MRCC_t->CR, 0);
        while(READ_BIT(MRCC_t->CR, 1) == 1 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_u8ErrorState = TIMEOUT_STATE;
        }

      }
      else
      {

      }
    }
    else if (Copy_u8CLK == HSE_CLK)
    {
      if (Copy_u8Status == CLK_ON)
      {
        SET_BIT(MRCC_t->CR, 18);
        SET_BIT(MRCC_t->CR, 16);
        while(READ_BIT(MRCC_t->CR, 17) == 0 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_u8ErrorState = TIMEOUT_STATE;
        }
      }

      else if (Copy_u8Status == CLK_OFF)
      {
        CLR_BIT(MRCC_t->CR, 16);
        while(READ_BIT(MRCC_t->CR, 17) == 1 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_u8ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }
    }
    else if (Copy_u8CLK == PLL_CLK)
    {
      if (Copy_u8Status == CLK_ON)
      {
        SET_BIT(MRCC_t->CR, 24);
        while(READ_BIT(MRCC_t->CR, 25) == 0 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_u8ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }

      else if (Copy_u8Status == CLK_OFF)
      {
        CLR_BIT(MRCC_t->CR, 24);
        while(READ_BIT(MRCC_t->CR, 25) == 1 && Local_u32TimeoutCounter != RCC_u32TIMEOUT)
        {
          Local_u32TimeoutCounter++;
        }

        if (Local_u32TimeoutCounter == RCC_u32TIMEOUT)
        {
          Local_u8ErrorState = TIMEOUT_STATE;
        }
        else
        {

        }
      }

    }
    else
    {

    }

    RCC_u8State = IDLE;

  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

ErrorStatus RCC_enumSetSysClk(uint8_t Copy_u8CLK)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    switch(Copy_u8CLK)
    {
    case HSI_CLK:
      MRCC_t->CFGR &= ~(SYS_CLK_MASK);
      MRCC_t->CFGR |= Copy_u8CLK;
      break;

    case HSE_CLK:
      MRCC_t->CFGR &= ~(SYS_CLK_MASK);
      MRCC_t->CFGR |= Copy_u8CLK;
      break;

    case PLL_CLK:
      MRCC_t->CFGR &= ~(SYS_CLK_MASK);
      MRCC_t->CFGR |= Copy_u8CLK;
      break;

    default:
      break;
    }

    RCC_u8State = IDLE;
  }

  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

ErrorStatus RCC_enumPLLConfig(uint8_t Copy_u8PLLSrc, uint8_t Copy_u8PLLMul)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if ((Copy_u8PLLMul >= PLL_MUL_2 || Copy_u8PLLMul <= PLL_MUL_16) && (Copy_u8PLLSrc == PLL_HSI || Copy_u8PLLSrc == PLL_HSE || Copy_u8PLLSrc == PLL_HSE_DIV_2))
    {
      if (Copy_u8PLLSrc == PLL_HSI)
      {
        CLR_BIT(MRCC_t->CFGR, 16);
      }

      else if (Copy_u8PLLSrc == PLL_HSE || Copy_u8PLLSrc == PLL_HSE_DIV_2)
      {
        if (Copy_u8PLLSrc == PLL_HSE)
        {
          CLR_BIT(MRCC_t->CFGR, 17);
        }

        else if (Copy_u8PLLSrc == PLL_HSE_DIV_2)
        {
          SET_BIT(MRCC_t->CFGR, 17);
        }

        SET_BIT(MRCC_t->CFGR, 16);
      }
      else
      {
      }

      /* To Multiply PLL after set it's source */
      MRCC_t->CFGR &= (~(PLL_CONFIG_MASK << 18));
      MRCC_t->CFGR |= (Copy_u8PLLMul << 18);

    }
    else
    {
      Local_u8ErrorState = NOK;
    }

    RCC_u8State = IDLE;
  }
  return Local_u8ErrorState;
}

ErrorStatus RCC_enumAHBConfig(uint8_t Copy_u8AHPDiv)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8AHPDiv >= AHB_NOT_DIV || Copy_u8AHPDiv <= AHB_DIV_512)
    {
      MRCC_t->CFGR &= (~(0xF << 4));
      MRCC_t->CFGR |= (Copy_u8AHPDiv << 4);
    }
    else
    {
      Local_u8ErrorState = NOK;
    }

    RCC_u8State = IDLE;
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

ErrorStatus RCC_enumAPB1Config(uint8_t Copy_u8APB1Div)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8APB1Div >= APB_NOT_DIV || Copy_u8APB1Div <= APB_DIV_16)
    {
      MRCC_t->CFGR &= (~(0x7 << 8));
      MRCC_t->CFGR |= (Copy_u8APB1Div << 8);
    }
    else
    {
      Local_u8ErrorState = NOK;
    }

    RCC_u8State = IDLE;
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

ErrorStatus RCC_enumAPB2Config(uint8_t Copy_u8APB2Div)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8APB2Div >= APB_NOT_DIV || Copy_u8APB2Div <= APB_DIV_16)
    {
      MRCC_t->CFGR &= (~(0x7 << 11));
      MRCC_t->CFGR |= (Copy_u8APB2Div << 11);
    }
    else
    {
      Local_u8ErrorState = NOK;
    }
    RCC_u8State = IDLE;
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

ErrorStatus RCC_enumAHPPerSts(uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;

    if (Copy_u8Status == PER_ON)
    {
      SET_BIT(MRCC_t->AHPENR, Copy_u8AHPPer);
    }
    else if (Copy_u8Status == PER_OFF)
    {
      CLR_BIT(MRCC_t->AHPENR, Copy_u8AHPPer);
    }
    else
    {

    }

    RCC_u8State = IDLE;
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

ErrorStatus RCC_enumABPPerSts(uint8_t Copy_u8Bus, uint8_t Copy_u8AHPPer, uint8_t Copy_u8Status)
{
  u8 Local_u8ErrorState = OK;

  if (RCC_u8State == IDLE)
  {
    RCC_u8State = BUSY;
    switch(Copy_u8Bus)
    {
    case APB1:
      if (Copy_u8Status == PER_ON)
      {
        SET_BIT(MRCC_t->APB1ENR, Copy_u8AHPPer);
      }
      else if (Copy_u8Status == PER_OFF)
      {
        CLR_BIT(MRCC_t->APB1ENR, Copy_u8AHPPer);
      }
      else
      {

      }
      break;
    case APB2:
      if (Copy_u8Status == PER_ON)
      {
        SET_BIT(MRCC_t->APB2ENR, Copy_u8AHPPer);
      }
      else if (Copy_u8Status == PER_OFF)
      {
        CLR_BIT(MRCC_t->APB2ENR, Copy_u8AHPPer);
      }
      else
      {

      }
      break;

    default:
      break;
    }


    RCC_u8State = IDLE;
  }
  else
  {
    Local_u8ErrorState = BUSY_STATE;
  }

  return Local_u8ErrorState;
}

