/*******************************************************************************
* File Name: CalibrateInterrupt.c  
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
#include "CalibrateInterrupt.h"

static CalibrateInterrupt_BACKUP_STRUCT  CalibrateInterrupt_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CalibrateInterrupt_Sleep
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
*  \snippet CalibrateInterrupt_SUT.c usage_CalibrateInterrupt_Sleep_Wakeup
*******************************************************************************/
void CalibrateInterrupt_Sleep(void)
{
    #if defined(CalibrateInterrupt__PC)
        CalibrateInterrupt_backup.pcState = CalibrateInterrupt_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CalibrateInterrupt_backup.usbState = CalibrateInterrupt_CR1_REG;
            CalibrateInterrupt_USB_POWER_REG |= CalibrateInterrupt_USBIO_ENTER_SLEEP;
            CalibrateInterrupt_CR1_REG &= CalibrateInterrupt_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CalibrateInterrupt__SIO)
        CalibrateInterrupt_backup.sioState = CalibrateInterrupt_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CalibrateInterrupt_SIO_REG &= (uint32)(~CalibrateInterrupt_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CalibrateInterrupt_Wakeup
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
*  Refer to CalibrateInterrupt_Sleep() for an example usage.
*******************************************************************************/
void CalibrateInterrupt_Wakeup(void)
{
    #if defined(CalibrateInterrupt__PC)
        CalibrateInterrupt_PC = CalibrateInterrupt_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CalibrateInterrupt_USB_POWER_REG &= CalibrateInterrupt_USBIO_EXIT_SLEEP_PH1;
            CalibrateInterrupt_CR1_REG = CalibrateInterrupt_backup.usbState;
            CalibrateInterrupt_USB_POWER_REG &= CalibrateInterrupt_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CalibrateInterrupt__SIO)
        CalibrateInterrupt_SIO_REG = CalibrateInterrupt_backup.sioState;
    #endif
}


/* [] END OF FILE */
