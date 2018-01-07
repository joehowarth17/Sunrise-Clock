/*******************************************************************************
* File Name: SelectPin.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SelectPin.h"

static SelectPin_BACKUP_STRUCT  SelectPin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SelectPin_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet SelectPin_SUT.c usage_SelectPin_Sleep_Wakeup
*******************************************************************************/
void SelectPin_Sleep(void)
{
    #if defined(SelectPin__PC)
        SelectPin_backup.pcState = SelectPin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SelectPin_backup.usbState = SelectPin_CR1_REG;
            SelectPin_USB_POWER_REG |= SelectPin_USBIO_ENTER_SLEEP;
            SelectPin_CR1_REG &= SelectPin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SelectPin__SIO)
        SelectPin_backup.sioState = SelectPin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SelectPin_SIO_REG &= (uint32)(~SelectPin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SelectPin_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to SelectPin_Sleep() for an example usage.
*******************************************************************************/
void SelectPin_Wakeup(void)
{
    #if defined(SelectPin__PC)
        SelectPin_PC = SelectPin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SelectPin_USB_POWER_REG &= SelectPin_USBIO_EXIT_SLEEP_PH1;
            SelectPin_CR1_REG = SelectPin_backup.usbState;
            SelectPin_USB_POWER_REG &= SelectPin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SelectPin__SIO)
        SelectPin_SIO_REG = SelectPin_backup.sioState;
    #endif
}


/* [] END OF FILE */
