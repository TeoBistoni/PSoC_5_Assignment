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

//MSB and LSB of the 3 outputs
uint8_t Acc_Data[6];

//These variables represent the value of the output in digits
int16_t Accelerometer_x;
int16_t Accelerometer_y;
int16_t Accelerometer_z;

//These represent the value of the output in m/(s^2)
int32 x_acceleration;
int32 y_acceleration;
int32 z_acceleration;

/*Instead of using a scaler function to convert data from digit to m/(s^2), I preferred
  to abide by the datasheet and to use the sensitivity that it specifies (1mg/digit @+-2g FSR,
  so 2mg/digit @+-4g FSR in high resolution mode).
  Moreover, I chose not to cut the values above 2000 digits or below -2000 digits.
  Therefore the output can result greater than 4g or lower than -4g. */
float sensitivity = ((2*9.81)/1000)*10000; //multiplying by 10000 in order to keep 4 decimals
 
CY_ISR(CUSTOM_ISR_TIMER){
    Timer_ReadStatusRegister();
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                    LIS3DH_STATUS_REG,
                                    &status_register);
    
    if(error == NO_ERROR){
        if((status_register & LIS3DH_STATUS_REGISTER_MASK) == LIS3DH_STATUS_REGISTER_MASK){ //check  if new data is available
            
            //READ X/Y/Z-AXIS VALUES
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                LIS3DH_OUT_X_L,
                                                6,
                                                &Acc_Data[0]);
            
            if(error == NO_ERROR){ 
                //In high resolution mode the data output is a 12-bit value
                //reconstruction of x-axis value
                Accelerometer_x = (int16)((Acc_Data[0] | (Acc_Data[1]<<8)))>>4;
                //reconstruction of y-axis value
                Accelerometer_y = (int16)((Acc_Data[2] | (Acc_Data[3]<<8)))>>4;
                //reconstruction of z-axis value
                Accelerometer_z = (int16)((Acc_Data[4] | (Acc_Data[5]<<8)))>>4;
                
                //convertion of the output values from digits to m/s^2 and casting the floating point to an int32
                x_acceleration = Accelerometer_x * sensitivity;
                y_acceleration = Accelerometer_y * sensitivity;
                z_acceleration = Accelerometer_z * sensitivity;
                
                //Preparation of the packet
                OutArray[1] = x_acceleration & 0xFF;//LSB x-axis output
                OutArray[2] = (x_acceleration >> 8) & 0xFF;
                OutArray[3] = (x_acceleration >> 16)&0xFF;
                OutArray[4] = x_acceleration >> 24; //MSB x-axis output
                
                OutArray[5] = y_acceleration & 0xFF;//LSB y-axis output
                OutArray[6] = (y_acceleration >> 8) & 0xFF;
                OutArray[7] = (y_acceleration >> 16)&0xFF;
                OutArray[8] = y_acceleration >> 24;//MSB y-axis output
                
                OutArray[9] = z_acceleration & 0xFF;//LSB z-axis output
                OutArray[10] = (z_acceleration >> 8) & 0xFF;
                OutArray[11] = (z_acceleration >> 16)&0xFF;
                OutArray[12] = z_acceleration >> 24;//MSB z-axis output
                
                FlagPacketReady = 1;//the packet is ready to be sent
            }
        }
    }
}

/* [] END OF FILE */