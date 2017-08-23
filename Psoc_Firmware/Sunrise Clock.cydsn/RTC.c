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

#include <RTC.h>
#include <stdio.h>

void changeHourMode(uint8 mode){
    
    uint8 controlReg = readReg(CONTROL_REG_1);
    uint8 value;

    if(mode == HOURMODE_12){
        
        value = controlReg | HOURMODE_12;
    }
    else if(mode == HOURMODE_24){
        
        value = controlReg & HOURMODE_24; 
    }
    
    writeReg(CONTROL_REG_1, value);

}

void changePowerMode(uint8 mode){
    
    writeReg(CONTROL_REG_3, mode);

}


void setSec(uint8 sec){

    uint8 secondsBCD = encodeSec(sec);
    
    writeReg(SECONDS_REG, secondsBCD);
}
uint8 getSec(){

    return decodeSec(readReg(SECONDS_REG));
}

void setMin(uint8 minutes){

    uint8 minutesBCD = encodeMin(minutes);
    writeReg(MINUTES_REG,minutesBCD);

}
uint8 getMin(){

    return decodeMin(readReg(MINUTES_REG));

}

void setHours(uint8 hour){

    uint8 bcdHour = encodeHours24(hour);
    
    writeReg(HOURS_REG,bcdHour);

}
uint8 getHours(){

    uint8 hourBCD = readReg(HOURS_REG);
    
    return decodeHours24(hourBCD);

}

void setDay(uint8 day){

    uint8 bcdDay = encodeDays(day);
    
    writeReg(DAYS_REG,bcdDay);

}
uint8 getDay(){

    uint8 dayBCD = readReg(DAYS_REG);
    
    return decodeHours24(dayBCD);

}

void setWkDay(uint8 wkday){
    
    uint8 bcdWkday = encodeWeekDay(wkday);
    writeReg(WEEKDAY_REG, bcdWkday);
    
}
uint8 getWkDay(){

    uint8 wkDayBCD = readReg(WEEKDAY_REG);
    
    return decodeWeekDay(wkDayBCD);
    
}

void setMonth(uint8 month){

    uint8 bcdMonth = encodeMonth(month);
    writeReg(MONTH_REG,bcdMonth);
    
}
uint8 getMonth(){

    uint8 monthBCD = readReg(MONTH_REG);
    
    return decodeMonth(monthBCD);

}

void setYear(uint8 year){

    uint8 bcdYear = encodeYear(year);
    
    writeReg(YEAR_REG,bcdYear);

}
uint8 getYear(){

    uint8 yearBCD = readReg(YEAR_REG);
    
    return decodeYear(yearBCD);

}

void getTime(struct time *currentTime){
    
    
    currentTime->year    =   getYear();
    currentTime->month   =   getMonth();   
    currentTime->day     =   getDay();
    currentTime->weekday =   getWkDay();
    currentTime->hour    =   getHours();
    currentTime->minute  =   getMin();
    currentTime->second  =   getSec();
   

}

void setTime(struct time *currentTime){
    

setSec(currentTime->second);   
setMin(currentTime->minute);
setHours(currentTime->hour);
setWkDay(currentTime->weekday);
setDay(currentTime->day);
setMonth(currentTime->month);  
setYear(currentTime->year); 

}

void createAlarm(struct time *alarm, uint8 weekDay, uint8 hour, uint8 minute){


    alarm->year = 0xFF;
    alarm->month = 0xFF;
    alarm->day =0xFF;
    alarm->weekday = weekDay;
    alarm->hour = hour;
    alarm->minute = minute;
    alarm->second = 0;

}

void createAlarmTEST(struct time *alarm,uint8 minute, uint8 second){

    alarm->year = 0xFF;
    alarm->month = 0xFF;
    alarm->day =0xFF;
    alarm->weekday = 0xFF;
    alarm->hour = 0xFF;
    alarm->minute = minute;
    alarm->second = second;
}

char checkAlarm(struct time *currentTime, struct time *alarmTime){
/* This function checks if the current time is equal to a time alarm.
 * If the times are equal the function returns 0. If a field of time
 * is to be ignored, the alarmTime should have 0xFF as that field.
 *  
 */
    char result = 0;
    
    // Check that each field of time is equal and not 0xFF.
    // If a field is 0xFF, then the if statment will always be false and not execute
    // effectivley rendering it ignored. If a field is not 0xFF, then only the relation to current
    // matters.
    if((!(currentTime->year == alarmTime->year)) && (!(alarmTime->year == 0xFF))){
        result++ ;
    }
    if((!(currentTime->month == alarmTime->month)) && (!(alarmTime->month == 0xFF))){
        result++ ;
    }
    if((!(currentTime->day == alarmTime->day)) && (!(alarmTime->day == 0xFF))){
        result++ ;
    }

    // each bit of alarmTime->weekday coresponds to a weekday, so to check if the current 
    //day is part of alram, 1 is shifted by the value of the current wkday to make a bit mask.
    if((!(alarmTime->weekday & (1 << currentTime->weekday))) && (!(alarmTime->weekday == 0xFF))){
        result++ ;
    }
    if((!(currentTime->hour == alarmTime->hour)) && (!(alarmTime->hour == 0xFF))){
        result++ ;
    }
    if((!(currentTime->minute == alarmTime->minute)) && ( !(alarmTime->minute == 0xFF))){
        result++ ;
    }
    if((!(currentTime->second == alarmTime->second)) && (!(alarmTime->second == 0xFF))){
        result++ ;
    }
    
    

    return result;
}

void softReset(){

writeReg(CONTROL_REG_1, RESET_VALUE);
    
}

void printTime(struct time *currentTime){

        char output[75];
        sprintf(output,"year: %d month: %d day:%d wkDay:%d %d:%2d:%d \n\r",currentTime->year,currentTime->month,currentTime->day,currentTime->weekday ,currentTime->hour, currentTime->minute,currentTime->second);
        UART_1_UartPutString(output);
}



/* [] END OF FILE */
