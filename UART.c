/*
 * UART.c
 *
 *  Created on: Mar 10, 2018
 *      Author: Lenovo
 */

#include "board.h"
#include "fsl_uart.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* UART instance and clock */
#define DEMO_UART UART0
#define DEMO_UART_CLKSRC UART0_CLK_SRC
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)
#define DEMO_UART_IRQn UART0_RX_TX_IRQn
#define DEMO_UART_IRQHandler UART0_RX_TX_IRQHandler

/*! @brief Ring buffer size (Unit: Byte). */
#define DEMO_RING_BUFFER_SIZE 16

/*! @brief Ring buffer to save received data. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_memorias[] =
" 1-Leer memoria I2C\r\n 2-Escribir memoria I2C\r\n";

uint8_t g_reloj[] =
" 3-Establecer hora\r\n 4-Establecer Fecha\r\n 5-Formato de hora\r\n 6-Leer hora\r\n 7-Leer fecha\r\n";

uint8_t g_ECO[] =
" 8-Comunicacion con terminal 2\r\n 9-ECO en pantalla LCD\r\n";
/*
  Ring buffer for data input and output, in this example, input data are saved
  to ring buffer in IRQ handler. The main function polls the ring buffer status,
  if there are new data, then send them out.
  Ring buffer full: (((rxIndex + 1) % DEMO_RING_BUFFER_SIZE) == txIndex)
  Ring buffer empty: (rxIndex == txIndex)
*/
uint8_t demoRingBuffer[DEMO_RING_BUFFER_SIZE];
volatile uint16_t txIndex; /* Index of the data to send out. */
volatile uint16_t rxIndex; /* Index of the memory to save new arrived data. */

/*******************************************************************************
 * Code
 ******************************************************************************/

void DEMO_UART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(DEMO_UART))
    {
        data = UART_ReadByte(DEMO_UART);

        /* If ring buffer is not full, add data to ring buffer. */
        if (((rxIndex + 1) % DEMO_RING_BUFFER_SIZE) != txIndex)
        {
            demoRingBuffer[rxIndex] = data;
            rxIndex++;
            rxIndex %= DEMO_RING_BUFFER_SIZE;
        }
    }
}

void UART_START(void)
{
	 uart_config_t config;
	 UART_GetDefaultConfig(&config);
	 config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	 config.enableTx = true;
	 config.enableRx = true;

	 UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);

	 UART_EnableInterrupts(DEMO_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
	 EnableIRQ(DEMO_UART_IRQn);
}

void UART_MENU_PRINCIPAL()
{
	UART_WriteBlocking(DEMO_UART, g_memorias, sizeof(g_memorias) / sizeof(g_memorias[0]));
	UART_WriteBlocking(DEMO_UART, g_reloj, sizeof(g_reloj) / sizeof(g_reloj[0]));
	UART_WriteBlocking(DEMO_UART, g_ECO, sizeof(g_ECO) / sizeof(g_ECO[0]));
}

void UART_RECIVE(void)
{


	    while (1)
	    {
	        /* Send data only when UART TX register is empty and ring buffer has data to send out. */
	        while ((kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(DEMO_UART)) && (rxIndex != txIndex))
	        {
	            UART_WriteByte(DEMO_UART, demoRingBuffer[txIndex]);
	            txIndex++;
	            txIndex %= DEMO_RING_BUFFER_SIZE;
	        }
	    }
}
