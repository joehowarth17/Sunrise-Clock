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
#include <TimeFunctions.h>


uint8 decodeSec(uint8 seconds){

    uint8 tensMask = 0x70;  // 0111 0000 (Table 13, Pg. 20 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 13, Pg. 20 PCF8523 Datasheet)
    
    uint8 tens = (seconds & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (seconds & onesMask);

    return tens  + ones; 
}
uint8 encodeSec(uint8 seconds){

    uint8 tens = seconds / 10;
    uint8 ones = seconds - (tens * 10);
    
    return (tens << 4) | ones;

}

uint8 decodeMin(uint8 minutes){

    uint8 tensMask = 0x70;  // 0111 0000 (Table 14, Pg. 21 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 14, Pg. 21 PCF8523 Datasheet)
    
    uint8 tens = (minutes & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (minutes & onesMask);

    return tens  + ones; 
}
uint8 encodeMin(uint8 minutes){

    uint8 tens = minutes / 10;
    uint8 ones = minutes - (tens * 10);
    
    return (tens << 4) | ones;

}

uint8 decodeHours12(uint8 hours){
    
    uint8 AmPmMask = 0x20;  // 0010 0000 (Table 15, Pg. 21 PCF8523 Datasheet)
    uint8 tensMask = 0x10;  // 0001 0000 (Table 15, Pg. 21 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 15, Pg. 21 PCF8523 Datasheet)
    
    uint8 tens = (hours & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (hours & onesMask);
    
    if((AmPmMask & hours) == 0){
    //tens += 100;
        
    }
    else{
        
        
    }
    return tens  + ones;
}

uint8 decodeHours24(uint8 hours){

    uint8 tensMask = 0x30;  // 0011 0000 (Table 15, Pg. 21 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 15, Pg. 21 PCF8523 Datasheet)
    
    uint8 tens = (hours & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (hours & onesMask);

    return tens  + ones; 
    
}
uint8 encodeHours24(uint8 hours){

    uint8 tens = hours / 10;   
    uint8 ones = hours -(tens *10);  
    
    tens = (tens<<4) ;
       
    uint8 output = (tens | ones);

    return output;

}

uint8 decodeDays(uint8 days){

    uint8 tensMask = 0x30;  // 0011 0000 (Table 16, Pg. 21 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 16, Pg. 21 PCF8523 Datasheet)
    
    uint8 tens = (days & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (days & onesMask);

    return tens  + ones;

}
uint8 encodeDays(uint8 days){

    uint8 tens = days / 10;
    uint8 ones = days - (tens * 10);
    
    return (tens << 4) | ones;

}

uint8 decodeWeekDay(uint8 weekday){

    uint8 onesMask = 0x0F;  // 0000 1111 (Table 17, Pg. 22 PCF8523 Datasheet)
    
    uint8 ones = (weekday & onesMask);

    return ones;

}
uint8 encodeWeekDay(uint8 weekday){

    return weekday;

}

uint8 decodeMonth(uint8 month){

    uint8 tensMask = 0x10;  // 0001 0000 (Table 19, Pg. 22 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 19, Pg. 22 PCF8523 Datasheet)
    
    uint8 tens = (month & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (month & onesMask);

    return tens  + ones;

}
uint8 encodeMonth(uint8 month){

    uint8 tens = month / 10;
    uint8 ones = month - (tens * 10);
    
    return (tens << 4) | ones;

}

uint8 decodeYear(uint8 year){

    uint8 tensMask = 0xF0;  // 1111 0000 (Table 21, Pg. 23 PCF8523 Datasheet)
    uint8 onesMask = 0x0F;  // 0000 1111 (Table 21, Pg. 23 PCF8523 Datasheet)
    
    uint8 tens = (year & tensMask)>> 4;
    tens = tens * 10;
    uint8 ones = (year & onesMask);

    return tens  + ones;
}
uint8 encodeYear(uint8 year){

    uint8 tens = year / 10;
    uint8 ones = year - (tens * 10);
    
    return (tens << 4) | ones;
    
}


/* [] END OF FILE */
