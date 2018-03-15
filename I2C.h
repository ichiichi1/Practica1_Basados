/*
 * I2C.h
 *
 *  Created on: Mar 12, 2018
 *      Author: Lenovo
 */

#ifndef I2C_H_
#define I2C_H_

//static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle,status_t status, void * userData);

 void I2C_START(void);

 static void i2c_release_bus_delay(void);

 void i2c_ReleaseBus();

 void I2C_READ_MEM(void);

 void I2C_WRITE_MEM(void);

 void I2C_READ_RTC(void);

 void I2C_WRITE_RTC(void);
#endif /* I2C_H_ */
