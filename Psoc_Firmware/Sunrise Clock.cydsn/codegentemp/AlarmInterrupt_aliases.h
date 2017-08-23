/*******************************************************************************
* File Name: AlarmInterrupt.h  
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

#if !defined(CY_PINS_AlarmInterrupt_ALIASES_H) /* Pins AlarmInterrupt_ALIASES_H */
#define CY_PINS_AlarmInterrupt_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AlarmInterrupt_0			(AlarmInterrupt__0__PC)
#define AlarmInterrupt_0_PS		(AlarmInterrupt__0__PS)
#define AlarmInterrupt_0_PC		(AlarmInterrupt__0__PC)
#define AlarmInterrupt_0_DR		(AlarmInterrupt__0__DR)
#define AlarmInterrupt_0_SHIFT	(AlarmInterrupt__0__SHIFT)
#define AlarmInterrupt_0_INTR	((uint16)((uint16)0x0003u << (AlarmInterrupt__0__SHIFT*2u)))

#define AlarmInterrupt_INTR_ALL	 ((uint16)(AlarmInterrupt_0_INTR))


#endif /* End Pins AlarmInterrupt_ALIASES_H */


/* [] END OF FILE */
