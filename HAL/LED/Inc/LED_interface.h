/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    LED_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : LED                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrTypes.h"

/************************** LED Connection Type **************************/
typedef enum
{
  LED_ACTIVE_HIGH = 0, /* LED connected to VCC (ON = HIGH, OFF = LOW) */
  LED_ACTIVE_LOW       /* LED connected to GND (ON = LOW, OFF = HIGH) */
} LED_ConnectionType_t;

/************************** LED Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port;                    /* GPIO Port (PORTA to PORTE) */
  GPIO_Pin_t Pin;                      /* GPIO Pin (PIN0 to PIN15) */
  LED_ConnectionType_t ConnectionType; /* LED Connection Type */
} LED_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     LED_enumInit
 * @brief  Initialize LED pin configuration
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumInit(const LED_Config_t *Config);

/**
 * @fn     LED_enumTurnOn
 * @brief  Turn on the LED
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumTurnOn(const LED_Config_t *Config);

/**
 * @fn     LED_enumTurnOff
 * @brief  Turn off the LED
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumTurnOff(const LED_Config_t *Config);

/**
 * @fn     LED_enumToggle
 * @brief  Toggle the LED state
 * @param  Config[in]: Pointer to LED configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LED_enumToggle(const LED_Config_t *Config);

#endif /* HAL_LED_INTERFACE_H_ */