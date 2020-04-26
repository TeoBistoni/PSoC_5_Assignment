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

float sensitivity = 8*9.81/4096;
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
                    float_x.x_acceleration = Scaler(-2048,2048,-4*9.81,4*9.81,Accelerometer_x);
                    OutArray[1] = float_x.bytes_x[3];
                    OutArray[2] = float_x.bytes_x[2];
                    OutArray[3] = float_x.bytes_x[1];
                    OutArray[4] = float_x.bytes_x[0];
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
                    float_y.y_acceleration =Scaler(-2048,2048,-4*9.81,4*9.81,Accelerometer_y);
                    OutArray[5] = float_y.bytes_y[3];
                    OutArray[6] = float_y.bytes_y[2];
                    OutArray[7] = float_y.bytes_y[1];
                    OutArray[8] = float_y.bytes_y[0];
                }
                
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Z_L,
                                                    2,
                                                    &Acc_zData[0]);
                if(error == NO_ERROR){
                    Accelerometer_z = (int16)((Acc_zData[0] | (Acc_zData[1]<<8)))>>4;
                    float_z.z_acceleration =Scaler(-2048,2048,-4*9.81,4*9.81,Accelerometer_z);
                    OutArray[9] = float_z.bytes_z[3];
                    OutArray[10] = float_z.bytes_z[2];
                    OutArray[11] = float_z.bytes_z[1];
                    OutArray[12] = float_z.bytes_z[0];
                }
            }
        }
        FlagPacketReady = 1;
}
/* [] END OF FILE */
float Scaler(float min, float max, float a, float b, float x){
    return (float)((((x-min)*(b-a))/(max-min))+a);
}