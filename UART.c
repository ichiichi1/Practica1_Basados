/*
 * UART.c
 *
 *  Created on: Mar 10, 2018
 *      Author: Lenovo
 */

#include "board.h"
#include "fsl_uart.h"
#include <stdio.h>

#include "pin_mux.h"
#include "clock_config.h"
#include "UART.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* UART instance and clock */


/*! @brief Ring buffer size (Unit: Byte). */
#define DEMO_RING_BUFFER_SIZE 16

/*! @brief Ring buffer to save received data. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
/////////////////////// UTILIZADAS EN MENÚ PRINCIPAL ///////////////////////////

uint8_t g_memorias[] =
" 1-Leer memoria I2C\r\n 2-Escribir memoria I2C\r\n";

uint8_t g_reloj[] =
" 3-Establecer hora\r\n 4-Establecer Fecha\r\n 5-Formato de hora\r\n 6-Leer hora\r\n 7-Leer fecha\r\n";

uint8_t g_ECO[] =
" 8-Comunicacion con terminal 2\r\n 9-ECO en pantalla LCD\r\n";

////////////////////////////////////////////////////////////////////////////////
///////////////////// UTILIZADAS EN I2C ////////////////////////////////////////

uint8_t Leer_I2C_1[] = "Direccion de lectura:\r\n";
uint8_t Leer_I2C_2[] = "Longitud en bytes: \r\n";
uint8_t Leer_I2C_3[] = "Contenido: \r\n";
uint8_t Leer_I2C_4[] = "Presione una tecla para continuar \r\n";

uint8_t Escribir_I2C_1[] = "Direccion de escritura:\r\n";
uint8_t Escribir_I2C_2[] = "Texto a guardar\r\n";
uint8_t Escribir_I2C_3[] = "Su texto ha sido guardado";

////////////////////////////////////////////////////////////////////////////////
///////////////////// UTILIZADAS EN RTC ////////////////////////////////////////

uint8_t Establecer_hora_1[] = "Establecer hora en hh/mm/ss:'r\n";
uint8_t Establecer_hora_2[] = "La hora ha sido cambiada";

uint8_t Establecer_fecha_1[] = "Establecer fecha en dd/mm/aa:\r\n";
uint8_t Establecer_fecha_2[] = "La hora ha sido cambiada";

uint8_t Formato_hr_1[] = "El formato actual es:";
uint8_t Formato_hr_2[] = "Desea cambiar el formato";
uint8_t Formato_hr_3[] = "El formato ha sido cambiado ...";

uint8_t Leer_hora_1[] = "La hora actual es:";

uint8_t Leer_fecha_1[] = "La fecha actual es:";

////////////////////////////////////////////////////////////////////////////////
///////////////////// UTILIZADAS EN ECO Y CHAT /////////////////////////////////



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
	 //falta setear la prioridad
}

void UART_MENU_PRINCIPAL()
{
	UART_WriteBlocking(DEMO_UART, g_memorias, sizeof(g_memorias) / sizeof(g_memorias[0]));
	UART_WriteBlocking(DEMO_UART, g_reloj, sizeof(g_reloj) / sizeof(g_reloj[0]));
	UART_WriteBlocking(DEMO_UART, g_ECO, sizeof(g_ECO) / sizeof(g_ECO[0]));
}

void UART_MENU(values_t valor)
{
	switch(valor)
	{
	case Lectura_I2C_1:
	UART_WriteBlocking(DEMO_UART, Leer_I2C_2, sizeof(Leer_I2C_2) / sizeof(Leer_I2C_2[0]));
	break;
	case Lectura_I2C_2:
	UART_WriteBlocking(DEMO_UART, Leer_I2C_2, sizeof(Leer_I2C_2) / sizeof(Leer_I2C_2[0]));
	break;
	case Lectura_I2C_3:
	UART_WriteBlocking(DEMO_UART, Leer_I2C_3, sizeof(Leer_I2C_3) / sizeof(Leer_I2C_3[0]));
	break;
	case Lectura_I2C_4:
	UART_WriteBlocking(DEMO_UART, Leer_I2C_4, sizeof(Leer_I2C_4) / sizeof(Leer_I2C_4[0]));
	break;
	case Escritura_I2C_1:
	UART_WriteBlocking(DEMO_UART, Escribir_I2C_1, sizeof(Escribir_I2C_1) / sizeof(Escribir_I2C_1[0]));
	break;
	case Escritura_I2C_2:
	UART_WriteBlocking(DEMO_UART, Escribir_I2C_1, sizeof(Escribir_I2C_1) / sizeof(Escribir_I2C_1[0]));
	break;
	case Escritura_I2C_3:
	UART_WriteBlocking(DEMO_UART, Escribir_I2C_1, sizeof(Escribir_I2C_1) / sizeof(Escribir_I2C_1[0]));
	break;
	case Set_hr1:
	UART_WriteBlocking(DEMO_UART, Establecer_hora_1, sizeof(Establecer_hora_1) / sizeof(Establecer_hora_1[0]));
	break;
	case Set_hr2:
	UART_WriteBlocking(DEMO_UART, Establecer_hora_2, sizeof(Establecer_hora_2) / sizeof(Establecer_hora_2[0]));
	break;
	case Set_date1:
	UART_WriteBlocking(DEMO_UART, Establecer_fecha_1, sizeof(Establecer_fecha_1) / sizeof(Establecer_fecha_1[0]));
	break;
	case Set_date2:
	UART_WriteBlocking(DEMO_UART, Establecer_fecha_2, sizeof(Establecer_fecha_2) / sizeof(Establecer_fecha_2[0]));
	break;
	case Set_format1:
	UART_WriteBlocking(DEMO_UART, Formato_hr_1, sizeof(Formato_hr_1) / sizeof(Formato_hr_1[0]));
	break;
	case Set_format2:
	UART_WriteBlocking(DEMO_UART, Formato_hr_2, sizeof(Formato_hr_2) / sizeof(Formato_hr_2[0]));
	break;
	case Set_format3:
	UART_WriteBlocking(DEMO_UART, Formato_hr_3, sizeof(Formato_hr_3) / sizeof(Formato_hr_3[0]));
	break;
	case Lectura_hr:
	UART_WriteBlocking(DEMO_UART, Leer_hora_1, sizeof(Leer_hora_1) / sizeof(Leer_hora_1[0]));
	break;
	case Lectura_fecha:
	UART_WriteBlocking(DEMO_UART, Leer_fecha_1, sizeof(Leer_fecha_1) / sizeof(Leer_fecha_1[0]));
	break;
	default:
	break;
	}
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
