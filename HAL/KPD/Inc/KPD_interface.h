/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : KPD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_KPD_INTERFACE_H_
#define HAL_KPD_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/* Keypad dimensions */
#define KPD_ROWS 4
#define KPD_COLS 4

/************************** Keypad Configuration Structure **************************/
typedef struct
{
  GPIO_Port_t RowsPort;             /* GPIO Port for rows */
  GPIO_Port_t ColsPort;             /* GPIO Port for columns */
  GPIO_Pin_t RowPins[KPD_ROWS];     /* Array of row pins */
  GPIO_Pin_t ColPins[KPD_COLS];     /* Array of column pins */
  uint8_t Keys[KPD_ROWS][KPD_COLS]; /* Keypad mapping matrix */
} KPD_Config_t;

/************************** Function Prototypes **************************/

/**
 * @fn     KPD_enumInit
 * @brief  Initialize keypad pins configuration
 * @param  Config[in]: Pointer to keypad configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t KPD_enumInit(const KPD_Config_t *Config);

/**
 * @fn     KPD_enumGetPressedKey
 * @brief  Get the currently pressed key
 * @param  Config[in]: Pointer to keypad configuration structure
 * @param  Key[out]: Pointer to store the pressed key value
 * @retval ErrorState_t: OK if successful, NOK if error
 * @note   Returns 0xFF if no key is pressed
 */
ErrorState_t KPD_enumGetPressedKey(const KPD_Config_t *Config, uint8_t *Key);

#endif /* HAL_KPD_INTERFACE_H_ */