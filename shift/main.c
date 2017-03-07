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
#include <project.h>
#include <stdio.h>
void shiftOut(uint16_t output){
    CyPins_ClearPin(Latch_0); // set latch pin low, so output doesnt display/change
    
    for(char i = 0; i<16; i++){
        
        CyPins_ClearPin(Clock_0); // clock pin low
        Data_Write((output >> (15-i)) && 0x01); // set data 
        CyPins_SetPin(Clock_0);// clock pin high
    }

    CyPins_SetPin(Latch_0); // set latch pin high, so output is displayed.
}

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        uint16_t value = 0xFFFF;
 
        shiftOut(value);
    }
}  



/* [] END OF FILE */

