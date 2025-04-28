/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SSD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_SSD_INTERFACE_H_
#define HAL_SSD_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/************************** Seven Segment Type **************************/
typedef enum
{
  SSD_COMMON_ANODE = 0, /* Common anode seven segment (active low) */
  SSD_COMMON_CATHODE    /* Common cathode seven segment (active high) */
} SSD_Type_t;

/************************** Seven Segment Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port; /* GPIO Port for all pins */
  GPIO_Pin_t PinA;  /* Pin for segment A */
  GPIO_Pin_t PinB;  /* Pin for segment B */
  GPIO_Pin_t PinC;  /* Pin for segment C */
  GPIO_Pin_t PinD;  /* Pin for segment D */
  GPIO_Pin_t PinE;  /* Pin for segment E */
  GPIO_Pin_t PinF;  /* Pin for segment F */
  GPIO_Pin_t PinG;  /* Pin for segment G */
  GPIO_Pin_t PinDP; /* Pin for decimal point (optional) */
  SSD_Type_t Type;  /* Seven segment type (Common Anode/Cathode) */
} SSD_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     SSD_enumInit
 * @brief  Initialize seven segment display pins
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumInit(const SSD_Config_t *Config);

/**
 * @fn     SSD_enumDisplayNumber
 * @brief  Display a number (0-9) on the seven segment
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @param  Number[in]: Number to display (0-9)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumDisplayNumber(const SSD_Config_t *Config, uint8_t Number);

/**
 * @fn     SSD_enumClear
 * @brief  Clear/turn off all segments
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumClear(const SSD_Config_t *Config);

/**
 * @fn     SSD_enumSetDecimalPoint
 * @brief  Set the decimal point state
 * @param  Config[in]: Pointer to seven segment configuration structure
 * @param  State[in]: State to set (1 = ON, 0 = OFF)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SSD_enumSetDecimalPoint(const SSD_Config_t *Config, uint8_t State);

#endif /* HAL_SSD_INTERFACE_H_ */