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
                
                //READ X-AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_X_L,
                                                    2,
                                                    &Acc_xData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_x = (int16)((Acc_xData[0] | (Acc_xData[1]<<8)))>>6;
                    
                    //digit values multiplied by 4 in order to convert them to mg units
                    OutArray[1] = (uint8_t)(Accelerometer_x*4 & 0xFF); //LSB
                    OutArray[2] = (uint8_t)(Accelerometer_x*4 >> 8); //MSB
                    
                }else{
                   UART_Debug_PutString("Error occurred during I2C comm to read OUT_X_L and OUT_X_H registers\r\n");   
                }
                
                //READ Y-AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Y_L,
                                                    2,
                                                    &Acc_yData[0]);
                if(error == NO_ERROR){ 
                    Accelerometer_y = (int16)((Acc_yData[0] | (Acc_yData[1]<<8)))>>6;
                    
                    //digit values multiplied by 4 in order to convert them to mg units
                    OutArray[3] = (uint8_t)(Accelerometer_y*4 & 0xFF);//LSB
                    OutArray[4] = (uint8_t)(Accelerometer_y*4 >> 8);//MSB
                    
                }else{
                    UART_Debug_PutString("Error occurred during I2C comm to read OUT_Y_L and OUT_Y_H registers\r\n");   
                }
                
                //READ Z-AXIS VALUES
                error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_OUT_Z_L,
                                                    2,
                                                    &Acc_zData[0]);
                if(error == NO_ERROR){
                    Accelerometer_z = (int16)((Acc_zData[0] | (Acc_zData[1]<<8)))>>6;
                    
                    //digit values multiplied by 4 in order to convert them to mg units              
                    OutArray[5] = (uint8_t)(Accelerometer_z*4 & 0xFF);//LSB
                    OutArray[6] = (uint8_t)(Accelerometer_z*4 >> 8);//MSB
                    
                    FlagPacketReady = 1; //Packet ready to be sent to Bridge Control Panel
                    
                }else{
                    UART_Debug_PutString("Error occurred during I2C comm to read OUT_Z_L and OUT_Z_H registers\r\n");   
                }
            }
        }
}
/* [] END OF FILE */
