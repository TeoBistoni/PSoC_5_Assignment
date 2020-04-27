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

float Scaler(float min, float max, float a, float b, float x);

float sensitivity = (8*9.81/4096)*10000;
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
                    Accelerometer_x = (int16)((Acc_xData[0] | (Acc_xData[1]<<8)))>>4;
                    //float_x.x_acceleration =(float) Accelerometer_x * sensitivity;
                    x_acceleration = Accelerometer_x * sensitivity;
                    OutArray[4] = x_acceleration >> 24;
                    OutArray[3] = (x_acceleration >> 16)&0xFF;
                    OutArray[2] = (x_acceleration >> 8) & 0xFF;
                    OutArray[1] = x_acceleration & 0xFF;
                   /* for(i = 0;i<4;i++){
                        sprintf(message,"byte %d is %02x\r\n",i,float_x.bytes[i]);
                        UART_Debug_PutString(message);
                    }*/
                 }
                
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Y_L,
                                                    2,
                                                    &Acc_yData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_y = (int16)((Acc_yData[0] | (Acc_yData[1]<<8)))>>4;
                    y_acceleration = Accelerometer_y * sensitivity;
                    OutArray[8] = y_acceleration >> 24;
                    OutArray[7] = (y_acceleration >> 16)&0xFF;
                    OutArray[6] = (y_acceleration >> 8) & 0xFF;
                    OutArray[5] = y_acceleration & 0xFF;
                }
                
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Z_L,
                                                    2,
                                                    &Acc_zData[0]);
                if(error == NO_ERROR){
                    Accelerometer_z = (int16)((Acc_zData[0] | (Acc_zData[1]<<8)))>>4;
                    z_acceleration = Accelerometer_z * sensitivity;
                    OutArray[12] = z_acceleration >> 24;
                    OutArray[11] = (z_acceleration >> 16)&0xFF;
                    OutArray[10] = (z_acceleration >> 8) & 0xFF;
                    OutArray[9] = z_acceleration & 0xFF;
                }
            }
        }
        FlagPacketReady = 1;
}
/* [] END OF FILE */
float Scaler(float min, float max, float a, float b, float x){
    return (float)((((x-min)*(b-a))/(max-min))+a);
}