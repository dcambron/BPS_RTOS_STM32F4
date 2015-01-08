#ifndef __I2C_H
#define __I2C_H

#include <stm32f4xx.h> 

extern void init_I2C1(void);

/* This function issues a start condition and 
 * transmits the slave address + R/W bit
 * 
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the tranmission direction can be:
 * 						I2C_Direction_Tranmitter for Master transmitter mode
 * 						I2C_Direction_Receiver for Master receiver
 */
extern void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);

/* This function transmits one byte to the slave device
 * Parameters:
 *		I2Cx --> the I2C peripheral e.g. I2C1 
 *		data --> the data byte to be transmitted
 */
extern void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);

/* This function reads one byte from the slave device 
 * and acknowledges the byte (requests another byte)
 */
extern uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
extern uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
extern void I2C_stop(I2C_TypeDef* I2Cx);

#endif
