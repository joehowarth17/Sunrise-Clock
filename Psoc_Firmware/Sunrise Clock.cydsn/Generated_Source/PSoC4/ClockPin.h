/*******************************************************************************
* File Name: ClockPin.h  
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

#if !defined(CY_PINS_ClockPin_H) /* Pins ClockPin_H */
#define CY_PINS_ClockPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ClockPin_aliases.h"


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
} ClockPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ClockPin_Read(void);
void    ClockPin_Write(uint8 value);
uint8   ClockPin_ReadDataReg(void);
#if defined(ClockPin__PC) || (CY_PSOC4_4200L) 
    void    ClockPin_SetDriveMode(uint8 mode);
#endif
void    ClockPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   ClockPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ClockPin_Sleep(void); 
void ClockPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ClockPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ClockPin_DRIVE_MODE_BITS        (3)
    #define ClockPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ClockPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ClockPin_SetDriveMode() function.
         *  @{
         */
        #define ClockPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ClockPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ClockPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ClockPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ClockPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ClockPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ClockPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ClockPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ClockPin_MASK               ClockPin__MASK
#define ClockPin_SHIFT              ClockPin__SHIFT
#define ClockPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ClockPin_SetInterruptMode() function.
     *  @{
     */
        #define ClockPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ClockPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ClockPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ClockPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ClockPin__SIO)
    #define ClockPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ClockPin__PC) && (CY_PSOC4_4200L)
    #define ClockPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ClockPin_USBIO_DISABLE              ((uint32)(~ClockPin_USBIO_ENABLE))
    #define ClockPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ClockPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ClockPin_USBIO_ENTER_SLEEP          ((uint32)((1u << ClockPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ClockPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define ClockPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ClockPin_USBIO_SUSPEND_SHIFT)))
    #define ClockPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ClockPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define ClockPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ClockPin__PC)
    /* Port Configuration */
    #define ClockPin_PC                 (* (reg32 *) ClockPin__PC)
#endif
/* Pin State */
#define ClockPin_PS                     (* (reg32 *) ClockPin__PS)
/* Data Register */
#define ClockPin_DR                     (* (reg32 *) ClockPin__DR)
/* Input Buffer Disable Override */
#define ClockPin_INP_DIS                (* (reg32 *) ClockPin__PC2)

/* Interrupt configuration Registers */
#define ClockPin_INTCFG                 (* (reg32 *) ClockPin__INTCFG)
#define ClockPin_INTSTAT                (* (reg32 *) ClockPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ClockPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ClockPin__SIO)
    #define ClockPin_SIO_REG            (* (reg32 *) ClockPin__SIO)
#endif /* (ClockPin__SIO_CFG) */

/* USBIO registers */
#if !defined(ClockPin__PC) && (CY_PSOC4_4200L)
    #define ClockPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ClockPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ClockPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ClockPin_DRIVE_MODE_SHIFT       (0x00u)
#define ClockPin_DRIVE_MODE_MASK        (0x07u << ClockPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ClockPin_H */


/* [] END OF FILE */
