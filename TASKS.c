/*
 * TASKS.c
 *
 *  Created on: Mar 8, 2018
 *      Author: Lenovo
 */

#include "UART.h"

void Menu_principal(void *arg)
{
	for(;;)
	{
		UART_MENU_PRINCIPAL();
	}
}

void Leer_memoria_i2c(void *arg)
{
	for(;;)
	{

	}
}

void Escribir_memoria_i2c(void *arg)
{
	for(;;)
	{

	}
}

void Establecer_Hora(void *arg)
{
	for(;;)
	{

	}
}

void Establecer_fecha(void *arg)
{
	for(;;)
	{

	}
}

void Formato_de_hora(void *arg)
{
	for(;;)
	{

	}
}

void Leer_hora(void *arg)
{
	for(;;)
	{

	}
}

void Leer_fecha(void *arg)
{
	for(;;)
	{

	}
}

void Terminal_2(void *arg)
{
	for(;;)
	{

	}
}

void ECO(void *arg)
{
	for(;;)
	{

	}
}

/*
data_to send = data;
masterXfer.salveAdress = MEME_SALVE_DIR;
masterXfer.DIRECTION = kI2C_Write;
masterXfer.subadress = address;
masterXfer.subadresssize = 2;
masterXfer.data = &data_to_send;
masterXfer.datasize = 1;
masterXfer.flags = kI2C_TransferDefault Flag;
while() */


