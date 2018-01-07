/*******************************************************************************
* File Name: SelectPin.h  
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

#if !defined(CY_PINS_SelectPin_H) /* Pins SelectPin_H */
#define CY_PINS_SelectPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SelectPin_aliases.h"


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
} SelectPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SelectPin_Read(void);
void    SelectPin_Write(uint8 value);
uint8   SelectPin_ReadDataReg(void);
#if defined(SelectPin__PC) || (CY_PSOC4_4200L) 
    void    SelectPin_SetDriveMode(uint8 mode);
#endif
void    SelectPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   SelectPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SelectPin_Sleep(void); 
void SelectPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SelectPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SelectPin_DRIVE_MODE_BITS        (3)
    #define SelectPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SelectPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SelectPin_SetDriveMode() function.
         *  @{
         */
        #define SelectPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SelectPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SelectPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SelectPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SelectPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SelectPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SelectPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SelectPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SelectPin_MASK               SelectPin__MASK
#define SelectPin_SHIFT              SelectPin__SHIFT
#define SelectPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SelectPin_SetInterruptMode() function.
     *  @{
     */
        #define SelectPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SelectPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SelectPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SelectPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SelectPin__SIO)
    #define SelectPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SelectPin__PC) && (CY_PSOC4_4200L)
    #define SelectPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SelectPin_USBIO_DISABLE              ((uint32)(~SelectPin_USBIO_ENABLE))
    #define SelectPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SelectPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SelectPin_USBIO_ENTER_SLEEP          ((uint32)((1u << SelectPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SelectPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SelectPin_USBIO_SUSPEND_SHIFT)))
    #define SelectPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SelectPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define SelectPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SelectPin__PC)
    /* Port Configuration */
    #define SelectPin_PC                 (* (reg32 *) SelectPin__PC)
#endif
/* Pin State */
#define SelectPin_PS                     (* (reg32 *) SelectPin__PS)
/* Data Register */
#define SelectPin_DR                     (* (reg32 *) SelectPin__DR)
/* Input Buffer Disable Override */
#define SelectPin_INP_DIS                (* (reg32 *) SelectPin__PC2)

/* Interrupt configuration Registers */
#define SelectPin_INTCFG                 (* (reg32 *) SelectPin__INTCFG)
#define SelectPin_INTSTAT                (* (reg32 *) SelectPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SelectPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SelectPin__SIO)
    #define SelectPin_SIO_REG            (* (reg32 *) SelectPin__SIO)
#endif /* (SelectPin__SIO_CFG) */

/* USBIO registers */
#if !defined(SelectPin__PC) && (CY_PSOC4_4200L)
    #define SelectPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SelectPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SelectPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SelectPin_DRIVE_MODE_SHIFT       (0x00u)
#define SelectPin_DRIVE_MODE_MASK        (0x07u << SelectPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SelectPin_H */


/* [] END OF FILE */
