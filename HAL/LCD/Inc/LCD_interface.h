/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : LCD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_LCD_INTERFACE_H_
#define HAL_LCD_INTERFACE_H_

#include "GPIO_interface.h"
#include "ErrorStates.h"

/************************** LCD Mode **************************/
typedef enum
{
  LCD_4BIT_MODE = 0, /* 4-bit data mode */
  LCD_8BIT_MODE      /* 8-bit data mode */
} LCD_Mode_t;

/************************** LCD Configuration Structure **************************/
typedef struct
{
  LCD_Mode_t Mode;         /* LCD mode (4-bit or 8-bit) */
  GPIO_Port_t DataPort;    /* GPIO Port for data pins */
  GPIO_Port_t ControlPort; /* GPIO Port for control pins */
  GPIO_Pin_t RS;           /* Register Select pin */
  GPIO_Pin_t RW;           /* Read/Write pin */
  GPIO_Pin_t EN;           /* Enable pin */
  GPIO_Pin_t DataPins[8];  /* Data pins (D0-D7 for 8-bit mode, D4-D7 for 4-bit mode) */
} LCD_Config_t;

/************************** LCD Commands **************************/
#define LCD_CMD_CLEAR 0x01          /* Clear display */
#define LCD_CMD_RETURN_HOME 0x02    /* Return cursor to home position */
#define LCD_CMD_ENTRY_MODE 0x06     /* Increment cursor (no display shift) */
#define LCD_CMD_DISPLAY_ON 0x0C     /* Display ON, cursor OFF */
#define LCD_CMD_DISPLAY_OFF 0x08    /* Display OFF */
#define LCD_CMD_8BIT_2LINE 0x38     /* 8-bit mode, 2 lines */
#define LCD_CMD_4BIT_2LINE 0x28     /* 4-bit mode, 2 lines */
#define LCD_CMD_SET_CGRAM_ADDR 0x40 /* Set CGRAM address */
#define LCD_CMD_SET_DDRAM_ADDR 0x80 /* Set DDRAM address */

/************************** Function Prototypes **************************/

/**
 * @fn     LCD_enumInit
 * @brief  Initialize LCD
 * @param  Config[in]: Pointer to LCD configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumInit(const LCD_Config_t *Config);

/**
 * @fn     LCD_enumSendCommand
 * @brief  Send command to LCD
 * @param  Config[in]: Pointer to LCD configuration structure
 * @param  Command[in]: Command to send
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumSendCommand(const LCD_Config_t *Config, uint8_t Command);

/**
 * @fn     LCD_enumDisplayChar
 * @brief  Display character on LCD
 * @param  Config[in]: Pointer to LCD configuration structure
 * @param  Char[in]: Character to display
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumDisplayChar(const LCD_Config_t *Config, uint8_t Char);

/**
 * @fn     LCD_enumDisplayString
 * @brief  Display string on LCD
 * @param  Config[in]: Pointer to LCD configuration structure
 * @param  String[in]: Pointer to string to display
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumDisplayString(const LCD_Config_t *Config, const char *String);

/**
 * @fn     LCD_enumDisplayNumber
 * @brief  Display number on LCD
 * @param  Config[in]: Pointer to LCD configuration structure
 * @param  Number[in]: Number to display
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumDisplayNumber(const LCD_Config_t *Config, int32_t Number);

/**
 * @fn     LCD_enumGoToXY
 * @brief  Set cursor position
 * @param  Config[in]: Pointer to LCD configuration structure
 * @param  X[in]: Column position (0-15)
 * @param  Y[in]: Row position (0-1)
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumGoToXY(const LCD_Config_t *Config, uint8_t X, uint8_t Y);

/**
 * @fn     LCD_enumCreateCustomChar
 * @brief  Create custom character
 * @param  Config[in]: Pointer to LCD configuration structure
 * @param  Location[in]: CGRAM location (0-7)
 * @param  Pattern[in]: Array of 8 bytes containing character pattern
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumCreateCustomChar(const LCD_Config_t *Config, uint8_t Location, const uint8_t *Pattern);

/**
 * @fn     LCD_enumClear
 * @brief  Clear LCD display
 * @param  Config[in]: Pointer to LCD configuration structure
 * @retval ErrorState_t: OK if successful, NOK if error
 */
ErrorState_t LCD_enumClear(const LCD_Config_t *Config);

#endif /* HAL_LCD_INTERFACE_H_ */