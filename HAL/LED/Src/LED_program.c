/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_program.c      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : LED                                             **
 **                                                                           **
 **===========================================================================**
 */

#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

/**
 * @fn     LED_enumInit
 * @brief  Initialize LED pin configuration
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumInit(const LED_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure GPIO pin for LED */
    PinConfig.Port = Config->Port;
    PinConfig.PinNum = Config->Pin;
    PinConfig.Mode = LED_DEFAULT_OUTPUT_MODE;
    /* Pull-up/down not needed for output mode */
    PinConfig.Pull = GPIO_PULL_DOWN;

    /* Initialize GPIO pin */
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);

    /* Set initial state to OFF */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = LED_enumTurnOff(Config);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     LED_enumTurnOn
 * @brief  Turn on the LED
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumTurnOn(const LED_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set pin value based on connection type */
    GPIO_PinValue_t PinValue = (Config->ConnectionType == LED_ACTIVE_HIGH) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;

    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin, PinValue);
  }

  return Local_ErrorState;
}

/**
 * @fn     LED_enumTurnOff
 * @brief  Turn off the LED
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumTurnOff(const LED_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set pin value based on connection type */
    GPIO_PinValue_t PinValue = (Config->ConnectionType == LED_ACTIVE_HIGH) ? GPIO_PIN_LOW : GPIO_PIN_HIGH;

    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin, PinValue);
  }

  return Local_ErrorState;
}

/**
 * @fn     LED_enumToggle
 * @brief  Toggle the LED state
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumToggle(const LED_Config_t *Config)
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