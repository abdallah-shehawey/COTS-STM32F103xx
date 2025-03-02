/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<    SYSTIC_program.c     >>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SYSTIC                                          **
 **                                                                           **
 **===========================================================================**
 */

#include <stdint.h>
#include "STM32F103xx.h"
#include "ErrorStates.h"
#include "SYSTIC_interface.h"
#include "SYSTIC_private.h"
#include "SYSTIC_config.h"

/* Private variables */
static void (*SYSTICK_CallBack)(void) = NULL;
static uint8_t SYSTICK_IntervalMode;

/**
 * @fn     SYSTICK_enumInit
 * @brief  Initialize the SysTick timer with configured settings
 * @param  ClockSource: Clock source for SysTick (AHB or AHB/8)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumInit(SYSTICK_CLKSource_t ClockSource)
{
  ErrorState_t Local_ErrorState = OK;

  /* Disable SysTick first */
  MSYSTIC->CTRL = 0;

  /* Configure clock source */
  if (ClockSource == SYSTICK_CLK_AHB)
  {
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_CLKSOURCE);
  }
  /* else AHB/8 is selected by default */

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumSetPreloadValue
 * @brief  Set the preload value for SysTick timer
 * @param  Copy_u32Value: Value to be loaded (0 to 0x00FFFFFF)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumSetPreloadValue(uint32_t Copy_u32Value)
{
  ErrorState_t Local_ErrorState = OK;

  if (Copy_u32Value > SYSTICK_LOAD_RELOAD_MSK)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    MSYSTIC->LOAD = Copy_u32Value;
    MSYSTIC->VAL = 0; /* Clear current value */
  }

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumGetCurrentValue
 * @brief  Get the current value of SysTick timer
 * @param  Copy_u32Value[out]: Pointer to store current value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumGetCurrentValue(uint32_t *Copy_u32Value)
{
  ErrorState_t Local_ErrorState = OK;

  if (Copy_u32Value == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    *Copy_u32Value = MSYSTIC->VAL & SYSTICK_VAL_CURRENT;
  }

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumDelayMs
 * @brief  Generate a delay in milliseconds using polling method
 * @param  Copy_u32TimeMs: Time in milliseconds to delay
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumDelayMs(uint32_t Copy_u32TimeMs)
{
  ErrorState_t Local_ErrorState = OK;
  uint32_t Local_u32Ticks;
  uint32_t Local_u32PreloadValue;

  /* Calculate number of ticks needed */
  if (MSYSTIC->CTRL & (1 << SYSTICK_CTRL_CLKSOURCE))
  {
    Local_u32Ticks = (SYSTEM_CLOCK_FREQ / 1000) * Copy_u32TimeMs;
  }
  else
  {
    Local_u32Ticks = (SYSTEM_CLOCK_FREQ / 8000) * Copy_u32TimeMs;
  }

  /* Check if ticks exceed maximum value */
  if (Local_u32Ticks > SYSTICK_LOAD_RELOAD_MSK)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Configure SysTick */
    Local_u32PreloadValue = Local_u32Ticks - 1;
    MSYSTIC->LOAD = Local_u32PreloadValue;
    MSYSTIC->VAL = 0;
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_ENABLE); /* Enable counter */

    /* Wait until flag is raised */
    while (!(MSYSTIC->CTRL & (1 << SYSTICK_CTRL_COUNTFLAG)))
      ;

    /* Stop timer */
    MSYSTIC->CTRL &= ~(1 << SYSTICK_CTRL_ENABLE);
    MSYSTIC->LOAD = 0;
    MSYSTIC->VAL = 0;
  }

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumDelayUs
 * @brief  Generate a delay in microseconds using polling method
 * @param  Copy_u32TimeUs: Time in microseconds to delay
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumDelayUs(uint32_t Copy_u32TimeUs)
{
  ErrorState_t Local_ErrorState = OK;
  uint32_t Local_u32Ticks;
  uint32_t Local_u32PreloadValue;

  /* Calculate number of ticks needed */
  if (MSYSTIC->CTRL & (1 << SYSTICK_CTRL_CLKSOURCE))
  {
    Local_u32Ticks = (SYSTEM_CLOCK_FREQ / 1000000) * Copy_u32TimeUs;
  }
  else
  {
    Local_u32Ticks = (SYSTEM_CLOCK_FREQ / 8000000) * Copy_u32TimeUs;
  }

  /* Check if ticks exceed maximum value */
  if (Local_u32Ticks > SYSTICK_LOAD_RELOAD_MSK)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Configure SysTick */
    Local_u32PreloadValue = Local_u32Ticks - 1;
    MSYSTIC->LOAD = Local_u32PreloadValue;
    MSYSTIC->VAL = 0;
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_ENABLE); /* Enable counter */

    /* Wait until flag is raised */
    while (!(MSYSTIC->CTRL & (1 << SYSTICK_CTRL_COUNTFLAG)))
      ;

    /* Stop timer */
    MSYSTIC->CTRL &= ~(1 << SYSTICK_CTRL_ENABLE);
    MSYSTIC->LOAD = 0;
    MSYSTIC->VAL = 0;
  }

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumSetIntervalSingle
 * @brief  Set up SysTick for single interval interrupt
 * @param  Copy_u32Ticks: Number of ticks before interrupt
 * @param  CallBack: Function to call when interval completes
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumSetIntervalSingle(uint32_t Copy_u32Ticks, void (*CallBack)(void))
{
  ErrorState_t Local_ErrorState = OK;

  if (CallBack == NULL || Copy_u32Ticks > SYSTICK_LOAD_RELOAD_MSK)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Store callback and interval mode */
    SYSTICK_CallBack = CallBack;
    SYSTICK_IntervalMode = SYSTICK_SINGLE_INTERVAL;

    /* Configure SysTick */
    MSYSTIC->LOAD = Copy_u32Ticks - 1;
    MSYSTIC->VAL = 0;
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_TICKINT); /* Enable interrupt */
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_ENABLE);  /* Enable counter */
  }

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumSetIntervalPeriodic
 * @brief  Set up SysTick for periodic interval interrupt
 * @param  Copy_u32Ticks: Number of ticks for each interval
 * @param  CallBack: Function to call when each interval completes
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumSetIntervalPeriodic(uint32_t Copy_u32Ticks, void (*CallBack)(void))
{
  ErrorState_t Local_ErrorState = OK;

  if (CallBack == NULL || Copy_u32Ticks > SYSTICK_LOAD_RELOAD_MSK)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Store callback and interval mode */
    SYSTICK_CallBack = CallBack;
    SYSTICK_IntervalMode = SYSTICK_PERIODIC_INTERVAL;

    /* Configure SysTick */
    MSYSTIC->LOAD = Copy_u32Ticks - 1;
    MSYSTIC->VAL = 0;
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_TICKINT); /* Enable interrupt */
    MSYSTIC->CTRL |= (1 << SYSTICK_CTRL_ENABLE);  /* Enable counter */
  }

  return Local_ErrorState;
}

/**
 * @fn     SYSTICK_enumStop
 * @brief  Stop the SysTick timer
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumStop(void)
{
  ErrorState_t Local_ErrorState = OK;

  /* Disable counter and interrupt */
  MSYSTIC->CTRL &= ~(1 << SYSTICK_CTRL_ENABLE);
  MSYSTIC->CTRL &= ~(1 << SYSTICK_CTRL_TICKINT);

  /* Clear registers */
  MSYSTIC->LOAD = 0;
  MSYSTIC->VAL = 0;

  /* Clear callback */
  SYSTICK_CallBack = NULL;

  return Local_ErrorState;
}

/**
 * @fn     SysTick_Handler
 * @brief  SysTick interrupt handler
 */
void SysTick_Handler(void)
{
  if (SYSTICK_CallBack != NULL)
  {
    if (SYSTICK_IntervalMode == SYSTICK_SINGLE_INTERVAL)
    {
      /* Stop timer in single interval mode */
      SYSTICK_enumStop();
    }

    /* Call the callback function */
    SYSTICK_CallBack();
  }
}