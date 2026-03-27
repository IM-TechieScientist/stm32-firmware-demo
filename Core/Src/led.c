/*
 * led.c
 *
 *  Created on: Mar 27, 2026
 *      Author: santosh
 */


#include "led.h"
#include "main.h"

static led_mode_t current_mode = LED_MODE_BLINK;
static uint32_t blink_period = 500;

static uint32_t last_toggle = 0;
static uint8_t led_state = 0;

void LED_Init(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void LED_SetMode(led_mode_t mode)
{
    current_mode = mode;

    if (mode == LED_MODE_SOLID)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    }
}

void LED_SetPeriod(uint32_t period_ms)
{
    blink_period = period_ms;
}

led_mode_t LED_GetMode(void)
{
    return current_mode;
}

uint32_t LED_GetPeriod(void)
{
    return blink_period;
}

void LED_Update(void)
{
    if (current_mode == LED_MODE_BLINK)
    {
        uint32_t now = HAL_GetTick();

        if (now - last_toggle >= blink_period)
        {
            last_toggle = now;

            led_state = !led_state;

            HAL_GPIO_WritePin(
                GPIOB,
                GPIO_PIN_0,
                led_state ? GPIO_PIN_SET : GPIO_PIN_RESET
            );
        }
    }
}
