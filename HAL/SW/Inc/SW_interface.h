/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    SW_interface.h      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SW                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_SW_INTERFACE_H_
#define HAL_SW_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/************************** Switch Connection Type **************************/
typedef enum
{
  SW_PULL_UP = 0, /* Switch connected to GND (Pressed = LOW) */
  SW_PULL_DOWN    /* Switch connected to VCC (Pressed = HIGH) */
} SW_ConnectionType_t;

/************************** Switch State **************************/
typedef enum
{
  SW_NOT_PRESSED = 0,
  SW_PRESSED
} SW_State_t;

/************************** Switch Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port;                   /* GPIO Port (PORTA to PORTE) */
  GPIO_Pin_t Pin;                     /* GPIO Pin (PIN0 to PIN15) */
  SW_ConnectionType_t ConnectionType; /* Switch Connection Type */
} SW_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     SW_enumInit
 * @brief  Initialize switch pin configuration
 * @param  Config[in]: Pointer to switch configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SW_enumInit(const SW_Config_t *Config);

/**
 * @fn     SW_enumGetState
 * @brief  Get the current state of the switch
 * @param  Config[in]: Pointer to switch configuration structure
 * @param  State[out]: Pointer to store switch state
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t SW_enumGetState(const SW_Config_t *Config, SW_State_t *State);

#endif /* HAL_SW_INTERFACE_H_ */