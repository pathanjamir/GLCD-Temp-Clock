                          		/* i2c.h */
#ifndef __I2C_H__
#define __I2C_H__

#include "types.h"
//declarations/prototypes for i2c Bus Events (bit-banging method)
void i2cStart(void);
void i2cStop(void);
void i2cReStart(void);
void i2cWrite(u8);
u8 i2cRead(void);
void i2cAck(void);
void i2cNAck(void);
void i2cMasterAck(void);

//declarations/prototypes for i2c communication algorithms for 
//eeprom slave 24c01/24c02
void i2cByteWrite(u8,u8,u8);
u8 i2cRandomRead(u8,u8);
void i2cPageWrite(u8,u8,u8 *,u8);
void i2cSeqRead(u8,u8,u8 *,u8);

#endif  
