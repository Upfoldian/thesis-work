//Sensor libs and variables
#include <LSM6.h>
#include <LIS3MDL.h>
#include <Wire.h>

LSM6 gyro_acc;
LIS3MDL mag;
//adjust these based on sensor orientation
const int16_t AX_OFFSET = 0;
const int16_t AY_OFFSET = 0;
const int16_t AZ_OFFSET = 0;
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

const int N = 5;
const int S = 7;
const int W = 6;
const int E = 4;

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
double getHeadingDeg(double x, double y) {
  double heading = 0;
  if (y > 0) {
    heading = 90.00 - atan(x/y) * (180.0/PI);
  } else if (y < 0) {
    heading = 270 - atan(x/y) * (180.0/PI);
  } else if (y == 0) {
    if (x < 0) {
      heading = 180.0;
    } else {
      heading = 0;
    }
  }
  return heading;
}
String getHeadingStr(double heading) {
  for (int i = 4; i < 8; i++) {
    digitalWrite(i, LOW);
  }
  if (heading >= 22.5 && heading < 67.8 ) {
    digitalWrite(N, HIGH);
    digitalWrite(W, HIGH);
    return "NW";
  } else if (heading >= 67.5 && heading < 112.5) {
    digitalWrite(N, HIGH);
    return "N";
  } else if (heading >= 112.5 && heading < 157.5) {
    digitalWrite(N, HIGH);
    digitalWrite(E, HIGH);
    return "NE";
  } else if (heading >= 157.5 && heading < 202.5) {
    digitalWrite(E, HIGH);
    return "E";
  } else if (heading >= 202.5 && heading < 247.5) {
    digitalWrite(E, HIGH);
    digitalWrite(S, HIGH);
    return "SE";
  } else if (heading >= 247.5 && heading < 292.5) {
    digitalWrite(S, HIGH);
    return "S";
  } else if (heading >= 292.5 && heading < 337.5) {
    digitalWrite(S, HIGH);
    digitalWrite(W, HIGH);
    return "SW";
  } else if (heading >= 337.5 || heading < 22.5) {
    digitalWrite(W, HIGH);
    return "W";
  } else {
    return "?";
  }
}
void loop() {
  gyro_acc.read();
  mag.read();
  int16_t dataValues[9];
  dataValues[0] = ((gyro_acc.a.x) - AX_OFFSET);
  dataValues[1] = ((gyro_acc.a.y) - AY_OFFSET);
  dataValues[2] = ((gyro_acc.a.z) - AZ_OFFSET);
  
  dataValues[3] = ((gyro_acc.g.x) - GX_OFFSET);
  dataValues[4] = ((gyro_acc.g.y) - GY_OFFSET);
  dataValues[5] = ((gyro_acc.g.z) - GZ_OFFSET);

  double magX = ((mag.m.x) - MX_OFFSET);
  double magY = ((mag.m.y) - MY_OFFSET);
  double magZ = ((mag.m.z) - MZ_OFFSET);

  //Math.atan2(sensor.y, sensor.x) * (180 / Math.PI)
  double headingDeg = getHeadingDeg(magY,magZ);
  Serial.println("HeadingDeg: " + String(headingDeg) + "\tHeadingStr: " + getHeadingStr(headingDeg));
  delay(100);
}

