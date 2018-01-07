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
#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

/***************************INCLUDES*******************************************/
#include <project.h>

/***************************MACROS*********************************************/
   
#define SUNDAY          (0x00)
#define MONDAY          (0x01)
#define TUESDAY         (0x02)
#define WEDNESDAY       (0x03)
#define THURSDAY        (0x04)
#define FRIDAY          (0x05)
#define SATURDAY        (0x06)

#define JANUARY         (0x01)
#define FEBRUAURY       (0x02)
#define MARCH           (0x03)
#define APRIL           (0x04)
#define MAY             (0x05)
#define JUNE            (0x06)
#define JULY            (0x07)
#define AUGUST          (0x08)
#define SEPTEMBER       (0x09)
#define OCTOBER         (0x0A)
#define NOVEMBER        (0x0B)
#define DECEMBER        (0x0C)
/***************************FUNCTION DECLARATIONS******************************/
uint8 decodeSec(uint8 seconds);
uint8 decodeMin(uint8 minutes);
uint8 decodeHours12(uint8 hours);
uint8 decodeHours24(uint8 hours);
uint8 decodeDays(uint8 days);
uint8 decodeWeekDay(uint8 weekday);
uint8 decodeMonth(uint8 month);
uint8 decodeYear(uint8 year);

uint8 encodeSec(uint8 seconds);
uint8 encodeMin(uint8 minutes);
uint8 encodeHours24(uint8 hours);
uint8 encodeDays(uint8 days);
uint8 encodeWeekDay(uint8 weekday);
uint8 encodeMonth(uint8 month);
uint8 encodeYear(uint8 year);

#endif
/* [] END OF FILE */
