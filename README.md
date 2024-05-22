Button Handling for ARM Cortex-M4
===

Description
---

Library to support button press for the ARM Coretex-M4. Demo application is prepared for the [STM32F3-DISCOVERY](https://www.st.com/en/evaluation-tools/stm32f3discovery.html) board but can be easly changed using [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html). It need systick to work.

Features
---

- Debouncing
- Short and/or long press
- Auto repeat short presses
- 3 speeds of the auto repeat

How to?
---

1. Copy `Core/Inc/button.h` and `Core/Src/button.c` to your project.
2. Before the `main` loop, execute `button_setup` function.
3. In the main loop you can check whether a button has been pressed using `button_pressed` and/or `button_long_pressed` functions.
4. In the `SysTick` handler execute `button_systick` function.
