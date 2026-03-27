/*
 * led.h
 *
 *  Created on: Mar 27, 2026
 *      Author: santosh
 */

#ifndef INC_LED_H_
#define INC_LED_H_


#include <stdint.h>

typedef enum
{
    LED_MODE_BLINK = 0,
    LED_MODE_SOLID
} led_mode_t;

void LED_Init(void);

void LED_SetMode(led_mode_t mode);
void LED_SetPeriod(uint32_t period_ms);

void LED_Update(void);

led_mode_t LED_GetMode(void);
uint32_t LED_GetPeriod(void);


#endif /* INC_LED_H_ */
