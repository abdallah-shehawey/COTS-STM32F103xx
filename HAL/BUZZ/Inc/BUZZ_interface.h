/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    BUZZ_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : BUZZ                                            **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_BUZZ_INTERFACE_H_
#define HAL_BUZZ_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/************************** Buzzer Connection Type **************************/
typedef enum
{
  BUZZ_ACTIVE_HIGH = 0, /* Buzzer connected to VCC (ON = HIGH, OFF = LOW) */
  BUZZ_ACTIVE_LOW       /* Buzzer connected to GND (ON = LOW, OFF = HIGH) */
} BUZZ_ConnectionType_t;

/************************** Buzzer Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port;                     /* GPIO Port (PORTA to PORTE) */
  GPIO_Pin_t Pin;                       /* GPIO Pin (PIN0 to PIN15) */
  BUZZ_ConnectionType_t ConnectionType; /* Buzzer Connection Type */
} BUZZ_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     BUZZ_enumInit
 * @brief  Initialize buzzer pin configuration
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumInit(const BUZZ_Config_t *Config);

/**
 * @fn     BUZZ_enumTurnOn
 * @brief  Turn on the buzzer
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumTurnOn(const BUZZ_Config_t *Config);

/**
 * @fn     BUZZ_enumTurnOff
 * @brief  Turn off the buzzer
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumTurnOff(const BUZZ_Config_t *Config);

/**
 * @fn     BUZZ_enumToggle
 * @brief  Toggle the buzzer state
 * @param  Config[in]: Pointer to buzzer configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t BUZZ_enumToggle(const BUZZ_Config_t *Config);

#endif /* HAL_BUZZ_INTERFACE_H_ */