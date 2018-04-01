/*
 * I2C.c
 *
 *  Created on: Apr 1, 2018
 *      Author: Lenovo
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_port.h"
#include "I2C.h"



volatile bool g_MasterCompletionFlag = false;

i2c_master_config_t masterConfig;
i2c_master_handle_t g_m_handle;
i2c_master_transfer_t masterXfer_tx;
i2c_master_transfer_t masterXfer_rx;

uint8_t DATA = 0x01;


static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,
		status_t status, void * userData)
{
	/* Signal transfer success when received success status.*/
	if (status == kStatus_Success)
	{
		g_MasterCompletionFlag = true;
	}
}

void I2C_INIT(void)
	{
	CLOCK_EnableClock(kCLOCK_PortB);
	    CLOCK_EnableClock(kCLOCK_I2c0);

	    port_pin_config_t config_i2c =
	    	{ kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
	    	        kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAlt2,
	    	        kPORT_UnlockRegister, };

	    PORT_SetPinConfig(PORTB, 2, &config_i2c);
	    PORT_SetPinConfig(PORTB, 3, &config_i2c);

	    /* Get default configuration for master.*/

	    I2C_MasterGetDefaultConfig(&masterConfig);

	    masterConfig.baudRate_Bps = 100000;


	    /* Init I2C master.*/
	    I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));


	   I2C_MasterTransferCreateHandle(I2C0, &g_m_handle,
			   i2c_master_callback, NULL);



		}

//device_t device, mode_t mode, uint16_t adress, uint8_t data
void I2C_WRITE_MEM(uint16_t adress, uint8_t data, uint8_t size)
{
	 	masterXfer_tx.slaveAddress = 0x51;
	    masterXfer_tx.direction = kI2C_Write;
	    masterXfer_tx.subaddress = 0x03;
	    masterXfer_tx.subaddressSize = 1;
	    masterXfer_tx.data = &DATA;
	    masterXfer_tx.dataSize = 2;
	    masterXfer_tx.flags = kI2C_TransferDefaultFlag;

	    I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer_tx);
	    /* Wait for transfer completed.*/

	    while (!g_MasterCompletionFlag)
	    {
	    }
	    g_MasterCompletionFlag = false;

}

void I2C_READ_MEM(uint16_t adress, uint8_t data, uint8_t size)
{
	    static uint8_t read_data;

	    masterXfer_rx.slaveAddress = 0x51;
	    masterXfer_rx.direction = kI2C_Read;
	    masterXfer_rx.subaddress = 0x03;
	    masterXfer_rx.subaddressSize = 1;
	    masterXfer_rx.data = &read_data; //tenia amperson
	    masterXfer_rx.dataSize = 2;
	    masterXfer_rx.flags = kI2C_TransferDefaultFlag;

	    I2C_MasterTransferNonBlocking(I2C0, &g_m_handle,
	    		&masterXfer_rx);

	    while (!g_MasterCompletionFlag)
	    {
	    }

	    g_MasterCompletionFlag = false;

}

void I2C_WRITE_CLK(uint8_t adress, uint8_t data)
{
	 	masterXfer_tx.slaveAddress = 0x50;
	    masterXfer_tx.direction = kI2C_Write;
	    masterXfer_tx.subaddress = 0x03;
	    masterXfer_tx.subaddressSize = 1;
	    masterXfer_tx.data = &DATA;
	    masterXfer_tx.dataSize = 2;
	    masterXfer_tx.flags = kI2C_TransferDefaultFlag;

	    I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer_tx);
	    /* Wait for transfer completed.*/

	    while (!g_MasterCompletionFlag)
	    {
	    }
	    g_MasterCompletionFlag = false;

}

void I2C_READ_CLK(uint8_t adress, uint8_t data)
{
	    static uint8_t read_data;

	    masterXfer_rx.slaveAddress = 0x50;
	    masterXfer_rx.direction = kI2C_Read;
	    masterXfer_rx.subaddress = 0x03;
	    masterXfer_rx.subaddressSize = 1;
	    masterXfer_rx.data = &read_data; //tenia amperson
	    masterXfer_rx.dataSize = 2;
	    masterXfer_rx.flags = kI2C_TransferDefaultFlag;

	    I2C_MasterTransferNonBlocking(I2C0, &g_m_handle,
	    		&masterXfer_rx);

	    while (!g_MasterCompletionFlag)
	    {
	    }

	    g_MasterCompletionFlag = false;

}

