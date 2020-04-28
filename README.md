# PSoC_5_Assignment

I2C communication between PSoC microcontroller (master) and a LIS3DH accelerometer (slave).

PROJECT 2
In this project the 3-axis accelerometer output's values are converted from digit to mg using a sensitivity
of 4 mg/digit (suggested in the datasheet).
The values are sent to the Bridge Control Panel in order to be plotted. 

PROJECT 3
In this project the 3-axis accelerometer output's values are converted from digit to m/(s^2) using a sensitivity of 2mg/digit.
The floating point variable containing the values in m/(s^2) are multiplied by 10000 and casted into 32-bit integers 
in order to keep 4 decimals. Then, they are sent to the Bridge Control Panel in order to be plotted.




