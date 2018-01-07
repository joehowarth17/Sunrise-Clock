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
#include <Interrupts.h>

    volatile uint8_t dataIn[3];
    volatile int8_t  ReceiveFlag =0;
    volatile uint8_t byteNum = 0;
    uint8_t ledDelay = 250;
    struct time *alarms[7]; // array of all alarms
    uint8_t numAlarms = 0;
    uint8_t MAX_ALARMS = 7;
    
int main()
{
    CyDelay(1000);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Start();
    
    
    UART_1_SetCustomInterruptHandler(ReceiveISR);

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
        
        //printlnNum(control3,'X');
        //changeHourMode(EVERYTHING_ENABLED);
        uint8_t registerValue = 0xA0;// write 1010 to PM bits which enable directSwitching and disable low batt moniter, write 0000 to battery flags
        writeReg(CONTROL_REG_3,registerValue); 
        control3 = readReg(CONTROL_REG_3);
       // printlnNum(control3,'X');
        //UART_1_UartPutString("Error: Baterry backup did not work\n\r");
    }
    
    if((control3 & 0x0F) != 0){
        Pin_2_Write(1);
        CyDelay(2000);
        Pin_2_Write(0);
        
        //printlnNum(control3,'X');


        writeReg(CONTROL_REG_3,0xA0); 
        control3 = readReg(CONTROL_REG_3);
        //printlnNum(control3,'X');
        //UART_1_UartPutString("Note: Power was lost. Battery backup successfull!\n\r");
    
    }
    
    

    
    struct time currentTime;
    //currentTime.second = 21;
    uint8 hour;
    uint8 seconds;
    uint8 minutes;
    
    
    currentTime.year =17;
    currentTime.month=8;
    currentTime.day = 17;
    currentTime.weekday = THURSDAY;
    currentTime.hour = 23;
    currentTime.minute=52;
    currentTime.second = 0;
    
    struct time alarm;
//    createAlarmTEST(&alarm,0xFF,30);
//    
//    alarms[numAlarms] = alarm;
//    numAlarms++;
//    
//    
//    createAlarmTEST(&alarm,0xFF,0);
//    
//    alarms[numAlarms] = alarm;
//    numAlarms++;
    
    struct time calibrateTimeAlarm;
    
    // set clock to update time at 3:25:25
//    calibrateTimeAlarm.year    = 0xFF;
//    calibrateTimeAlarm.month   = 0xFF;
//    calibrateTimeAlarm.day     = 0xFF;
//    calibrateTimeAlarm.weekday = 0xFF;
//    calibrateTimeAlarm.hour    = 3;
//    calibrateTimeAlarm.minute  = 25;
//    calibrateTimeAlarm.second  = 25;
    createAlarmTEST(&calibrateTimeAlarm,0xFF,25);
    
    //struct time alarm2;
    //setTime(&currentTime);
    int count = 0;

for(;;)
    { 
        

           
//        hour = getHours();
//        seconds = getSec();
//        minutes = getMin();


//        getTime(&currentTime);
//        char check = (checkAlarm(&currentTime,&alarm));
//        if(!check){
//        Pin_3_Write(1);
//        CyDelay(1000);
//        Pin_3_Write(0);
//        }

        if(ReceiveFlag == -1){
            UART_1_UartPutString("in flag = -1");
                Pin_2_Write(1);
                CyDelay(ledDelay);
                Pin_2_Write(0);
            if((dataIn[0]&0xC0) == 0x00){
                Pin_1_Write(1);
                CyDelay(ledDelay);
                Pin_1_Write(0);
                
              
                
            uint8 min = dataIn[0];
            uint8 wk  = (dataIn[2]);
            uint8 hour = dataIn[1];
            
            printlnNum(min,'X');
            printlnNum(hour,'X');
            printlnNum(wk,'X');
            
            createAlarm(&alarm,wk,hour,min);
            
            // if number of alarms is greater than 7 start overwriting previous alarms
            if(numAlarms == MAX_ALARMS){
            
                numAlarms = 0;
            }
            alarms[numAlarms] = &alarm; 
            numAlarms += 1;  
            
            UART_1_UartPutString("alarm Made");
            
            }
            
            if((dataIn[0]&0xC0) == 0xC0){
                Pin_4_Write(1);
                CyDelay(ledDelay);
                Pin_4_Write(0);
            
                uint8_t mins = dataIn[1];
                setMin(mins);
                uint8_t secs = dataIn[0] &= 0x3F; // 0011 1111
                setSec(secs);
            
            }
            ReceiveFlag =0;
        }
        getTime(&currentTime);
        
        uint8_t check = 255;
        int i;
        for(i = 0; i <numAlarms; i++){
           
            if(!(checkAlarm(&currentTime,alarms[i]))){
            
                check = 0;
            }
            
        }
        
        if(!check){
        Pin_5_Write(1);
        AlarmInterrupt_Write(0);
        CyDelay(ledDelay);
        Pin_5_Write(0);
        AlarmInterrupt_Write(1);
        }
        
        if(!(checkAlarm(&currentTime, &calibrateTimeAlarm))){
        CalibrateInterrupt_Write(0);
         CyDelay(1);
        CalibrateInterrupt_Write(1);
        
        }
        
       
//        if(currentTime.second == 0){
//        
//            Pin_4_Write(1);
//            CyDelay(ledDelay);
//            Pin_4_Write(0);
//        }
        


        //printlnNum(currentTime.second,'d');
        
        char output[25];
        
        //uint8 control1 = readReg(CONTROL_REG_1);
        //uint8 control2 = readReg(CONTROL_REG_2);
        uint8 control3 = readReg(CONTROL_REG_3);
        if(count%25 ==0 ){
            
            printTime(&currentTime);
            
//        sprintf(output, "control 3 :%X      ", control3);
//        sprintf(output2," %d:%2d:%d \n\r",hour, minutes,seconds);
//        UART_1_UartPutString(output);
        
        }

        count++;
        //softReset();
        //year:%d,month%d,day:%d,wkday:%d currentTime.year,currentTime.month,currentTime.day,currentTime.weekday,
        
    }    /* Place your application code here. */
    
}

/* [] END OF FILE */
