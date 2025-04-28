/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    BUZZ_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : BUZZ                                            **
 **                                                                           **
 **===========================================================================**
 */

#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "BUZZ_interface.h"
#include "BUZZ_private.h"
#include "BUZZ_config.h"

/**
 * @fn     BUZZ_enumInit
 * @brief  Initialize buzzer pin configuration
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumInit(const BUZZ_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure GPIO pin for buzzer */
    PinConfig.Port = Config->Port;
    PinConfig.PinNum = Config->Pin;
    PinConfig.Mode = BUZZ_OUTPUT_MODE;
    PinConfig.Pull = GPIO_NO_PULL;

    /* Initialize GPIO pin */
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);

    /* Set initial state to OFF */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = BUZZ_enumTurnOff(Config);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     BUZZ_enumTurnOn
 * @brief  Turn on the buzzer
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumTurnOn(const BUZZ_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set pin value based on connection type */
    GPIO_PinValue_t PinValue = (Config->ConnectionType == BUZZ_ACTIVE_HIGH) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin, PinValue);
  }

  return Local_ErrorState;
}

/**
 * @fn     BUZZ_enumTurnOff
 * @brief  Turn off the buzzer
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumTurnOff(const BUZZ_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set pin value based on connection type */
    GPIO_PinValue_t PinValue = (Config->ConnectionType == BUZZ_ACTIVE_HIGH) ? GPIO_PIN_LOW : GPIO_PIN_HIGH;
    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin, PinValue);
  }

  return Local_ErrorState;
}

/**
 * @fn     BUZZ_enumToggle
 * @brief  Toggle the buzzer state
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumToggle(const BUZZ_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    Local_ErrorState = GPIO_enumTogglePinValue(Config->Port, Config->Pin);
  }

  return Local_ErrorState;
}