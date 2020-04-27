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
    
    ErrorCode error;
    uint8_t status_register; 
        
    //MSB and LSB of the outputs
    uint8_t Acc_xData[2];
    uint8_t Acc_yData[2];
    uint8_t Acc_zData[2];
    
    //values of the 3-axis output in digits
    int16_t Accelerometer_x;
    int16_t Accelerometer_y;
    int16_t Accelerometer_z;
    
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE];
    
    volatile uint8_t FlagPacketReady;

    CY_ISR_PROTO(CUSTOM_ISR_TIMER);
 
#endif
/* [] END OF FILE */
