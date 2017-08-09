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
#include <RTC.h>
#include <SerialPrint.h>



int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Start();
    UART_1_Start();   

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    
    //  check that rtc is in battery backup mode
    uint8 control3 = readReg(CONTROL_REG_3) ;
    if((control3 >>4) != 0xA){
        Pin_3_Write(1);
        CyDelay(1000);
        Pin_3_Write(0);
        CyDelay(1000);
        Pin_3_Write(1);
        CyDelay(1000);
        Pin_3_Write(0);
        
        printlnNum(control3,'X');
        //changeHourMode(EVERYTHING_ENABLED);
        uint8_t registerValue = 0xA0;// write 1010 to PM bits which enable directSwitching and disable low batt moniter, write 0000 to battery flags
        writeReg(CONTROL_REG_3,registerValue); 
        control3 = readReg(CONTROL_REG_3);
        printlnNum(control3,'X');
        UART_1_UartPutString("Error: Baterry backup did not work\n\r");
    }
    
    if((control3 & 0x0F) != 0){
        Pin_2_Write(1);
        CyDelay(2000);
        Pin_2_Write(0);
        
        printlnNum(control3,'X');


        writeReg(CONTROL_REG_3,0xA0); 
        control3 = readReg(CONTROL_REG_3);
        printlnNum(control3,'X');
        UART_1_UartPutString("Note: Power was lost. Battery backup successfull!\n\r");
    
    }
//    UART_1_UartPutString("Enabling alarm interupt ...\n\r");
//    uint8_t control1 = readReg(CONTROL_REG_1);
//    printlnNum(control1,'X');
//    writeReg(CONTROL_REG_1,(control1 | 0x02));
//    printlnNum(control1,'X');
    
    struct time currentTime;
    //currentTime.second = 21;
    uint8 hour;
    uint8 seconds;
    uint8 minutes;
    
    
    currentTime.year =17;
    currentTime.month=8;
    currentTime.day = 8;
    currentTime.weekday = TUESDAY;
    currentTime.hour = 22;
    currentTime.minute=50;
    currentTime.second = 45;
    
    struct time alarm;
    createAlarmTEST(&alarm,0xFF,0);

    //setTime(&currentTime);
    int count = 0;

for(;;)
    { 
        
        //changeHourMode(HOURMODE_24);
        //setHours(14);
        //char bcd[10];
        //sprintf(bcd,"hourbcd: %d",encodeHours24(2));
        //UART_1_UartPutString(bcd);    
           
//        hour = getHours();
//        seconds = getSec();
//        minutes = getMin();


        getTime(&currentTime);
        char check = (checkAlarm(&currentTime,&alarm));
        if(!check){
        Pin_3_Write(1);
        CyDelay(1000);
        Pin_3_Write(0);
        }

        
        //printlnNum(currentTime.second,'d');
        
        char output[25];
        char output2[75];
        //uint8 control1 = readReg(CONTROL_REG_1);
        //uint8 control2 = readReg(CONTROL_REG_2);
        uint8 control3 = readReg(CONTROL_REG_3);
        if(count%25 ==0 ){
        sprintf(output, "control 3 :%X      ", control3);
        sprintf(output2,"year: %d month: %d day:%d wkDay:%d %d:%2d:%d \n\r",currentTime.year,currentTime.month,currentTime.day,currentTime.weekday ,currentTime.hour, currentTime.minute,currentTime.second);
        //sprintf(output2," %d:%2d:%d \n\r",hour, minutes,seconds);
        UART_1_UartPutString(output);
        UART_1_UartPutString(output2);
        }

        count++;
        //softReset();
        //year:%d,month%d,day:%d,wkday:%d currentTime.year,currentTime.month,currentTime.day,currentTime.weekday,
        
    }    /* Place your application code here. */
    
}

/* [] END OF FILE */
