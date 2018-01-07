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

#include <Interrupts.h>
#include <project.h>
#include <SerialPrint.h>

 uint8_t ledState = 0;
CY_ISR(ReceiveISR){
    
    dataIn[byteNum%3] = UART_1_UartGetByte();
//    dataIn[1] = UART_1_UartGetByte();
//    dataIn[2] = UART_1_UartGetByte();
    printlnNum(dataIn[byteNum%3],'X');
//    printlnNum(dataIn[1],'X');
//    printlnNum(dataIn[2],'X');
    
    uint32 intsrc = UART_1_GetRxInterruptSourceMasked();
    byteNum += 1;
    if(byteNum%3==0){
    ReceiveFlag = -1;}
    UART_1_ClearRxInterruptSource(intsrc);
    ledState = !ledState;
    Pin_4_Write(ledState);
    }
    

/* [] END OF FILE */
