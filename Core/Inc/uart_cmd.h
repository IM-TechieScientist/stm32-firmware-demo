/*
 * uart_cmd.h
 *
 *  Created on: Mar 27, 2026
 *      Author: santosh
 */

#ifndef INC_UART_CMD_H_
#define INC_UART_CMD_H_


#include <stdint.h>

void UARTCMD_Init(void);
void UARTCMD_Task(void);

void UART_SendString(const char *str);

#endif /* INC_UART_CMD_H_ */
