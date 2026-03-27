/*
 * app.c
 *
 *  Created on: Mar 27, 2026
 *      Author: santosh
 */

#include "app.h"
#include "led.h"
#include "button.h"

void App_Init(void)
{
    LED_Init();
    Button_Init();
}

void App_Update(void)
{
    LED_Update();

    if (Button_WasPressed())
    {
        if (LED_GetMode() == LED_MODE_BLINK)
        {
            LED_SetMode(LED_MODE_SOLID);
        }
        else
        {
            LED_SetMode(LED_MODE_BLINK);
        }
    }
}
