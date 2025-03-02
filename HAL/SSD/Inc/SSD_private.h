/**
 **===========================================================================**
 **<<<<<<<<<<<<<<<<<<<<<<<<<<    SSD_private.h      >>>>>>>>>>>>>>>>>>>>>>>>>>**
 **                                                                           **
 **                  Author : Abdallah Abdelmoemen Shehawey                   **
 **                  Layer  : HAL                                             **
 **                  CPU    : Cortex-M3                                       **
 **                  MCU    : STM32F103C8T6                                   **
 **                  SWC    : SSD                                             **
 **                                                                           **
 **===========================================================================**
 */

#ifndef HAL_SSD_PRIVATE_H_
#define HAL_SSD_PRIVATE_H_

/* Seven segment display patterns for numbers 0-9 */
static const uint8_t SSD_NumberPatterns[10] = {
    0x3F, /* 0: 0b00111111 */
    0x06, /* 1: 0b00000110 */
    0x5B, /* 2: 0b01011011 */
    0x4F, /* 3: 0b01001111 */
    0x66, /* 4: 0b01100110 */
    0x6D, /* 5: 0b01101101 */
    0x7D, /* 6: 0b01111101 */
    0x07, /* 7: 0b00000111 */
    0x7F, /* 8: 0b01111111 */
    0x6F  /* 9: 0b01101111 */
};

/* Segment bit positions in pattern */
#define SSD_SEG_A_BIT 0
#define SSD_SEG_B_BIT 1
#define SSD_SEG_C_BIT 2
#define SSD_SEG_D_BIT 3
#define SSD_SEG_E_BIT 4
#define SSD_SEG_F_BIT 5
#define SSD_SEG_G_BIT 6

#endif /* HAL_SSD_PRIVATE_H_ */