/*
 * UART.c
 *
 *  Created on: Mar 10, 2018
 *      Author: Lenovo
 */

#include "board.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

#include <stdio.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "UART.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* UART instance and clock */


////////////////////////////////////////////////////////////////////////////////
/////////////////////// UTILIZADAS EN MENÚ PRINCIPAL ///////////////////////////

uint8_t menu_princ[] =
              " 1-Leer memoria I2C\r\n "
              " 2-Escribir memoria I2C\r\n"
              " 3-Establecer hora\r\n  "
              " 4-Establecer Fecha\r\n "
              " 5-Formato de hora\r\n "
              " 6-Leer hora\r\n "
              " 7-Leer fecha\r\n";
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





uint8_t g_tipString[] =
    "Uart interrupt example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";

uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};
uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};
volatile bool rxBufferEmpty = true;
volatile bool txBufferFull = false;
volatile bool txOnGoing = false;
volatile bool rxOnGoing = false;

	uart_config_t config;
    uart_config_t config1;

    uart_transfer_t xfer;
    uart_transfer_t sendXfer;
    uart_transfer_t receiveXfer;
    uart_handle_t g_uartHandle;

extern void UART1_DriverIRQHandler(void);
extern void UART0_DriverIRQHandler(void);

void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing = false;
    }

    if (kStatus_UART_RxIdle == status)
    {
        rxBufferEmpty = false;
        rxOnGoing = false;
    }
}

void UART_START(void)
{


    CLOCK_EnableClock(kCLOCK_PortC);
        port_pin_config_t config_UART1 =
           	{ kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
           			kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAlt3,
           			kPORT_UnlockRegister, };

           	PORT_SetPinConfig(PORTC, 3, &config_UART1);
           	PORT_SetPinConfig(PORTC, 4, &config_UART1);

           	    /*Inicializamos la UART1 y les pasamos parametros*/

           	    UART_GetDefaultConfig(&config1);
           	    config1.baudRate_Bps = 9600; //BOARD_DEBUG_UART_BAUDRATE
           	    config1.enableTx = true;
           	    config1.enableRx = true;

           	    UART_Init(DEMO_UART1, &config1, DEMO_UART1_CLK_FREQ);
           	    UART_TransferCreateHandle(DEMO_UART1, &g_uartHandle, UART_UserCallback, NULL);

           	    /*Inicializamos la UART0 y le pasamos los parametros*/

           	    UART_GetDefaultConfig(&config);
				config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
				config.enableTx = true;
				config.enableRx = true;

				UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
				UART_TransferCreateHandle(DEMO_UART, &g_uartHandle, UART_UserCallback, NULL);

}

void UART_MENU_PRINCIPAL()
{
	xfer.data = menu_princ;
	xfer.dataSize = sizeof(menu_princ) - 1;
	UART_SEND();
}

void UART_SEND()
{
	/* Send g_tipString out. */

	    txOnGoing = true;

	    UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &xfer);

	    while (txOnGoing)
	    	    {
	    	    }

	    UART_TransferSendNonBlocking(DEMO_UART1, &g_uartHandle, &xfer);

	    /* Wait send finished */
	    while (txOnGoing)
				{
				}

}

void UART_RECIVE(void)
{
/* Start to echo. */
    sendXfer.data = g_txBuffer;
    sendXfer.dataSize = ECHO_BUFFER_LENGTH;
    receiveXfer.data = g_rxBuffer;
    receiveXfer.dataSize = ECHO_BUFFER_LENGTH;

    while (1)
    {
    	 /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
    	            if ((!rxOnGoing) && rxBufferEmpty)
    	            {
    	                rxOnGoing = true;
    	                UART_TransferReceiveNonBlocking(DEMO_UART, &g_uartHandle, &receiveXfer, NULL);
    	            }

    	            /* If TX is idle and g_txBuffer is full, start to send data. */
    	            if ((!txOnGoing) && txBufferFull)
    	            {
    	                txOnGoing = true;
    	                UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &sendXfer);
    	            }

    	            /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
    	            if ((!rxBufferEmpty) && (!txBufferFull))
    	            {
    	                memcpy(g_txBuffer, g_rxBuffer, ECHO_BUFFER_LENGTH);
    	                rxBufferEmpty = true;
    	                txBufferFull = true;
    	            }
    }
}

void UART_MENU(values_t valor)
{
	switch(valor)
	{
	case Lectura_I2C_1:
	xfer.data = Leer_I2C_2;
    xfer.dataSize = sizeof(Leer_I2C_2) - 1;
	UART_SEND();
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
