/*
 * uart_cmd.c
 *
 *  Created on: Mar 27, 2026
 *      Author: santosh
 */


#include "uart_cmd.h"
#include "main.h"
#include "led.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern UART_HandleTypeDef huart3;

#define RX_BUFFER_SIZE 64

static char rx_buffer[RX_BUFFER_SIZE];
static uint8_t rx_index = 0;

static uint8_t rx_char;

void UART_SendString(const char *str)
{
    HAL_UART_Transmit(
        &huart3,
        (uint8_t*)str,
        strlen(str),
        HAL_MAX_DELAY
    );
}

static void SendStatus(void)
{
    char msg[64];

    const char *mode =
        (LED_GetMode() == LED_MODE_BLINK)
        ? "BLINK"
        : "SOLID";

    sprintf(
        msg,
        "OK mode=%s period=%lu\r\n",
        mode,
        LED_GetPeriod()
    );

    UART_SendString(msg);
}

static void SendError(const char *msg)
{
    char buffer[64];

    sprintf(
        buffer,
        "ERR %s\r\n",
        msg
    );

    UART_SendString(buffer);
}

static void HandlePeriod(char *arg)
{
    if (arg == NULL)
    {
        SendError("invalid argument");
        return;
    }

    char *endptr;

    long value = strtol(arg, &endptr, 10);

    if (*endptr != '\0')
    {
        SendError("invalid argument");
        return;
    }

    if (value < 50 || value > 5000)
    {
        SendError("invalid argument");
        return;
    }

    LED_SetPeriod((uint32_t)value);

    SendStatus();
}

static void ProcessLine(char *line)
{
    char *cmd = strtok(line, " ");

    if (cmd == NULL)
    {
        SendError("unknown command");
        return;
    }

    if (strcmp(cmd, "status") == 0)
    {
        SendStatus();
    }
    else if (strcmp(cmd, "period") == 0)
    {
        char *arg = strtok(NULL, " ");

        HandlePeriod(arg);
    }
    else
    {
        SendError("unknown command");
    }
}

void UARTCMD_Init(void)
{
    HAL_UART_Receive_IT(
        &huart3,
        &rx_char,
        1
    );
}

void UARTCMD_Task(void)
{
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        if (rx_char == '\r' || rx_char == '\n')
        {
            rx_buffer[rx_index] = '\0';

            ProcessLine(rx_buffer);

            rx_index = 0;
        }
        else
        {
            if (rx_index < RX_BUFFER_SIZE - 1)
            {
                rx_buffer[rx_index++] = rx_char;
            }
        }

        HAL_UART_Receive_IT(
            &huart3,
            &rx_char,
            1
        );
    }
}
