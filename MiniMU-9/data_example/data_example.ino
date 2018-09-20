/*  Written by Thomas Upfold while mucking around on his thesis
 *  go to https://www.pololu.com/product/2738 for more information regarding the sensor.
 *  A lot of this is nicked from https://github.com/pololu/minimu-9-ahrs-arduino/blob/master/MinIMU9AHRS/I2C.ino
 *  
 */

#include <LSM6.h>
#include <LIS3MDL.h>
#include <Wire.h>

LSM6 gyro_acc;
LIS3MDL mag;

void setup() {
  //I2C init
  Wire.begin();
  
  //Accelerometer init
  gyro_acc.init();
  gyro_acc.enableDefault();
  gyro_acc.writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale
  
  //Compass init
  mag.init();
  mag.enableDefault();
  
  //Gyro init
  gyro_acc.writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale
  
  //Serial init
  Serial.begin(9600);
}

void loop() {
  gyro_acc.read();
  mag.read();
  //See sensor orientation for x/y/z directions
  //Accel
  //NOTE: values are bitshift so that 1g = 256, just going from example program
  //NOTE: adjust your offset values based on measurements on a level surface.
  const int AX_OFFSET = 0;
  const int AY_OFFSET = 3;
  const int AZ_OFFSET = 47;
  Serial.print("Accel x,y,z =\t");
  Serial.print((gyro_acc.a.x>>4) - AX_OFFSET);
  Serial.print('\t');
  Serial.print((gyro_acc.a.y>>4) - AY_OFFSET);
  Serial.print('\t');
  Serial.print((gyro_acc.a.z>>4) - AZ_OFFSET);
  //gyro values
  const int GX_OFFSET = 44;
  const int GY_OFFSET = -88;
  const int GZ_OFFSET = -60;
   Serial.print("\tGyro x,y,z =\t");
  Serial.print(gyro_acc.g.x - GX_OFFSET);
  Serial.print('\t');
  Serial.print(gyro_acc.g.y - GY_OFFSET);
  Serial.print('\t');
  Serial.println(gyro_acc.g.z - GZ_OFFSET);
  
  delay(200);
}
