#ifndef __BUTTON_H
#define __BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "stm32f303xc.h"

// #define CLICK_LONG_AND_SHORT_TOGETHER


#define BUTTON_DAMPING_TIME_MS 80
#define BUTTON_LONG_TIME_MS 1200
#define BUTTON_AUTOREPEAT_DELAY_1_MS 500
#define BUTTON_AUTOREPEAT_DELAY_2_MS 350
#define BUTTON_AUTOREPEAT_DELAY_3_MS 200
#define BUTTON_AUTOREPEAT_1_NUM 6
#define BUTTON_AUTOREPEAT_2_NUM (BUTTON_AUTOREPEAT_1_NUM + 10)


typedef struct
{
    GPIO_TypeDef *port; /* GPIO port setting */
    uint32_t pin; /* GPIO pin setting*/
    volatile bool enable_autorepeat; /* Enable (true) or disable (false) auto repeat presses */
    volatile bool enable_long_press; /* Enable (true) or disable (false) long button press */
    uint32_t ctr_on; /* Continuous turn on pin time counter */
    uint32_t ctr_autorepeat; /* Autorepeat time counter */
    uint32_t ctr_autorepeat_num; /* Numer of autorepeat clicks */
    volatile bool pressed; /* Button has been pressed */
    volatile bool long_pressed; /* Button has been long pressed */
} button_def_t;

void button_setup(
    button_def_t *button_def,
    GPIO_TypeDef *GPIO,
    uint32_t pin,
    bool enable_autorepeat,
    bool enable_long_press);
void button_systick(button_def_t *button_def);
bool button_pressed(button_def_t *button_def);
bool button_long_pressed(button_def_t *button_def);

#ifdef __cplusplus
}
#endif

#endif /* __BUTTON_H */
