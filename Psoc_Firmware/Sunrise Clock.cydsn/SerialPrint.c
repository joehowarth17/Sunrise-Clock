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
#include <SerialPrint.h>

void printNum(uint16 input,char format){

    char output[8];
    char formatter[3];
    
    sprintf(formatter,"%%%c", format);
    sprintf(output, formatter, input);
    UART_1_UartPutString(output);
}

void printlnNum(uint16 input, char format){

    char output[8];
    char formatter[5];
    
    sprintf(formatter,"%%%c\n\r", format);
    sprintf(output, formatter, input);
    UART_1_UartPutString(output);
    
}


/* [] END OF FILE */
