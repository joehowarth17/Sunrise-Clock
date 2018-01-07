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
    
void updateDisplay(struct time *newTime){
// This function updates the seven segment diplay via attiny85.
// The time is updated by pulsing select pin to reset the time stored in attiny
// and then pulsing the clock pin repeatedly increasing the time by one minute each pulse.
    
            SelectPin_Write(1);
            CyDelayUs(50);
            SelectPin_Write(0);
            CyDelayUs(100);  
            SelectPin_Write(1);
            
            uint16_t i;
            uint16_t mins = newTime->hour * 60 + newTime->minute; // Get time in minutes
            
            printlnNum(mins,'X');
            
            for(i= 0;i<mins;i++){
                
            ClockPin_Write(1);
            CyDelayUs(200);
            ClockPin_Write(0);
            CyDelayUs(200);
            

    }
            ClockPin_Write(1);
            

}
    
int main()
{
    CyDelay(1000); // Wait for esp8266 to initialize first.
    
    I2C_Start();
    
    UART_1_SetCustomInterruptHandler(ReceiveISR);

    UART_1_Start();   
    

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    
    
    //  check that rtc is in battery backup mode
    uint8 control3 = readReg(CONTROL_REG_3) ;
    if((control3 >>4) != 0xA){
        
        // Flash led 3 to signal error.
        Pin_3_Write(1);
        CyDelay(1000);
        Pin_3_Write(0);
        CyDelay(1000);
        Pin_3_Write(1);
        CyDelay(1000);
        Pin_3_Write(0);
        
        //printlnNum(control3,'X'); // show control value
        
        uint8_t registerValue = 0xA0;// write 1010 to PM bits which enable directSwitching and disable low batt moniter, write 0000 to battery flags
        writeReg(CONTROL_REG_3,registerValue); 
        control3 = readReg(CONTROL_REG_3);
        
       // printlnNum(control3,'X');
        //UART_1_UartPutString("Error: Baterry backup did not work\n\r");
    }
    
    if((control3 & 0x0F) != 0){
        
        //flash led 2 to show error.
        Pin_2_Write(1);
        CyDelay(2000);
        Pin_2_Write(0);
        
        //printlnNum(control3,'X'); // show control value
        
        writeReg(CONTROL_REG_3,0xA0); 
        control3 = readReg(CONTROL_REG_3);
        
        //printlnNum(control3,'X');
        //UART_1_UartPutString("Note: Power was lost. Battery backup successfull!\n\r");
    
    }
    
 
    struct time currentTime;
    uint8 hour;
    uint8 seconds;
    uint8 minutes;
    
    // Uncomment call to setTime to update the time manually.    
    currentTime.year =18;
    currentTime.month=1;
    currentTime.day = 6;
    currentTime.weekday = SATURDAY;
    currentTime.hour = 20;
    currentTime.minute=19;
    currentTime.second = 0;
    //setTime(&currentTime);
    
    struct time alarm;
    uint8_t alarmState = 0; 
    
    struct time displayTime;
    createAlarmTEST(&displayTime,0xFF,0); // make an alarm to update display every second
    uint8_t displayState = 0;

/*    set clock to update time at 3:25
 *    uncomment time assignment to pick time. 
 *    Currently updating every minute at 25 seconds.
 */ 
    struct time calibrateTimeAlarm;
    uint8_t calibrateTimeState = 0;
      createAlarmTEST(&calibrateTimeAlarm,0xFF,25);
//    calibrateTimeAlarm.year    = 0xFF;
//    calibrateTimeAlarm.month   = 0xFF;
//    calibrateTimeAlarm.day     = 0xFF;
//    calibrateTimeAlarm.weekday = 0xFF;
//    calibrateTimeAlarm.hour    = 3;
//    calibrateTimeAlarm.minute  = 25;
//    calibrateTimeAlarm.second  = 25;   

    
    int count = 0;                  // Used to control how often time is printed.
    getTime(&currentTime);
    updateDisplay(&currentTime);
    
for(;;)
    { 
        // Recieve data from uart.
        if(ReceiveFlag == -1){
            
            //flash led and print to show data has been recieved.
            UART_1_UartPutString("in flag = -1");
                Pin_2_Write(1);
                CyDelay(ledDelay);
                Pin_2_Write(0);
            
            
            if((dataIn[0]&0xC0) == 0x00){
                
                // if data is a new alarm time, flash led 1.
                Pin_1_Write(1);
                CyDelay(ledDelay);
                Pin_1_Write(0);

                
                uint8 min  = dataIn[0];
                uint8 wk   = dataIn[2];
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
                
                // If data is updated time from ntp, flash led 4.
                Pin_4_Write(1);
                CyDelay(ledDelay);
                Pin_4_Write(0);
            
                uint8_t mins = dataIn[1];
                setMin(mins);
                
                uint8_t secs = dataIn[0] &= 0x3F; // 0011 1111
                setSec(secs);
                
                updateDisplay(&currentTime);
            }
            ReceiveFlag =0; // Clear uart RX flag.
        }
        
        getTime(&currentTime); // get new time form RTC module.
        
        uint8_t check = 255; // 0 if the time matches an alarm, otherwise value>0
        
        // Check all the alarms.
        int i;
        for(i = 0; i <numAlarms; i++){
           
            if(!(checkAlarm(&currentTime,alarms[i]))){
            
                check = 0;
            }
            
        }
        //If any of the alarms are active and have not been taken care of, flash led 5 and pulse pin to signal ESP8266.
        if(!check && !alarmState){
            check = 255;
            alarmState = 1;
            
            Pin_5_Write(1);
            AlarmInterrupt_Write(0);
            
            CyDelay(ledDelay);
            
            Pin_5_Write(0);
            AlarmInterrupt_Write(1);
        }
        // When the time no longer matches alarm (check>0), and an alarm has been set, clear alarm.
        if(check && alarmState){
            alarmState = 0;
        }
        
        //Check alarm that sends request to ESP8266 for ntp time.
        if(!(checkAlarm(&currentTime, &calibrateTimeAlarm)) && !calibrateTimeState){
        calibrateTimeState = 1;
        CalibrateInterrupt_Write(0);
         CyDelay(1);
        CalibrateInterrupt_Write(1);       
        }
        else if((checkAlarm(&currentTime, &calibrateTimeAlarm)) && calibrateTimeState){
            
            calibrateTimeState = 0;
        }
        
        if(!(checkAlarm(&currentTime, &displayTime)) && !displayState){
        // if the time matches and the display hasnt already been updated
        // then write the clock pin high and set displayState
           
            //Increment time on display by one minute.
            ClockPin_Write(0);
            CyDelayUs(200);
            ClockPin_Write(1);
            
            //flash led
            Pin_1_Write(1);
            CyDelay(100);
            Pin_1_Write(0);
            
            displayState =1;
        }
        else if(checkAlarm(&currentTime, &displayTime) && displayState){
        // if the time no longer matches and displayState hasnt been reset,
        //then reset displayState
            displayState =0; 
        }
                
        char output[25];
        if(count%25 ==0 ){
            
            printTime(&currentTime);
        
        }

        count++;

    }   
    
}



/* [] END OF FILE */
