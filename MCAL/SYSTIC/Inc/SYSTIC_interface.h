/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<    SYSTIC_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SYSTIC                                          **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_SYSTIC_INTERFACE_H_
#define MCAL_SYSTIC_INTERFACE_H_

#include <stdint.h>
#include "ErrorStates.h"

/************************** Clock Source Options **************************/
typedef enum
{
  SYSTICK_CLK_AHB_DIV8 = 0, /* AHB Clock divided by 8 */
  SYSTICK_CLK_AHB           /* AHB Clock */
} SYSTICK_CLKSource_t;

/************************** Function Prototypes **************************/

/**
 * @fn     SYSTICK_enumInit
 * @brief  Initialize the SysTick timer with configured settings
 * @param  ClockSource: Clock source for SysTick (AHB or AHB/8)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumInit(SYSTICK_CLKSource_t ClockSource);

/**
 * @fn     SYSTICK_enumSetPreloadValue
 * @brief  Set the preload value for SysTick timer
 * @param  Copy_u32Value: Value to be loaded (0 to 0x00FFFFFF)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumSetPreloadValue(uint32_t Copy_u32Value);

/**
 * @fn     SYSTICK_enumGetCurrentValue
 * @brief  Get the current value of SysTick timer
 * @param  Copy_u32Value[out]: Pointer to store current value
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumGetCurrentValue(uint32_t *Copy_u32Value);

/**
 * @fn     SYSTICK_enumDelayMs
 * @brief  Generate a delay in milliseconds using polling method
 * @param  Copy_u32TimeMs: Time in milliseconds to delay
 * @retval ErrorState_t: OK if successful, NOK if error
 * @note   This function blocks until the delay is complete
 */
ErrorState_t SYSTICK_enumDelayMs(uint32_t Copy_u32TimeMs);

/**
 * @fn     SYSTICK_enumDelayUs
 * @brief  Generate a delay in microseconds using polling method
 * @param  Copy_u32TimeUs: Time in microseconds to delay
 * @retval ErrorState_t: OK if successful, NOK if error
 * @note   This function blocks until the delay is complete
 */
ErrorState_t SYSTICK_enumDelayUs(uint32_t Copy_u32TimeUs);

/**
 * @fn     SYSTICK_enumSetIntervalSingle
 * @brief  Set up SysTick for single interval interrupt
 * @param  Copy_u32Ticks: Number of ticks before interrupt
 * @param  CallBack: Function to call when interval completes
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumSetIntervalSingle(uint32_t Copy_u32Ticks, void (*CallBack)(void));

/**
 * @fn     SYSTICK_enumSetIntervalPeriodic
 * @brief  Set up SysTick for periodic interval interrupt
 * @param  Copy_u32Ticks: Number of ticks for each interval
 * @param  CallBack: Function to call when each interval completes
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumSetIntervalPeriodic(uint32_t Copy_u32Ticks, void (*CallBack)(void));

/**
 * @fn     SYSTICK_enumStop
 * @brief  Stop the SysTick timer
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SYSTICK_enumStop(void);

#endif /* MCAL_SYSTIC_INTERFACE_H_ */