/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_program.c      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : KPD                                             **
 **                                                                           **
 **===========================================================================**
 */

#include <stdint.h>
#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "STK_interface.h"
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

/**
 * @fn     KPD_enumInit
 * @brief  Initialize keypad pins configuration
 * @param  Config[in]: Pointer to keypad configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t KPD_enumInit(const KPD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;
  uint8_t Local_Counter;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure row pins as inputs with pull-up */
    PinConfig.Port = Config->RowsPort;
    PinConfig.Mode = KPD_ROW_MODE;
    PinConfig.Pull = GPIO_PULL_UP;

    for (Local_Counter = 0; Local_Counter < KPD_ROWS && Local_ErrorState == OK; Local_Counter++)
    {
      PinConfig.PinNum = Config->RowPins[Local_Counter];
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Configure column pins as outputs */
    if (Local_ErrorState == OK)
    {
      PinConfig.Port = Config->ColsPort;
      PinConfig.Mode = KPD_COL_MODE;
      PinConfig.Pull = GPIO_NO_PULL;

      for (Local_Counter = 0; Local_Counter < KPD_COLS && Local_ErrorState == OK; Local_Counter++)
      {
        PinConfig.PinNum = Config->ColPins[Local_Counter];
        Local_ErrorState = GPIO_enumPinInit(&PinConfig);

        if (Local_ErrorState == OK)
        {
          /* Set columns to high initially */
          Local_ErrorState = GPIO_enumSetPinValue(Config->ColsPort, Config->ColPins[Local_Counter], GPIO_PIN_HIGH);
        }
      }
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     KPD_enumGetPressedKey
 * @brief  Get the currently pressed key
 * @param  Config[in]: Pointer to keypad configuration structure
 * @param  Key[out]: Pointer to store the pressed key value
 * @retval ErrorState_t: OK if successful, NOK if error
 * @note   Returns 0xFF if no key is pressed
 */
ErrorState_t KPD_enumGetPressedKey(const KPD_Config_t *Config, uint8_t *Key)
{
  ErrorState_t Local_ErrorState = OK;
  uint8_t Local_RowCounter, Local_ColCounter;
  GPIO_PinValue_t Local_PinValue;

  if (Config == NULL || Key == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    *Key = KPD_NO_PRESSED_KEY;

    /* Scan all columns */
    for (Local_ColCounter = 0; Local_ColCounter < KPD_COLS && *Key == KPD_NO_PRESSED_KEY && Local_ErrorState == OK; Local_ColCounter++)
    {
      /* Set current column to low */
      Local_ErrorState = GPIO_enumSetPinValue(Config->ColsPort, Config->ColPins[Local_ColCounter], GPIO_PIN_LOW);

      if (Local_ErrorState == OK)
      {
        /* Add small delay for signal stabilization */
        STK_enumSetBusyWait(KPD_SCAN_DELAY_US);

        /* Check all rows */
        for (Local_RowCounter = 0; Local_RowCounter < KPD_ROWS && *Key == KPD_NO_PRESSED_KEY && Local_ErrorState == OK; Local_RowCounter++)
        {
          Local_ErrorState = GPIO_enumGetPinValue(Config->RowsPort, Config->RowPins[Local_RowCounter], &Local_PinValue);

          if (Local_ErrorState == OK && Local_PinValue == GPIO_PIN_LOW)
          {
            /* Key is pressed, get its value from the mapping matrix */
            *Key = Config->Keys[Local_RowCounter][Local_ColCounter];
          }
        }

        /* Set column back to high */
        if (Local_ErrorState == OK)
        {
          Local_ErrorState = GPIO_enumSetPinValue(Config->ColsPort, Config->ColPins[Local_ColCounter], GPIO_PIN_HIGH);
        }
      }
    }
  }

  return Local_ErrorState;
}