/*
 * UART.h
 *
 *  Created on: Mar 10, 2018
 *      Author: Lenovo
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include "board.h"
#include "fsl_uart.h"

#define DEMO_UART UART0
#define DEMO_UART_CLKSRC UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_IRQn UART0_RX_TX_IRQn
#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler

typedef enum
{
 Lectura_I2C_1,
 Lectura_I2C_2,
 Lectura_I2C_3,
 Lectura_I2C_4,
 Escritura_I2C_1,
 Escritura_I2C_2,
 Escritura_I2C_3,
 Set_hr1,
 Set_hr2,
 Set_date1,
 Set_date2,
 Set_format1,
 Set_format2,
 Set_format3,
 Lectura_hr,
 Lectura_fecha
}values_t;







void DEMO_UART_IRQHandler(void);
void UART_START(void);
void UART_RECIVE(void);
void UART_MENU_PRINCIPAL();
void UART_MENU(values_t);
void UART_PRINT(uint8_t print);

#endif /* UART_H_ */
