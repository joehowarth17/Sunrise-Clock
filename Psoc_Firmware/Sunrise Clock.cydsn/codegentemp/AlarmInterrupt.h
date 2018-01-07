/*******************************************************************************
* File Name: AlarmInterrupt.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_AlarmInterrupt_H) /* Pins AlarmInterrupt_H */
#define CY_PINS_AlarmInterrupt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AlarmInterrupt_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} AlarmInterrupt_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   AlarmInterrupt_Read(void);
void    AlarmInterrupt_Write(uint8 value);
uint8   AlarmInterrupt_ReadDataReg(void);
#if defined(AlarmInterrupt__PC) || (CY_PSOC4_4200L) 
    void    AlarmInterrupt_SetDriveMode(uint8 mode);
#endif
void    AlarmInterrupt_SetInterruptMode(uint16 position, uint16 mode);
uint8   AlarmInterrupt_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void AlarmInterrupt_Sleep(void); 
void AlarmInterrupt_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(AlarmInterrupt__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define AlarmInterrupt_DRIVE_MODE_BITS        (3)
    #define AlarmInterrupt_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AlarmInterrupt_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the AlarmInterrupt_SetDriveMode() function.
         *  @{
         */
        #define AlarmInterrupt_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define AlarmInterrupt_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define AlarmInterrupt_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define AlarmInterrupt_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define AlarmInterrupt_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define AlarmInterrupt_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define AlarmInterrupt_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define AlarmInterrupt_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define AlarmInterrupt_MASK               AlarmInterrupt__MASK
#define AlarmInterrupt_SHIFT              AlarmInterrupt__SHIFT
#define AlarmInterrupt_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AlarmInterrupt_SetInterruptMode() function.
     *  @{
     */
        #define AlarmInterrupt_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define AlarmInterrupt_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define AlarmInterrupt_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define AlarmInterrupt_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(AlarmInterrupt__SIO)
    #define AlarmInterrupt_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(AlarmInterrupt__PC) && (CY_PSOC4_4200L)
    #define AlarmInterrupt_USBIO_ENABLE               ((uint32)0x80000000u)
    #define AlarmInterrupt_USBIO_DISABLE              ((uint32)(~AlarmInterrupt_USBIO_ENABLE))
    #define AlarmInterrupt_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define AlarmInterrupt_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define AlarmInterrupt_USBIO_ENTER_SLEEP          ((uint32)((1u << AlarmInterrupt_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << AlarmInterrupt_USBIO_SUSPEND_DEL_SHIFT)))
    #define AlarmInterrupt_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << AlarmInterrupt_USBIO_SUSPEND_SHIFT)))
    #define AlarmInterrupt_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << AlarmInterrupt_USBIO_SUSPEND_DEL_SHIFT)))
    #define AlarmInterrupt_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(AlarmInterrupt__PC)
    /* Port Configuration */
    #define AlarmInterrupt_PC                 (* (reg32 *) AlarmInterrupt__PC)
#endif
/* Pin State */
#define AlarmInterrupt_PS                     (* (reg32 *) AlarmInterrupt__PS)
/* Data Register */
#define AlarmInterrupt_DR                     (* (reg32 *) AlarmInterrupt__DR)
/* Input Buffer Disable Override */
#define AlarmInterrupt_INP_DIS                (* (reg32 *) AlarmInterrupt__PC2)

/* Interrupt configuration Registers */
#define AlarmInterrupt_INTCFG                 (* (reg32 *) AlarmInterrupt__INTCFG)
#define AlarmInterrupt_INTSTAT                (* (reg32 *) AlarmInterrupt__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define AlarmInterrupt_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(AlarmInterrupt__SIO)
    #define AlarmInterrupt_SIO_REG            (* (reg32 *) AlarmInterrupt__SIO)
#endif /* (AlarmInterrupt__SIO_CFG) */

/* USBIO registers */
#if !defined(AlarmInterrupt__PC) && (CY_PSOC4_4200L)
    #define AlarmInterrupt_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define AlarmInterrupt_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define AlarmInterrupt_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define AlarmInterrupt_DRIVE_MODE_SHIFT       (0x00u)
#define AlarmInterrupt_DRIVE_MODE_MASK        (0x07u << AlarmInterrupt_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins AlarmInterrupt_H */


/* [] END OF FILE */
