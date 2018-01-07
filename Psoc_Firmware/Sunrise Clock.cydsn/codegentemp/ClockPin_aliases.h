/*******************************************************************************
* File Name: ClockPin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ClockPin_ALIASES_H) /* Pins ClockPin_ALIASES_H */
#define CY_PINS_ClockPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ClockPin_0			(ClockPin__0__PC)
#define ClockPin_0_PS		(ClockPin__0__PS)
#define ClockPin_0_PC		(ClockPin__0__PC)
#define ClockPin_0_DR		(ClockPin__0__DR)
#define ClockPin_0_SHIFT	(ClockPin__0__SHIFT)
#define ClockPin_0_INTR	((uint16)((uint16)0x0003u << (ClockPin__0__SHIFT*2u)))

#define ClockPin_INTR_ALL	 ((uint16)(ClockPin_0_INTR))


#endif /* End Pins ClockPin_ALIASES_H */


/* [] END OF FILE */
