/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_program.c      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SSD                                             **
 **                                                                           **
 **===========================================================================**
 */

#include <stdint.h>
#include "GPIO_interface.h"
#include "ErrorStates.h"
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

/**
 * @fn     SSD_enumInit
 * @brief  Initialize seven segment display pins
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumInit(const SSD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;

    /* Configure all segment pins */
    PinConfig.Port = Config->Port;
    PinConfig.Mode = SSD_OUTPUT_MODE;
    PinConfig.Pull = GPIO_NO_PULL;

    /* Initialize pins A-G */
    PinConfig.PinNum = Config->PinA;
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);

    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinB;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinC;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinD;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinE;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinF;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->PinG;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Initialize decimal point pin if provided */
    if (Local_ErrorState == OK && Config->PinDP != GPIO_PIN_NONE)
    {
      PinConfig.PinNum = Config->PinDP;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Clear display after initialization */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = SSD_enumClear(Config);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     SSD_enumDisplayNumber
 * @brief  Display a number (0-9) on the seven segment
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @param  Number[in]: Number to display (0-9)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumDisplayNumber(const SSD_Config_t *Config, uint8_t Number)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL || Number > SSD_MAX_NUMBER)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Pattern = SSD_NumberPatterns[Number];
    GPIO_PinValue_t SegmentState;

    /* Set each segment based on the pattern */
    /* Segment A */
    SegmentState = ((Pattern >> SSD_SEG_A_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
    if (Config->Type == SSD_COMMON_ANODE)
      SegmentState = !SegmentState;
    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinA, SegmentState);

    /* Segment B */
    if (Local_ErrorState == OK)
    {
      SegmentState = ((Pattern >> SSD_SEG_B_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
      if (Config->Type == SSD_COMMON_ANODE)
        SegmentState = !SegmentState;
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinB, SegmentState);
    }

    /* Segment C */
    if (Local_ErrorState == OK)
    {
      SegmentState = ((Pattern >> SSD_SEG_C_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
      if (Config->Type == SSD_COMMON_ANODE)
        SegmentState = !SegmentState;
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinC, SegmentState);
    }

    /* Segment D */
    if (Local_ErrorState == OK)
    {
      SegmentState = ((Pattern >> SSD_SEG_D_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
      if (Config->Type == SSD_COMMON_ANODE)
        SegmentState = !SegmentState;
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinD, SegmentState);
    }

    /* Segment E */
    if (Local_ErrorState == OK)
    {
      SegmentState = ((Pattern >> SSD_SEG_E_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
      if (Config->Type == SSD_COMMON_ANODE)
        SegmentState = !SegmentState;
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinE, SegmentState);
    }

    /* Segment F */
    if (Local_ErrorState == OK)
    {
      SegmentState = ((Pattern >> SSD_SEG_F_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
      if (Config->Type == SSD_COMMON_ANODE)
        SegmentState = !SegmentState;
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinF, SegmentState);
    }

    /* Segment G */
    if (Local_ErrorState == OK)
    {
      SegmentState = ((Pattern >> SSD_SEG_G_BIT) & 0x01) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
      if (Config->Type == SSD_COMMON_ANODE)
        SegmentState = !SegmentState;
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinG, SegmentState);
    }
  }

  return Local_ErrorState;
}

/**
 * @fn     SSD_enumClear
 * @brief  Clear/turn off all segments
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumClear(const SSD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinValue_t ClearState = (Config->Type == SSD_COMMON_ANODE) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;

    /* Turn off all segments */
    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinA, ClearState);

    if (Local_ErrorState == OK)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinB, ClearState);

    if (Local_ErrorState == OK)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinC, ClearState);

    if (Local_ErrorState == OK)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinD, ClearState);

    if (Local_ErrorState == OK)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinE, ClearState);

    if (Local_ErrorState == OK)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinF, ClearState);

    if (Local_ErrorState == OK)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinG, ClearState);

    /* Clear decimal point if available */
    if (Local_ErrorState == OK && Config->PinDP != GPIO_PIN_NONE)
      Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinDP, ClearState);
  }

  return Local_ErrorState;
}

/**
 * @fn     SSD_enumSetDecimalPoint
 * @brief  Set the decimal point state
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @param  State[in]: State to set (1 = ON, 0 = OFF)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumSetDecimalPoint(const SSD_Config_t *Config, uint8_t State)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL || Config->PinDP == GPIO_PIN_NONE)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinValue_t PinState;

    if (Config->Type == SSD_COMMON_ANODE)
      PinState = State ? GPIO_PIN_LOW : GPIO_PIN_HIGH;
    else
      PinState = State ? GPIO_PIN_HIGH : GPIO_PIN_LOW;

    Local_ErrorState = GPIO_enumSetPinValue(Config->Port, Config->PinDP, PinState);
  }

  return Local_ErrorState;
}