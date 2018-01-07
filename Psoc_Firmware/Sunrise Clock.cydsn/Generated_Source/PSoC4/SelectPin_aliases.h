/*******************************************************************************
* File Name: SelectPin.h  
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

#if !defined(CY_PINS_SelectPin_ALIASES_H) /* Pins SelectPin_ALIASES_H */
#define CY_PINS_SelectPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SelectPin_0			(SelectPin__0__PC)
#define SelectPin_0_PS		(SelectPin__0__PS)
#define SelectPin_0_PC		(SelectPin__0__PC)
#define SelectPin_0_DR		(SelectPin__0__DR)
#define SelectPin_0_SHIFT	(SelectPin__0__SHIFT)
#define SelectPin_0_INTR	((uint16)((uint16)0x0003u << (SelectPin__0__SHIFT*2u)))

#define SelectPin_INTR_ALL	 ((uint16)(SelectPin_0_INTR))


#endif /* End Pins SelectPin_ALIASES_H */


/* [] END OF FILE */
