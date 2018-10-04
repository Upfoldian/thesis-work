//Sensor libs and variables
#include <LSM6.h>
#include <LIS3MDL.h>
#include <Wire.h>

LSM6 gyro_acc;
LIS3MDL mag;
//adjust these based on sensor orientation
const int16_t AX_OFFSET = 200;
const int16_t AY_OFFSET = -170;
const int16_t AZ_OFFSET = 330;
const int16_t GX_OFFSET = 0;
const int16_t GY_OFFSET = 0;
const int16_t GZ_OFFSET = 0;
const int16_t MX_OFFSET = 0;
const int16_t MY_OFFSET = 0;
const int16_t MZ_OFFSET = 0; 


/* Some important config stuff
 *  Unadjusted values of accelerometer at the default scale of +- 2g
 *  has a conversion factor of 0.061 so raw value * 0.061 / 1000 = value in g
 *  
 *  For gyro, at default +-125, conversion rate is 4.375 millidegrees per second
 *  or raw value * 4.375 / 1000 = value in dps
 *  
 *  For magnetometer/compass at default +- 4 gauss, conversion rate is 1/6842
 *  or raw value / 6842 = value in gauss
 */
const double accelAdjust = 0.061/1000.0;
const double gyroAdjust = 4.375/1000.0;

void sensorInit() {
  //I2C init
  Wire.begin();
  //Accelerometer init
  gyro_acc.init();
  gyro_acc.enableDefault();
  //gyro_acc.writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale
  //Compass init
  mag.init();
  mag.enableDefault();
  //Gyro init
  //gyro_acc.writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale
  for (int i = 4; i < 8; i++) {
    pinMode(i, OUTPUT); 
  }
}

void setup() {
  Serial.begin(9600);
  sensorInit();
}

int incOldest (int current, int size) {
  return (current + 1)%size;
}

void loop() {
  int avgSize = 10;
  int oldest = 0;
  double dataValues[9][avgSize];
  unsigned long currentTime, prevTime = millis();
  while (true) {
    gyro_acc.read();
    mag.read();
    currentTime = millis();
    
    dataValues[0][oldest] = ((gyro_acc.a.x) - AX_OFFSET) * accelAdjust;
    dataValues[1][oldest] = ((gyro_acc.a.y) - AY_OFFSET) * accelAdjust;
    dataValues[2][oldest] = ((gyro_acc.a.z) - AZ_OFFSET) * accelAdjust;
    
    //dataValues[3][oldest] = ((gyro_acc.g.x) - GX_OFFSET);// * gyroAdjust;
    //dataValues[4][oldest] = ((gyro_acc.g.y) - GY_OFFSET);// * gyroAdjust;
    //dataValues[5][oldest] = ((gyro_acc.g.z) - GZ_OFFSET);// * gyroAdjust;
    
    oldest = incOldest(oldest, avgSize);
    
    double totals[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < avgSize; j++) {
         totals[i] += dataValues[i][j];
      }
      totals[i] = totals[i] / avgSize;
    }
    for (int i = 0; i < 3; i++) {
      Serial.print(String(totals[i]) + "\t");
    }
    Serial.print("\n");

    //Integration stuff
    
    
  }
}

