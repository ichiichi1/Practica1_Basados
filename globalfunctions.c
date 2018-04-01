/*
 * GlobalFunctions.c
 *
 *  Created on: Apr 1, 2018
 *      Author: Felipe Rivera
 */


#include "GlobalFunctions.h"
#include "fsl_port.h"

void delay(uint16_t delay)
{
	volatile int counter, counter2;

	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--);

	}
}
