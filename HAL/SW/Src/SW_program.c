/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    SW_program.c       >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SW                                             **
 **                                                                           **
 **===========================================================================**
 */

#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"

/**
 * @fn     SW_enumInit
 * @brief  Initialize switch pin configuration
 * @param  Config[in]: Pointer to switch configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SW_enumInit(const SW_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure GPIO pin for switch */
    PinConfig.Port = Config->Port;
    PinConfig.PinNum = Config->Pin;
    PinConfig.Mode = (Config->ConnectionType == SW_PULL_UP) ? SW_PULL_UP_MODE : SW_PULL_DOWN_MODE;
    PinConfig.Pull = (Config->ConnectionType == SW_PULL_UP) ? GPIO_PULL_UP : GPIO_PULL_DOWN;

    /* Initialize GPIO pin */
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);
  }

  return Local_ErrorState;
}

/**
 * @fn     SW_enumGetState
 * @brief  Get the current state of the switch
 * @param  Config[in]: Pointer to switch configuration structure
 * @param  State[out]: Pointer to store switch state
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SW_enumGetState(const SW_Config_t *Config, SW_State_t *State)
{
  ErrorState_t Local_ErrorState = OK;
  GPIO_PinValue_t PinValue;

  if (Config == NULL || State == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Read the pin value */
    Local_ErrorState = GPIO_enumGetPinValue(Config->Port, Config->Pin, &PinValue);

    if (Local_ErrorState == OK)
    {
      /* Determine switch state based on connection type and pin value */
      if (Config->ConnectionType == SW_PULL_UP)
      {
        *State = (PinValue == GPIO_PIN_LOW) ? SW_PRESSED : SW_NOT_PRESSED;
      }
      else /* SW_PULL_DOWN */
      {
        *State = (PinValue == GPIO_PIN_HIGH) ? SW_PRESSED : SW_NOT_PRESSED;
      }
    }
  }

  return Local_ErrorState;
}