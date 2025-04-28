/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_private.h      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : KPD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_KPD_PRIVATE_H_
#define HAL_KPD_PRIVATE_H_

/* Value returned when no key is pressed */
#define KPD_NO_PRESSED_KEY 0xFF

/* Delay between row scanning (in microseconds) */
#define KPD_SCAN_DELAY_US 5

#endif /* HAL_KPD_PRIVATE_H_ */