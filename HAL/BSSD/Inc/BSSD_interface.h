/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    BSSD_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : BSSD                                            **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_BSSD_INTERFACE_H_
#define HAL_BSSD_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/************************** BCD Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port; /* GPIO Port for BCD pins */
  GPIO_Pin_t PinA;  /* Pin for BCD bit A (LSB) */
  GPIO_Pin_t PinB;  /* Pin for BCD bit B */
  GPIO_Pin_t PinC;  /* Pin for BCD bit C */
  GPIO_Pin_t PinD;  /* Pin for BCD bit D (MSB) */
} BSSD_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     BSSD_enumInit
 * @brief  Initialize BCD pins
 * @param  Config[in]: Pointer to BCD configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BSSD_enumInit(const BSSD_Config_t *Config);

/**
 * @fn     BSSD_enumDisplayNumber
 * @brief  Display number on seven segment using BCD
 * @param  Config[in]: Pointer to BCD configuration structure
 * @param  Number[in]: Number to display (0-9)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BSSD_enumDisplayNumber(const BSSD_Config_t *Config, uint8_t Number);

#endif /* HAL_BSSD_INTERFACE_H_ */