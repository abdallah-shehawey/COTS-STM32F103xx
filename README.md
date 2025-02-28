# STM32F103C8T6 Driver for Bande Kit

## Overview

This repository contains the device drivers for the STM32F103C8T6 microcontroller, specifically configured for the Bande kit. These drivers provide low-level hardware abstraction and peripheral control.

## Features

- GPIO (General Purpose Input/Output)
- NVIC (Nested Vector Interrupt Controller)
- RCC (Reset and Clock Control)
- EXTI (External Interrupts)
- SYSTICK (System Timer)
- UART/USART Communication
- SPI Communication
- I2C Communication

## Hardware Requirements

- STM32F103C8T6 Blue Pill Board
- ST-Link V2 Programmer
- Bande Kit Components

## Software Requirements

- ARM GNU Toolchain
- Make build utility
- STM32CubeProgrammer
- Your preferred IDE (Eclipse, VS Code, etc.)

## Directory Structure

```
COTS/F103xx/
├── MCAL/           # Microcontroller Abstraction Layer
├── HAL/            # Hardware Abstraction Layer
├── APP/            # Application Layer
└── LIB/            # Library Files
```

## Usage

1. Clone this repository
2. Include needed drivers in your project
3. Configure the required peripherals
4. Build and flash your project

## Documentation

Essential reference documents for development:

- [STM32F103xx Reference Manual (RM0008)](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
- [STM32F103x8 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [STM32F103xx Programming Manual (PM0075)](https://www.st.com/resource/en/programming_manual/cd00228163-stm32f10xxx-flash-memory-microcontrollers-stmicroelectronics.pdf)
- [ARM Cortex-M3 Technical Reference Manual](https://developer.arm.com/documentation/ddi0337/e/)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

For any queries or support, please open an issue in the repository.
