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
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

/***************************INCLUDES*******************************************/
#include <project.h>

/***************************GLOBAL VARIABLES***********************************/
extern volatile uint8_t dataIn[3];
extern volatile int8_t  ReceiveFlag;
extern volatile uint8_t byteNum;
    
/***************************FUNCTION DECLARATIONS******************************/    
    
CY_ISR_PROTO(ReceiveISR);
#endif
/* [] END OF FILE */
