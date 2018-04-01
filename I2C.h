/*
 * I2C.h
 *
 *  Created on: Apr 1, 2018
 *      Author: Lenovo
 */

#ifndef I2C_H_
#define I2C_H_

#define SEC 		0x02
#define MINU 		0x03
#define HR  		0x04
#define FECHA1  	0x05
#define FECHA2  	0x06
#define FORMATO     0x04


void I2C_INIT(void);
void I2C_READ(void);
void I2C_WRITE(void);



#endif /* I2C_H_ */
