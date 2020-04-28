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
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    #include "cytypes.h"
    #include "stdio.h"
    #include "I2C_Interface.h"
    #include "RegistersDefinitions.h"
    
    #define BYTE_TO_SEND 6
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND + 1
    
    //mask to check if new data is available
    #define LIS3DH_STATUS_REGISTER_MASK 0x08
    
    ErrorCode error;
    uint8_t status_register; 
    
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE];
    
    volatile uint8_t FlagPacketReady;

    CY_ISR_PROTO(CUSTOM_ISR_TIMER);
 
#endif
/* [] END OF FILE */
