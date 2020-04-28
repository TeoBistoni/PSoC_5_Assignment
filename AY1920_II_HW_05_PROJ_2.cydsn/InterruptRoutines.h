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
    
    //parameters for the Scaler function (to turn values from digit to mg)
    //max and min digit
    #define OLD_MAX 511 
    #define OLD_MIN -512
    //max and min mg
    #define NEW_MAX 2000
    #define NEW_MIN -2000
    
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
    
    int16_t x_acceleration;
    int16_t y_acceleration;
    int16_t z_acceleration;
    
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE];
    
    volatile uint8_t FlagPacketReady;

    CY_ISR_PROTO(CUSTOM_ISR_TIMER);
 
#endif
/* [] END OF FILE */
