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
    
    #define BYTE_TO_SEND 12
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND + 1
        
    //parameters for the Scaler function (to turn values from digit to m/(s^2))
    //max and min digit
    #define OLD_MAX 2048 
    #define OLD_MIN -2048
    //max and min g
    #define NEW_MAX 4
    #define NEW_MIN -4
    //gravity constant
    #define G_CONSTANT 9.81
    
    ErrorCode error;
    
    uint8_t status_register; 
    
    //MSB and LSB of the outputs
    uint8_t Acc_xData[2];
    uint8_t Acc_yData[2];
    uint8_t Acc_zData[2];
    
    //These variables represent the value of the output in digits
    int16_t Accelerometer_x;
    int16_t Accelerometer_y;
    int16_t Accelerometer_z;
    
    //These represent the value of the output in m/(s^2)
    int32 x_acceleration;
    int32 y_acceleration;
    int32 z_acceleration;
    
    //Packet which will be transmitted to the Bridge Control Panel
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE]; 
    
    volatile uint8_t FlagPacketReady;
    
    CY_ISR_PROTO(CUSTOM_ISR_TIMER);
    
#endif
/* [] END OF FILE */
