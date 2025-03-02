/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<    SYSTIC_private.h     >>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : MCAL                                            **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SYSTIC                                          **
 **                                                                           **
 **===========================================================================**
 */

#ifndef MCAL_SYSTIC_PRIVATE_H_
#define MCAL_SYSTIC_PRIVATE_H_

/************************** SysTick Register Bit Definitions **************************/
/* CTRL Register Bits */
#define SYSTICK_CTRL_ENABLE 0     /* Counter Enable */
#define SYSTICK_CTRL_TICKINT 1    /* Exception Request Enable */
#define SYSTICK_CTRL_CLKSOURCE 2  /* Clock Source Selection */
#define SYSTICK_CTRL_COUNTFLAG 16 /* Timer Count Flag */

/* Maximum reload value */
#define SYSTICK_LOAD_RELOAD_MSK 0x00FFFFFF /* Maximum reload value */

/* Clear current value */
#define SYSTICK_VAL_CURRENT 0x00FFFFFF /* Current value mask */

/* Interrupt interval types */
#define SYSTICK_SINGLE_INTERVAL 0
#define SYSTICK_PERIODIC_INTERVAL 1

#endif /* MCAL_SYSTIC_PRIVATE_H_ */