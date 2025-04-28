/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    LCD_program.c      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : LCD                                             **
 **                                                                           **
 **===========================================================================**
 */

#include <stdint.h>
#include <string.h>
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "ErrorStates.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

/* Private helper functions */
static ErrorState_t LCD_enumSendData(const LCD_Config_t *Config, uint8_t Data)
{
  ErrorState_t Local_ErrorState = OK;

  /* Set RS pin to HIGH for data */
  Local_ErrorState = GPIO_enumSetPinValue(Config->ControlPort, Config->RS, GPIO_PIN_HIGH);

  if (Local_ErrorState == OK)
  {
    /* Set RW pin to LOW for write */
    Local_ErrorState = GPIO_enumSetPinValue(Config->ControlPort, Config->RW, GPIO_PIN_LOW);

    if (Local_ErrorState == OK)
    {
      if (Config->Mode == LCD_8BIT_MODE)
      {
        /* Send all 8 bits at once */
        for (uint8_t i = 0; i < 8 && Local_ErrorState == OK; i++)
        {
          Local_ErrorState = GPIO_enumSetPinValue(Config->DataPort, Config->DataPins[i],
                                                  (Data & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
        }
      }
      else /* 4-bit mode */
      {
        /* Send upper 4 bits */
        for (uint8_t i = 4; i < 8 && Local_ErrorState == OK; i++)
        {
          Local_ErrorState = GPIO_enumSetPinValue(Config->DataPort, Config->DataPins[i],
                                                  (Data & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
        }

        if (Local_ErrorState == OK)
        {
          /* Latch upper 4 bits */
          Local_ErrorState = LCD_enumLatch(Config);

          if (Local_ErrorState == OK)
          {
            /* Send lower 4 bits */
            for (uint8_t i = 0; i < 4 && Local_ErrorState == OK; i++)
            {
              Local_ErrorState = GPIO_enumSetPinValue(Config->DataPort, Config->DataPins[i + 4],
                                                      (Data & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
            }
          }
        }
      }

      if (Local_ErrorState == OK)
      {
        /* Latch the data */
        Local_ErrorState = LCD_enumLatch(Config);
      }
    }
  }

  return Local_ErrorState;
}

static ErrorState_t LCD_enumLatch(const LCD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  /* Set EN pin HIGH */
  Local_ErrorState = GPIO_enumSetPinValue(Config->ControlPort, Config->EN, GPIO_PIN_HIGH);

  if (Local_ErrorState == OK)
  {
    /* Wait for data to be latched */
    STK_enumSetBusyWait(LCD_EN_DELAY_US);

    /* Set EN pin LOW */
    Local_ErrorState = GPIO_enumSetPinValue(Config->ControlPort, Config->EN, GPIO_PIN_LOW);

    if (Local_ErrorState == OK)
    {
      /* Wait for command to be executed */
      STK_enumSetBusyWait(LCD_CMD_DELAY_US);
    }
  }

  return Local_ErrorState;
}

/* Public functions implementation */
ErrorState_t LCD_enumInit(const LCD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    GPIO_PinConfig_t PinConfig;
    uint8_t Local_Counter;

    /* Configure control pins */
    PinConfig.Port = Config->ControlPort;
    PinConfig.Mode = LCD_PIN_MODE;
    PinConfig.Pull = GPIO_NO_PULL;

    /* Configure RS pin */
    PinConfig.PinNum = Config->RS;
    Local_ErrorState = GPIO_enumPinInit(&PinConfig);

    /* Configure RW pin */
    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->RW;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Configure EN pin */
    if (Local_ErrorState == OK)
    {
      PinConfig.PinNum = Config->EN;
      Local_ErrorState = GPIO_enumPinInit(&PinConfig);
    }

    /* Configure data pins */
    if (Local_ErrorState == OK)
    {
      PinConfig.Port = Config->DataPort;
      uint8_t NumPins = (Config->Mode == LCD_8BIT_MODE) ? 8 : 4;

      for (Local_Counter = 0; Local_Counter < NumPins && Local_ErrorState == OK; Local_Counter++)
      {
        PinConfig.PinNum = Config->DataPins[Local_Counter];
        Local_ErrorState = GPIO_enumPinInit(&PinConfig);
      }
    }

    if (Local_ErrorState == OK)
    {
      /* Wait for LCD power-up */
      STK_enumSetBusyWait(LCD_INIT_DELAY_MS * 1000);

      /* Initialize LCD according to mode */
      if (Config->Mode == LCD_8BIT_MODE)
      {
        Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_8BIT_2LINE);
      }
      else /* 4-bit mode */
      {
        /* Special initialization sequence for 4-bit mode */
        Local_ErrorState = LCD_enumSendCommand(Config, 0x33);

        if (Local_ErrorState == OK)
        {
          Local_ErrorState = LCD_enumSendCommand(Config, 0x32);
        }

        if (Local_ErrorState == OK)
        {
          Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_4BIT_2LINE);
        }
      }

      /* Complete initialization sequence */
      if (Local_ErrorState == OK)
      {
        Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_DISPLAY_ON);
      }

      if (Local_ErrorState == OK)
      {
        Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_CLEAR);
        STK_enumSetBusyWait(LCD_CLEAR_DELAY_MS * 1000);
      }

      if (Local_ErrorState == OK)
      {
        Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_ENTRY_MODE);
      }
    }
  }

  return Local_ErrorState;
}

ErrorState_t LCD_enumSendCommand(const LCD_Config_t *Config, uint8_t Command)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set RS pin to LOW for command */
    Local_ErrorState = GPIO_enumSetPinValue(Config->ControlPort, Config->RS, GPIO_PIN_LOW);

    if (Local_ErrorState == OK)
    {
      /* Set RW pin to LOW for write */
      Local_ErrorState = GPIO_enumSetPinValue(Config->ControlPort, Config->RW, GPIO_PIN_LOW);

      if (Local_ErrorState == OK)
      {
        if (Config->Mode == LCD_8BIT_MODE)
        {
          /* Send all 8 bits at once */
          for (uint8_t i = 0; i < 8 && Local_ErrorState == OK; i++)
          {
            Local_ErrorState = GPIO_enumSetPinValue(Config->DataPort, Config->DataPins[i],
                                                    (Command & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
          }
        }
        else /* 4-bit mode */
        {
          /* Send upper 4 bits */
          for (uint8_t i = 4; i < 8 && Local_ErrorState == OK; i++)
          {
            Local_ErrorState = GPIO_enumSetPinValue(Config->DataPort, Config->DataPins[i],
                                                    (Command & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
          }

          if (Local_ErrorState == OK)
          {
            /* Latch upper 4 bits */
            Local_ErrorState = LCD_enumLatch(Config);

            if (Local_ErrorState == OK)
            {
              /* Send lower 4 bits */
              for (uint8_t i = 0; i < 4 && Local_ErrorState == OK; i++)
              {
                Local_ErrorState = GPIO_enumSetPinValue(Config->DataPort, Config->DataPins[i + 4],
                                                        (Command & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
              }
            }
          }
        }

        if (Local_ErrorState == OK)
        {
          /* Latch the command */
          Local_ErrorState = LCD_enumLatch(Config);
        }
      }
    }
  }

  return Local_ErrorState;
}

ErrorState_t LCD_enumDisplayChar(const LCD_Config_t *Config, uint8_t Char)
{
  return LCD_enumSendData(Config, Char);
}

ErrorState_t LCD_enumDisplayString(const LCD_Config_t *Config, const char *String)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL || String == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    while (*String != '\0' && Local_ErrorState == OK)
    {
      Local_ErrorState = LCD_enumDisplayChar(Config, *String);
      String++;
    }
  }

  return Local_ErrorState;
}

ErrorState_t LCD_enumDisplayNumber(const LCD_Config_t *Config, int32_t Number)
{
  ErrorState_t Local_ErrorState = OK;
  char Local_String[12]; /* Buffer for number conversion (max 10 digits + sign + null) */
  uint8_t Local_Index = 0;
  uint8_t Local_IsNegative = 0;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Handle negative numbers */
    if (Number < 0)
    {
      Local_IsNegative = 1;
      Number = -Number;
    }

    /* Convert number to string (reverse order) */
    do
    {
      Local_String[Local_Index++] = (Number % 10) + '0';
      Number /= 10;
    } while (Number > 0);

    /* Add negative sign if needed */
    if (Local_IsNegative)
    {
      Local_String[Local_Index++] = '-';
    }

    /* Display characters in correct order */
    while (Local_Index > 0 && Local_ErrorState == OK)
    {
      Local_ErrorState = LCD_enumDisplayChar(Config, Local_String[--Local_Index]);
    }
  }

  return Local_ErrorState;
}

ErrorState_t LCD_enumGoToXY(const LCD_Config_t *Config, uint8_t X, uint8_t Y)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL || X >= LCD_COLS || Y >= LCD_ROWS)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    uint8_t Local_Address = (Y == 0) ? LCD_LINE0_ADDRESS : LCD_LINE1_ADDRESS;
    Local_Address += X;
    Local_ErrorState = LCD_enumSendCommand(Config, Local_Address);
  }

  return Local_ErrorState;
}

ErrorState_t LCD_enumCreateCustomChar(const LCD_Config_t *Config, uint8_t Location, const uint8_t *Pattern)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL || Pattern == NULL || Location >= LCD_CGRAM_SIZE)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    /* Set CGRAM address */
    Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_SET_CGRAM_ADDR | (Location << 3));

    /* Write pattern to CGRAM */
    for (uint8_t i = 0; i < LCD_CGRAM_PATTERN_SIZE && Local_ErrorState == OK; i++)
    {
      Local_ErrorState = LCD_enumSendData(Config, Pattern[i]);
    }

    /* Return to DDRAM */
    if (Local_ErrorState == OK)
    {
      Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_SET_DDRAM_ADDR);
    }
  }

  return Local_ErrorState;
}

ErrorState_t LCD_enumClear(const LCD_Config_t *Config)
{
  ErrorState_t Local_ErrorState = OK;

  if (Config == NULL)
  {
    Local_ErrorState = NOK;
  }
  else
  {
    Local_ErrorState = LCD_enumSendCommand(Config, LCD_CMD_CLEAR);

    if (Local_ErrorState == OK)
    {
      STK_enumSetBusyWait(LCD_CLEAR_DELAY_MS * 1000);
    }
  }

  return Local_ErrorState;
}