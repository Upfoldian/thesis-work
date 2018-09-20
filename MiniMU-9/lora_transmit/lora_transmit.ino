//LoRa libs and variables
#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;
float frequency = 868.0;

//Sensor libs and variables
#include <LSM6.h>
#include <LIS3MDL.h>
#include <Wire.h>

LSM6 gyro_acc;
LIS3MDL mag;
//adjust these based on sensor orientation
const int AX_OFFSET = 0;
const int AY_OFFSET = 0;
const int AZ_OFFSET = 0;
const int GX_OFFSET = 2;
const int GY_OFFSET = -6;
const int GZ_OFFSET = -4;

void sensorInit() {
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
}

void loraInit() {
  rf95.init();
  rf95.setFrequency(frequency); // Setup ISM frequency
  rf95.setTxPower(13); // Setup Power,dBm
  rf95.setSpreadingFactor(7); // Setup Spreading Factor (6 ~ 12)
  rf95.setSignalBandwidth(125000);   // Setup BandWidth, option: 7800,10400,15600,20800,31200,41700,62500,125000,250000,500000
  rf95.setCodingRate4(5);  // Setup Coding Rate:5(4/5),6(4/6),7(4/7),8(4/8) 
}

void setup() {
  Serial.begin(9600);
  sensorInit();
  loraInit();
}

void loop() {
  gyro_acc.read();
  mag.read();
  int16_t dataValues[6];
  dataValues[0] = ((gyro_acc.a.x>>4) - AX_OFFSET);
  dataValues[1] = ((gyro_acc.a.y>>4) - AY_OFFSET);
  dataValues[2] = ((gyro_acc.a.z>>4) - AZ_OFFSET);
  dataValues[3] = ((gyro_acc.g.x>>4) - GX_OFFSET);
  dataValues[4] = ((gyro_acc.g.y>>4) - GY_OFFSET);
  dataValues[5] = ((gyro_acc.g.z>>4) - GZ_OFFSET);

  for (int i = 0; i < sizeof(dataValues)/sizeof(int16_t); i++) {
    Serial.print(dataValues[i]);
    Serial.print('\t');
  }
  
  rf95.send((uint8_t*) dataValues, sizeof(dataValues));
  rf95.waitPacketSent();

  
  Serial.print('\n');
  /* If I need to send back the data in future
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(3000)) { 
    if (rf95.recv(buf, &len)) {
      Serial.print("reply: ");
      Serial.println((char*)buf);
    } else {
      Serial.println("recv failed");
    }
  } else {
    Serial.println("No reply, is LoRa server running?");
  }
  */
  delay(300);
}

