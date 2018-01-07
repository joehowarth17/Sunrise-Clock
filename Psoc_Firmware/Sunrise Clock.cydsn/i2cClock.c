/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <i2cClock.h>



uint8 readReg(uint8 Reg){
    
// write register adress to slave adress
// use MasterReadBuff to store contents of register in read buffer
    
    uint8 writeBuffer[1] = {0}; 
    writeBuffer[0] = Reg;               
    // put register address into write buffer

    uint8 readBuffer[1] = {0};

    I2C_I2CMasterWriteBuf(CLOCK_ADDR, (uint8 *)writeBuffer,1, I2C_I2C_MODE_NO_STOP);
    //send register adress to slave at clock adress
    
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    // wait until transfer is done

    I2C_I2CMasterReadBuf(CLOCK_ADDR,(uint8 *)readBuffer,1,I2C_I2C_MODE_REPEAT_START);
    // read contents of register
    
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)==0){}
    // wait until read is done
    
    return readBuffer[0];

}

void writeReg(uint8 Reg, uint8 value){
    
// first write register address to slave, then write value
    
    uint8  writeBuffer[2];
    
    writeBuffer[0] = Reg; 
    writeBuffer[1] = value;   
    
    I2C_I2CMasterWriteBuf(CLOCK_ADDR, (uint8 *)writeBuffer, 2, I2C_I2C_MODE_COMPLETE_XFER);
    // write values
    
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    // wait until write is complete

}

void    writeMultiReg(uint8 startReg, uint8 values[], uint8 n){
    
// first write register address to slave, then write value
    
    uint8  writeBuffer[n+1];
    writeBuffer[0] = startReg;
    
    int i = 0;
    for(i =1; i<n+1; i++){
    
        writeBuffer[i] = values[i-1];
    }
    
    I2C_I2CMasterWriteBuf(CLOCK_ADDR, (uint8 *)writeBuffer, n+1, I2C_I2C_MODE_COMPLETE_XFER);
    // write values
    
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){}
    // wait until write is complete

}
/*
void    readMultiReg(uint8 startReg, uint8* readBuffer, uint8 n){

    // write register adress to slave adress
// use MasterReadBuff to store contents of register in read buffer
    
    uint8 writeBuffer[1] = {0}; 
    writeBuffer[0] = startReg;               
    // put register address into write buffer

    I2C_I2CMasterWriteBuf(CLOCK_ADDR, (uint8 *)writeBuffer,1, I2C_I2C_MODE_NO_STOP);
    //send register adress to slave at clock adress
    
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)==0){}
    // wait until transfer is done

    I2C_I2CMasterReadBuf(CLOCK_ADDR,(uint8 *)readBuffer,n,I2C_I2C_MODE_REPEAT_START);
    // read contents of register
    
    while((I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)==0){}
    // wait until read is done
    
    //return readBuffer[];

}*/

/* [] END OF FILE */
