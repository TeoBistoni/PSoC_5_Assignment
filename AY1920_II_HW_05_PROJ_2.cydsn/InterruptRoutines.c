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
int16 Scaler(int min, int max, int a, int b, int x);


CY_ISR(CUSTOM_ISR_TIMER){
        Timer_ReadStatusRegister();
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
        
        
        if(error == NO_ERROR){
            if((status_register & LIS3DH_STATUS_REGISTER_MASK) == LIS3DH_STATUS_REGISTER_MASK){
                
                //READ X-AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_X_L,
                                                    2,
                                                    &Acc_xData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_x = (int16)((Acc_xData[0] | (Acc_xData[1]<<8)))>>6;
                    x_acceleration = Scaler(OLD_MAX, OLD_MIN, NEW_MAX, NEW_MIN, Accelerometer_x);
                    //digit values multiplied by 4 in order to convert them to mg units
                    OutArray[1] = (uint8_t)(x_acceleration & 0xFF); //LSB
                    OutArray[2] = (uint8_t)(x_acceleration >> 8); //MSB
                }
                
                //READ Y-AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Y_L,
                                                    2,
                                                    &Acc_yData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_y = (int16)((Acc_yData[0] | (Acc_yData[1]<<8)))>>6;
                    y_acceleration = Scaler(OLD_MAX, OLD_MIN, NEW_MAX, NEW_MIN, Accelerometer_y);
                    //digit values multiplied by 4 in order to convert them to mg units
                    OutArray[3] = (uint8_t)(y_acceleration & 0xFF); //LSB
                    OutArray[4] = (uint8_t)(y_acceleration >> 8); //MSB
                }
                
                //READ Z-AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Z_L,
                                                    2,
                                                    &Acc_zData[0]);
                if(error == NO_ERROR){
                    Accelerometer_z = (int16)((Acc_zData[0] | (Acc_zData[1]<<8)))>>6;
                    z_acceleration = Scaler(OLD_MAX, OLD_MIN, NEW_MAX, NEW_MIN, Accelerometer_z);
                    //digit values multiplied by 4 in order to convert them to mg units
                    OutArray[5] = (uint8_t)(z_acceleration & 0xFF); //LSB
                    OutArray[6] = (uint8_t)(z_acceleration >> 8); //MSB
                    
                    FlagPacketReady = 1; //Packet ready to be sent to Bridge Control Panel
                    
                }
            }
        }
}
int16 Scaler(int max, int min, int b, int a, int x){
    //scaling the values from digit to m/(s^2) and multiplying by 10000 to keep 4 decimal.
    return ((((x-min)*(b-a))/(max-min))+a);
}
/* [] END OF FILE */
