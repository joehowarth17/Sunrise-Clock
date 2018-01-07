/*******************************************************************************
* File Name: CalibrateInterrupt.h  
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

#if !defined(CY_PINS_CalibrateInterrupt_ALIASES_H) /* Pins CalibrateInterrupt_ALIASES_H */
#define CY_PINS_CalibrateInterrupt_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CalibrateInterrupt_0			(CalibrateInterrupt__0__PC)
#define CalibrateInterrupt_0_PS		(CalibrateInterrupt__0__PS)
#define CalibrateInterrupt_0_PC		(CalibrateInterrupt__0__PC)
#define CalibrateInterrupt_0_DR		(CalibrateInterrupt__0__DR)
#define CalibrateInterrupt_0_SHIFT	(CalibrateInterrupt__0__SHIFT)
#define CalibrateInterrupt_0_INTR	((uint16)((uint16)0x0003u << (CalibrateInterrupt__0__SHIFT*2u)))

#define CalibrateInterrupt_INTR_ALL	 ((uint16)(CalibrateInterrupt_0_INTR))


#endif /* End Pins CalibrateInterrupt_ALIASES_H */


/* [] END OF FILE */
