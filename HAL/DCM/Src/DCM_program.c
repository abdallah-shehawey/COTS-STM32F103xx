/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    DCM_program.c      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : DCM                                             **
 **                                                                           **
 **===========================================================================**
 */

#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "DCM_interface.h"
#include "DCM_private.h"
#include "DCM_config.h"

/**
 * @fn     DCM_enumInit
 * @brief  Initialize DC motor pins
 * @param  Config[in]: Pointer to motor configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t DCM_enumInit(const DCM_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure motor pins */
    PinConfig.Port = Config->Port;
    PinConfig.Mode = DCM_PIN_MODE;
    PinConfig.Pull = GPIO_NO_PULL;

    /* Configure Pin1 */
    PinConfig.PinNum = Config->Pin1;
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);

    /* Configure Pin2 */
    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->Pin2;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Initially stop the motor */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = DCM_enumSetState(Config, DCM_STOP);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     DCM_enumSetState
 * @brief  Set motor rotation state
 * @param  Config[in]: Pointer to motor configuration structure
 * @param  State[in]: Motor state (CW, CCW, or STOP)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t DCM_enumSetState(const DCM_Config_t *Config, DCM_State_t State)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    switch (State)
    {
    case DCM_CW:
      /* Set Pin1 HIGH and Pin2 LOW for clockwise rotation */
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin1, GPIO_PIN_HIGH);
      if (Local_ErrorState == OK)
      {
        Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin2, GPIO_PIN_LOW);
      }
      break;

    case DCM_CCW:
      /* Set Pin1 LOW and Pin2 HIGH for counter-clockwise rotation */
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin1, GPIO_PIN_LOW);
      if (Local_ErrorState == OK)
      {
        Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin2, GPIO_PIN_HIGH);
      }
      break;

    case DCM_STOP:
      /* Set both pins LOW to stop the motor */
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin1, GPIO_PIN_LOW);
      if (Local_ErrorState == OK)
      {
        Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->Pin2, GPIO_PIN_LOW);
      }
      break;

    default:
      Local_ErrorState = NOK;
      break;
    }
  }

  return Local_ErrorState;
}