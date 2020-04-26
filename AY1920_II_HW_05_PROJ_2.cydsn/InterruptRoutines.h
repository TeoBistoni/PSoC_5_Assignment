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
    
        /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /**
    *   \brief Address of the WHO AM I register
    */
    #define LIS3DH_WHO_AM_I_REG_ADDR 0x0F

    /**
    *   \brief Address of the Status register
    */
    #define LIS3DH_STATUS_REG 0x27

    /**
    *   \brief Address of the Control register 1
    */
    #define LIS3DH_CTRL_REG1 0x20

    /**
    *   \brief Hex value to set normal mode to the accelerator
    */
    #define LIS3DH_NORMAL_MODE_CTRL_REG1 0x57

    /**
    *   \brief  Address of the Temperature Sensor Configuration register
    */
    #define LIS3DH_TEMP_CFG_REG 0x1F

    #define LIS3DH_TEMP_CFG_REG_ACTIVE 0xC0

    /**
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23

    #define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x80

    #define LIS3DH_NORMAL_MODE_CTRL_REG4 0x00

    /**
    *   \brief Address of the ADC output LSB register
    */
    #define LIS3DH_OUT_ADC_3L 0x0C

    /**
    *   \brief Address of the ADC output MSB register
    */
    #define LIS3DH_OUT_ADC_3H 0x0D

    #define LIS3DH_OUT_X_L 0x28
    #define LIS3DH_OUT_X_H 0x29
    #define LIS3DH_OUT_Y_L 0x2A
    #define LIS3DH_OUT_Y_H 0x2B
    #define LIS3DH_OUT_Z_L 0x2C
    #define LIS3DH_OUT_Z_H 0x2D
    
    #define BYTE_TO_SEND 6
    #define TRANSMIT_BUFFER_SIZE 1 + BYTE_TO_SEND + 1
    
    ErrorCode error;
    uint8_t status_register; 
    int16_t Accelerometer_x;
    int16_t Accelerometer_y;
    int16_t Accelerometer_z;
    uint8_t Acc_xData[2];
    uint8_t Acc_yData[2];
    uint8_t Acc_zData[2];
    
    uint8_t OutArray[TRANSMIT_BUFFER_SIZE]; 
    volatile uint8_t FlagPacketReady;
    
    
    
    CY_ISR_PROTO(CUSTOM_ISR_TIMER);
    
    
#endif
/* [] END OF FILE */
