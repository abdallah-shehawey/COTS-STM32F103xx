/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_private.h      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : LCD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_LCD_PRIVATE_H_
#define HAL_LCD_PRIVATE_H_

/* LCD dimensions */
#define LCD_ROWS 2
#define LCD_COLS 16

/* LCD line addresses */
#define LCD_LINE0_ADDRESS 0x80
#define LCD_LINE1_ADDRESS 0xC0

/* LCD timing delays in microseconds */
#define LCD_INIT_DELAY_MS 30
#define LCD_EN_DELAY_US 1
#define LCD_CMD_DELAY_US 100
#define LCD_CHAR_DELAY_US 100
#define LCD_CLEAR_DELAY_MS 2

/* CGRAM */
#define LCD_CGRAM_SIZE 8
#define LCD_CGRAM_PATTERN_SIZE 8

/* Private function prototypes */
static ErrorState_t LCD_enumSendData(const LCD_Config_t *Config, uint8_t Data);
static ErrorState_t LCD_enumLatch(const LCD_Config_t *Config);

#endif /* HAL_LCD_PRIVATE_H_ */