/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    BSSD_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : BSSD                                            **
 **                                                                           **
 **===========================================================================**
 */

#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "BSSD_interface.h"
#include "BSSD_private.h"
#include "BSSD_config.h"

/**
 * @fn     BSSD_enumInit
 * @brief  Initialize BCD pins
 * @param  Config[in]: Pointer to BCD configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BSSD_enumInit(const BSSD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure BCD pins */
    PinConfig.Port = Config->Port;
    PinConfig.Mode = BSSD_PIN_MODE;
    PinConfig.Pull = GPIO_NO_PULL;

    /* Configure Pin A (LSB) */
    PinConfig.PinNum = Config->PinA;
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);

    /* Configure Pin B */
    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinB;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Configure Pin C */
    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinC;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Configure Pin D (MSB) */
    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinD;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Initially display 0 */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = BSSD_enumDisplayNumber(Config, 0);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     BSSD_enumDisplayNumber
 * @brief  Display number on seven segment using BCD
 * @param  Config[in]: Pointer to BCD configuration structure
 * @param  Number[in]: Number to display (0-9)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BSSD_enumDisplayNumber(const BSSD_Config_t *Config, uint8_t Number)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL || Number > 9)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set Pin A (LSB) */
    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinA, (Number & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);

    /* Set Pin B */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinB, (Number & 0x02) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    }

    /* Set Pin C */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinC, (Number & 0x04) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    }

    /* Set Pin D (MSB) */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinD, (Number & 0x08) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    }
  }

  return Local_ErrorState;
}