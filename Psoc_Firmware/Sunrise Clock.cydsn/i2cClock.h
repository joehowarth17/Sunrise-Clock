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

/***************************HEADER GAURD **************************************/
#ifndef i2cClock_h
#define i2cClock_h
    
/***************************INCLUDES*******************************************/
#include <project.h>
    
/***************************MACROS*********************************************/
#define CLOCK_ADDR      (0x68) // from arduino i2c finder
    
/***************************FUNCTION DECLARATIONS******************************/    
uint8   readReg(uint8 Reg);
void    writeReg(uint8 Reg, uint8 value);
void    writeMultiReg(uint8 startReg, uint8 values[], uint8 n);    
void    readMultiReg(uint8 startReg, uint8* readBuffer, uint8 n); 
#endif
/* [] END OF FILE */
