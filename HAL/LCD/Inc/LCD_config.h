/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_config.h       >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : LCD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_LCD_CONFIG_H_
#define HAL_LCD_CONFIG_H_

/* Default GPIO output configuration for LCD pins */
#define LCD_PIN_MODE GPIO_OUTPUT_PP_2MHZ

/* Default LCD mode */
#define LCD_DEFAULT_MODE LCD_4BIT_MODE

/* Maximum number of custom characters */
#define LCD_MAX_CUSTOM_CHAR 8

#endif /* HAL_LCD_CONFIG_H_ */