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

#define DEMO_UART1 UART1
#define DEMO_UART1_CLKSRC UART1_CLK_SRC
#define DEMO_UART1_CLK_FREQ CLOCK_GetFreq(UART1_CLK_SRC)

#define ECHO_BUFFER_LENGTH 8

#define DEMO_UART UART0
#define DEMO_UART_CLKSRC UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)

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





void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);
void UART_START(void);
void UART_SEND(void);
void UART_RECIVE(void);
void UART_MENU_PRINCIPAL();
void UART_MENU(values_t);


#endif /* UART_H_ */
