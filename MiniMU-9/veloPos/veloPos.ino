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
const double accelAdjust = 0.061/1000.0 * 9.81;
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
  int avgSize = 1, count = 0, oldest = 0;
  double dataValues[9][avgSize];
  double prevAvg[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double velo[3] = {0.0, 0.0, 0.0};
  double prevVelo[3] = {0.0, 0.0, 0.0};
  double pos[3] = {0.0, 0.0, 0.0};
  
  unsigned long currentTime, prevTime = millis();
  
  while (true) {
    gyro_acc.read();
    mag.read();
    currentTime = millis();
    // Assign new values
    dataValues[0][oldest] = ((gyro_acc.a.x) - AX_OFFSET) * accelAdjust;
    dataValues[1][oldest] = ((gyro_acc.a.y) - AY_OFFSET) * accelAdjust;
    dataValues[2][oldest] = ((gyro_acc.a.z) - AZ_OFFSET) * accelAdjust;
    
    dataValues[3][oldest] = ((gyro_acc.g.x) - GX_OFFSET);// * gyroAdjust;
    dataValues[4][oldest] = ((gyro_acc.g.y) - GY_OFFSET);// * gyroAdjust;
    dataValues[5][oldest] = ((gyro_acc.g.z) - GZ_OFFSET);// * gyroAdjust;
    
    oldest = incOldest(oldest, avgSize);
    // average out the last 10 values
    double totals[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < avgSize; j++) {
         totals[i] += dataValues[i][j];
      }
      totals[i] = totals[i] / avgSize;
    }
    
    //Integration stuff
    if (count < 10) {
      count++;
    } else {
      double deltaT = (currentTime - prevTime)/1000.0; //converted to seconds

      for (int i = 0; i < 3; i++) {
        prevVelo[i] = velo[i];
      }
      
      velo[0] += (deltaT * (prevAvg[0]-9.81)) + (deltaT * (totals[0] - prevAvg[0])/2.0);
      velo[1] += (deltaT * prevAvg[1]) + (deltaT * (totals[1] - prevAvg[1])/2.0);
      velo[2] += (deltaT * prevAvg[2]) + (deltaT * (totals[2] - prevAvg[2])/2.0);
      
      for (int i = 0; i < 3; i++) {
        pos[i] += (deltaT * prevVelo[i]) + (deltaT * (velo[i] - prevVelo[i])/2.0);
      }
      
      
      Serial.println(String(pos[0]) + "\t" + String(pos[1]) + "\t" + String(pos[2]));
    
      prevTime = currentTime;
      for (int i = 0; i < 3; i++) {
        prevAvg[i] = totals[i];
      }
    }
    delay(10);
  }
}

