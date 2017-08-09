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
#ifndef RTC_H
#define RTC_H
    
/***************************INCLUDES*******************************************/
#include <project.h>
#include <TimeFunctions.h>
#include <i2cClock.h>
    
/***************************MACROS*********************************************/

    
// Registers: Table 6 -> Pg. 7 and 8 -> PCF8523 Datasheet  
#define CONTROL_REG_1           (0x00)
#define CONTROL_REG_2           (0x01)
#define CONTROL_REG_3           (0x02)
    
#define SECONDS_REG             (0x03)
#define MINUTES_REG             (0x04)
#define HOURS_REG               (0x05)
#define DAYS_REG                (0x06)
#define WEEKDAY_REG             (0x07)
#define MONTH_REG               (0x08)
#define YEAR_REG                (0x09)
    
#define ALARM_MIN_REG           (0x0A)
#define ALARM_HOUR_REG          (0x0B)
#define ALARM_DAY_REG           (0x0C)
#define ALARM_WKDAY_REG         (0x0D)

#define OFFSET_REG              (0x0E)

#define TMR_CLCKOUT_REG         (0x0F)
#define TMR_A_FREQ__CTRL_REG    (0x10)
#define TMR_A_REG               (0x11)
#define TMR_B_FREQ_CTRL_REG     (0x12)
#define TMR_B_REG               (0x13)
    
// Modes
#define HOURMODE_12              (0x08) // Table 7, pg.9     (0000 1000) 
#define HOURMODE_24              (0xF7) // Table 7, pg.9     (1111 0111)
    
#define EVERYTHING_DISABLED      (0xE0) // Table 11, pg.15   battery switch over and low batery detection disabled
#define EVERYTHING_ENABLED       (0x00) // Table 11, pg.15   battery switch over and low battery detection enabled
#define LOW_BATT_DISABLED        (0x80) // Table 11, pg.15   battery switch over enabled, low battery detection disabled.
    
//values
#define RESET_VALUE             (0x58)// Section 8.3 pg.12

    
/***************************STRUCTURES*****************************************/
    struct time{

    uint8 second;
    uint8 minute; 
    uint8 hour;
    uint8 day;
    uint8 weekday;
    uint8 month;
    uint8 year;

};
    
    
/***************************FUNCTION DECLARATIONS******************************/

void changeHourMode(uint8 mode);
void changePowerMode(uint8 mode);

void setSec(uint8 sec);
void setMin(uint8 minutes);
void setHours(uint8 hour);
void setDay(uint8 day);
void setWkDay(uint8 wkday);
void setMonth(uint8 month);
void setYear(uint8 year);

uint8 getSec();
uint8 getMin();
uint8 getHours();
uint8 getDay();
uint8 getWkDay();
uint8 getMonth();
uint8 getYear();

void getTime(struct time *currentTime);
void setTime(struct time *currentTime);
void createAlarm(struct time *alarm, uint8 weekDay, uint8 hour, uint8 minute);
void createAlarmTEST(struct time *alarm,uint8 minute, uint8 second);
char checkAlarm(struct time *time1, struct time *time2);
void softReset();




    
#endif
    
/* [] END OF FILE */
