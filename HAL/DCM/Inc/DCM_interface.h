/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    DCM_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : DCM                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_DCM_INTERFACE_H_
#define HAL_DCM_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/************************** DC Motor State **************************/
typedef enum
{
  DCM_CW = 0, /* Clockwise rotation */
  DCM_CCW,    /* Counter-clockwise rotation */
  DCM_STOP    /* Motor stop */
} DCM_State_t;

/************************** DC Motor Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t Port; /* GPIO Port for motor pins */
  GPIO_Pin_t Pin1;  /* First control pin */
  GPIO_Pin_t Pin2;  /* Second control pin */
} DCM_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     DCM_enumInit
 * @brief  Initialize DC motor pins
 * @param  Config[in]: Pointer to motor configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t DCM_enumInit(const DCM_Config_t *Config);

/**
 * @fn     DCM_enumSetState
 * @brief  Set motor rotation state
 * @param  Config[in]: Pointer to motor configuration structure
 * @param  State[in]: Motor state (CW, CCW, or STOP)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t DCM_enumSetState(const DCM_Config_t *Config, DCM_State_t State);

#endif /* HAL_DCM_INTERFACE_H_ */