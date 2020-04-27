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

/*the Scaler function returns a 32-bit integer because 16 bit are not sufficient to
  cast a floating point to an integer keeping 3 or more decimals*/
int32 Scaler(int min, int max, float a, float b, int x);

CY_ISR(CUSTOM_ISR_TIMER){
        Timer_ReadStatusRegister();
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
        
        if(error == NO_ERROR){
            if((status_register & 0b00001000) > 0){ //check  if new data is available
                
                //READ X-AXIS VALUE
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_X_L,
                                                    2,
                                                    &Acc_xData[0]);
                if(error == NO_ERROR){ 
                    //In high resolution mode the data output is a 12-bit value
                    Accelerometer_x = (int16)((Acc_xData[0] | (Acc_xData[1]<<8)))>>4;
                    x_acceleration = Scaler(OLD_MAX, OLD_MIN, NEW_MAX*G_CONSTANT, NEW_MIN*G_CONSTANT, Accelerometer_x);
                    
                    OutArray[1] = x_acceleration & 0xFF;//LSB
                    OutArray[2] = (x_acceleration >> 8) & 0xFF;
                    OutArray[3] = (x_acceleration >> 16)&0xFF;
                    OutArray[4] = x_acceleration >> 24; //MSB
                    
                 }else{
                    UART_Debug_PutString("Error occurred during I2C comm to read OUT_X_L and OUT_X_H registers\r\n");   
                 }
                
                //READ Y-AXIS VALUE
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Y_L,
                                                    2,
                                                    &Acc_yData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_y = (int16)((Acc_yData[0] | (Acc_yData[1]<<8)))>>4;
                    y_acceleration = Scaler(OLD_MAX, OLD_MIN, NEW_MAX*G_CONSTANT, NEW_MIN*G_CONSTANT, Accelerometer_y);
                    
                    OutArray[5] = y_acceleration & 0xFF;//LSB
                    OutArray[6] = (y_acceleration >> 8) & 0xFF;
                    OutArray[7] = (y_acceleration >> 16)&0xFF;
                    OutArray[8] = y_acceleration >> 24;//MSB
                    
                }else{
                    UART_Debug_PutString("Error occurred during I2C comm to read OUT_Y_L and OUT_Y_H registers\r\n");   
                 }
                
                //READ Z-AXIS VALUE
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Z_L,
                                                    2,
                                                    &Acc_zData[0]);
                if(error == NO_ERROR){
                    Accelerometer_z = (int16)((Acc_zData[0] | (Acc_zData[1]<<8)))>>4;
                    z_acceleration = Scaler(OLD_MAX, OLD_MIN, NEW_MAX*G_CONSTANT, NEW_MIN*G_CONSTANT, Accelerometer_z);

                    OutArray[9] = z_acceleration & 0xFF;//LSB
                    OutArray[10] = (z_acceleration >> 8) & 0xFF;
                    OutArray[11] = (z_acceleration >> 16)&0xFF;
                    OutArray[12] = z_acceleration >> 24;//MSB
                    
                    FlagPacketReady = 1;//the packet is ready to be sent
                    
                }else{
                    UART_Debug_PutString("Error occurred during I2C comm to read OUT_Z_L and OUT_Z_H registers\r\n");   
                 }
            }
        }else{
            UART_Debug_PutString("Error occurred during I2C comm to read control register\r\n");   
        }
}

int32 Scaler(int max, int min, float b, float a, int x){
    //scaling the values from digit to m/(s^2) and multiplying by 10000 to keep 4 decimal.
    return ((((x-min)*(b-a))/(max-min))+a)*10000;
}

/* [] END OF FILE */