/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<    SYSTIC_config.h      >>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SYSTIC                                          **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_SYSTIC_CONFIG_H_
#define MCAL_SYSTIC_CONFIG_H_

/* System clock frequency in Hz */
#define SYSTEM_CLOCK_FREQ 72000000UL /* 72 MHz for STM32F103C8T6 */

/* Clock source selection */
#define SYSTICK_CLOCK_SOURCE SYSTICK_CLK_AHB_DIV8 /* AHB/8 by default */

#endif /* MCAL_SYSTIC_CONFIG_H_ */