/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_config.h       >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : KPD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_KPD_CONFIG_H_
#define HAL_KPD_CONFIG_H_

/* Default GPIO configurations for keypad */
#define KPD_ROW_MODE GPIO_INPUT_PULL_UP  /* Rows are inputs with pull-up */
#define KPD_COL_MODE GPIO_OUTPUT_PP_2MHZ /* Columns are outputs */

/* Default keypad mapping matrix */
#define KPD_DEFAULT_KEYS {{'7', '8', '9', '/'}, \
                          {'4', '5', '6', '*'}, \
                          {'1', '2', '3', '-'}, \
                          {'C', '0', '=', '+'}}

#endif /* HAL_KPD_CONFIG_H_ */