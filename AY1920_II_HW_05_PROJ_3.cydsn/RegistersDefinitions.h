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
#ifndef __REGISTER_DEFINITIONS_H
    #define __REGISTER_DEFINITIONS_H
      /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /**
    *   \brief Address of the Status register
    */
    #define LIS3DH_STATUS_REG 0x27

    /**
    *   \brief Address of the Control register 1 
    */
    #define LIS3DH_CTRL_REG1 0x20

    //ctrl register value for high resolution mode
    #define LIS3DH_HIGH_RESOLUTION_MODE_CTRL_REG1 0x57

    /**
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23
    
    //Value of the ctrl register 4 for high resolution mode with +-4g FSR (BDU active)
    #define LIS3DH_HIGH_RESOLUTION_MODE_CTRL_REG4 0x98
    
    /*Despite there is no need to define every accelerometer output's register, I preferred to 
      define them just for information*/
    
    //Output x-axis registers
    #define LIS3DH_OUT_X_L 0x28
    #define LIS3DH_OUT_X_H 0x29
    //Output y-axis registers
    #define LIS3DH_OUT_Y_L 0x2A
    #define LIS3DH_OUT_Y_H 0x2B
    //Output z-axis registers
    #define LIS3DH_OUT_Z_L 0x2C
    #define LIS3DH_OUT_Z_H 0x2D
    
#endif
/* [] END OF FILE */
