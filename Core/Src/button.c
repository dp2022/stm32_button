#include "button.h"
#include <stm32f3xx.h>

void button_systick(button_def_t *button_def)
{
    if (HAL_GPIO_ReadPin(button_def->port, button_def->pin) == GPIO_PIN_SET)
    {
      button_def->ctr_on += 1;
      if (button_def->enable_long_press && (button_def->ctr_on == BUTTON_LONG_TIME_MS))
      {
        button_def->long_pressed = true;
#ifdef CLICK_LONG_AND_SHORT_TOGETHER
        button_def->ctr_autorepeat += BUTTON_AUTOREPEAT_SPEED_1_MS - 1;
#else
        button_def->ctr_autorepeat = 0;
#endif
      }
      if ((button_def->enable_autorepeat) && (button_def->ctr_on >= BUTTON_LONG_TIME_MS))
      {
        button_def->ctr_autorepeat += 1;
        uint32_t speed = BUTTON_AUTOREPEAT_DELAY_1_MS;
        if (button_def->ctr_autorepeat_num > BUTTON_AUTOREPEAT_2_NUM)
        {
            speed = BUTTON_AUTOREPEAT_DELAY_3_MS;
        } else
        if (button_def->ctr_autorepeat_num > BUTTON_AUTOREPEAT_1_NUM)
        {
            speed = BUTTON_AUTOREPEAT_DELAY_2_MS;
        }
        if (button_def->ctr_autorepeat >= speed)
        {
            button_def->pressed = true;
            button_def->ctr_autorepeat = 0;
            button_def->ctr_autorepeat_num += 1;
        }
      }
      return;
    }

    button_def->pressed = false;
    button_def->long_pressed = false;
    if ((button_def->ctr_on >= BUTTON_DAMPING_TIME_MS) && (button_def->ctr_on < BUTTON_LONG_TIME_MS))
    {
        button_def->pressed = true;
    }
    button_def->ctr_on = 0;
    button_def->ctr_autorepeat = 0;
    button_def->ctr_autorepeat_num = 0;
};

void button_setup(
    button_def_t *button_def, 
    GPIO_TypeDef *GPIO, 
    uint32_t pin, 
    bool enable_autorepeat,
    bool enable_long_press
)
{
    button_def->port = GPIO;
    button_def->pin = pin;
    button_def->enable_autorepeat = enable_autorepeat;
    button_def->enable_long_press = enable_long_press;
    button_def->ctr_on = 0;
    button_def->ctr_autorepeat = 0;
    button_def->ctr_autorepeat_num = 0;
    button_def->pressed = false;
    button_def->long_pressed = false;
};

bool button_pressed(button_def_t *button_def)
{
    bool result = button_def->pressed;
    button_def->pressed = false;
    return result;
};

bool button_long_pressed(button_def_t *button_def)
{
    bool result = button_def->long_pressed;
    button_def->long_pressed = false;
    return result;
};
