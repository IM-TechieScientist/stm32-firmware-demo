/*
 * button.c
 *
 *  Created on: Mar 27, 2026
 *      Author: santosh
 */


#include "button.h"
#include "main.h"

static volatile uint8_t button_flag = 0;
static uint32_t last_press_time = 0;

#define DEBOUNCE_MS 50

void Button_Init(void)
{
}

bool Button_WasPressed(void)
{
    if (button_flag)
    {
        button_flag = 0;
        return true;
    }

    return false;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13)
    {
        uint32_t now = HAL_GetTick();

        if (now - last_press_time > DEBOUNCE_MS)
        {
            button_flag = 1;
            last_press_time = now;
        }
    }
}
