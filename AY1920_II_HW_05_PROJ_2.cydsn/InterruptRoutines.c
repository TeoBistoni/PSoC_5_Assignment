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

//MSB and LSB of the outputs
uint8_t Acc_Data[6];

//values of the 3-axis output in digits
int16_t Accelerometer_x;
int16_t Accelerometer_y;
int16_t Accelerometer_z;

CY_ISR(CUSTOM_ISR_TIMER){
    Timer_ReadStatusRegister();
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                    LIS3DH_STATUS_REG,
                                    &status_register);
    
    
    if(error == NO_ERROR){
        if((status_register & LIS3DH_STATUS_REGISTER_MASK) == LIS3DH_STATUS_REGISTER_MASK){
            
            //READ X/Y/Z-AXIS VALUES
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                LIS3DH_OUT_X_L,
                                                6,
                                                &Acc_Data[0]);
            if(error == NO_ERROR){ 
                
              /*Instead of using a scaler function to convert data from digit to mg, I preferred
                to abide by the datasheet and to use the sensitivity that it specifies (4mg/digit @+-2g FSR,
                FSR in normal mode).
                Moreover, I chose not to cut the values above 500 digits or below -500 digits.
                Therefore the output can result greater than 2000mg or lower than -2000mg. */
                
                //In order to multiply the digit value by 4, It is sufficient to shift it to the right by 4 instead of 6.
                Accelerometer_x = (int16)((Acc_Data[0] | (Acc_Data[1]<<8)))>>4;
                Accelerometer_y = (int16)((Acc_Data[2] | (Acc_Data[3]<<8)))>>4;
                Accelerometer_z = (int16)((Acc_Data[4] | (Acc_Data[5]<<8)))>>4;
                
                OutArray[1] = (uint8_t)(Accelerometer_x & 0xFF); //LSB x-axis output
                OutArray[2] = (uint8_t)(Accelerometer_x >> 8); //MSB x-axis output
                OutArray[3] = (uint8_t)(Accelerometer_y & 0xFF); //LSB y-axis output
                OutArray[4] = (uint8_t)(Accelerometer_y >> 8); //MSB y-axis output
                OutArray[5] = (uint8_t)(Accelerometer_z & 0xFF); //LSB z-axis output
                OutArray[6] = (uint8_t)(Accelerometer_z >> 8); //MSB z-axis output
                
                FlagPacketReady = 1; //Packet ready to be sent to Bridge Control Panel
            }
        }
    }
}
/* [] END OF FILE */
