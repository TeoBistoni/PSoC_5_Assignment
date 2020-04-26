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
#include "InterruptRoutines.h"
#include "project.h"

CY_ISR(CUSTOM_ISR_TIMER){
        Timer_ReadStatusRegister();
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
        
        
        if(error == NO_ERROR){
            if((status_register & 0b00001000) > 0){
                //READ 3 AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_X_L,
                                                    2,
                                                    &Acc_xData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_x = (int16)((Acc_xData[0] | (Acc_xData[1]<<8)))>>6;
                    OutArray[1] = (uint8_t)(Accelerometer_x*4 & 0xFF);
                    OutArray[2] = (uint8_t)(Accelerometer_x*4 >> 8);
                 }
                
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Y_L,
                                                    2,
                                                    &Acc_yData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_y = (int16)((Acc_yData[0] | (Acc_yData[1]<<8)))>>6;
                    OutArray[3] = (uint8_t)(Accelerometer_y*4 & 0xFF);
                    OutArray[4] = (uint8_t)(Accelerometer_y*4 >> 8);
                }
                
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Z_L,
                                                    2,
                                                    &Acc_zData[0]);
                if(error == NO_ERROR){
                    Accelerometer_z = (int16)((Acc_zData[0] | (Acc_zData[1]<<8)))>>6;
                    OutArray[5] = (uint8_t)(Accelerometer_z*4 & 0xFF);
                    OutArray[6] = (uint8_t)(Accelerometer_z*4 >> 8);
                }
            }
        }
        FlagPacketReady = 1;
}
/* [] END OF FILE */
