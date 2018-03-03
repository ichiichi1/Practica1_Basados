/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Practica1_BOTONES.c
 * @brief   Application entry point.
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
/* TODO: insert other include files here. */

#define Leer_mem (1<<2)
#define Escrib_mem (1<<3)
#define Estab_hora (1<<10)
#define Estab_fecha (1<<11)
#define Formato_hr (1<<19)
#define Leer_hr (1<<20)
#define Leer_fech (1<<18)
#define Term2 (1<<23)
#define ECO (1<<9)

/* TODO: insert other definitions and declarations here. */

typedef enum
{
	Leer_i2c,
	Escribir_i2c,
	Hora,
	Fecha,
	Formato_hora,
	Leer_hora,
	Leer_fecha,
	Terminal2,
	Eco,
	Error
}Tasks_t;

void PORTB_IRQHandler()
{
	uint32_t Button = (PORT_GetPinsInterruptFlags(PORTB));
/*	if(Button && Leer_mem)
	{

	}
	else if(Button && Escrib_mem)
	{

	}
	else if(Button && Estab_hora)
	{

	}
	else if(Button && Estab_fecha)
	{

	}
	else if(Button && Formato_hr)
	{

	}
	else if(Button && Leer_hr)
	{

	}
	else if(Button && Leer_fech)
	{

	}
	else if(Button && Term2)
	{

	}
	else if(Button && ECO)
	{

	}
	else
	{
		//error
	}*/
	PORT_ClearPinsInterruptFlags(PORTB, (PORT_GetPinsInterruptFlags(PORTB)));

}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_PortB);

    port_pin_config_t config_switch =
    	{ kPORT_PullDisable, kPORT_SlowSlewRate, kPORT_PassiveFilterDisable,
    			kPORT_OpenDrainDisable, kPORT_LowDriveStrength, kPORT_MuxAsGpio,
    			kPORT_UnlockRegister};
    	PORT_SetPinInterruptConfig(PORTB, 2, kPORT_InterruptFallingEdge);
    /*	PORT_SetPinInterruptConfig(PORTB, 3, kPORT_InterruptFallingEdge);
    	PORT_SetPinInterruptConfig(PORTB, 10, kPORT_InterruptFallingEdge);
    	PORT_SetPinInterruptConfig(PORTB, 11, kPORT_InterruptFallingEdge);
    	PORT_SetPinInterruptConfig(PORTB, 18, kPORT_InterruptFallingEdge);
    	PORT_SetPinInterruptConfig(PORTB, 19, kPORT_InterruptFallingEdge);

    	PORT_SetPinInterruptConfig(PORTB, 20, kPORT_InterruptFallingEdge);
    	PORT_SetPinInterruptConfig(PORTB, 23, kPORT_InterruptFallingEdge);
    	PORT_SetPinInterruptConfig(PORTB, 9, kPORT_InterruptFallingEdge);

  	*/


    	PORT_SetPinConfig(PORTB, 2, &config_switch);
    /*	PORT_SetPinConfig(PORTB, 3, &config_switch);
    	PORT_SetPinConfig(PORTB, 10, &config_switch);
    	PORT_SetPinConfig(PORTB, 11, &config_switch);
    	PORT_SetPinConfig(PORTB, 20, &config_switch);
    	PORT_SetPinConfig(PORTB, 19, &config_switch);

    	PORT_SetPinConfig(PORTB, 18, &config_switch);
    	PORT_SetPinConfig(PORTB, 23, &config_switch);
    	PORT_SetPinConfig(PORTB, 9, &config_switch);

  	*/

    	gpio_pin_config_t switch_config_gpio =
    		{ kGPIO_DigitalInput, 1 };

		GPIO_PinInit(GPIOB, 2, &switch_config_gpio);
	 /*	GPIO_PinInit(GPIOB, 3, &switch_config_gpio);
		GPIO_PinInit(GPIOB, 10, &switch_config_gpio);
		GPIO_PinInit(GPIOB, 11, &switch_config_gpio);
		GPIO_PinInit(GPIOB, 20, &switch_config_gpio);
		GPIO_PinInit(GPIOB, 19, &switch_config_gpio);

		GPIO_PinInit(GPIOB, 18, &switch_config_gpio);
		GPIO_PinInit(GPIOB, 23, &switch_config_gpio);
		GPIO_PinInit(GPIOB, 9, &switch_config_gpio);


		*/

		NVIC_EnableIRQ(PORTB_IRQn);


		printf("Hello World\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
    }
    return 0 ;
}
