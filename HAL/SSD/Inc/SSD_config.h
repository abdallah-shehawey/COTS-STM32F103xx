/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_config.h       >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SSD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_SSD_CONFIG_H_
#define HAL_SSD_CONFIG_H_

/* Default GPIO output configuration for seven segment display */
#define SSD_OUTPUT_MODE GPIO_OUTPUT_PP_2MHZ

/* Maximum number that can be displayed (0-9) */
#define SSD_MAX_NUMBER 9

#endif /* HAL_SSD_CONFIG_H_ */