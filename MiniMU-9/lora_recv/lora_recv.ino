//LoRa libs and variables
#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;
float frequency = 868.0;

//System call lib
#include <Process.h>

void loraInit() {
  rf95.init();
  rf95.setFrequency(frequency); // Setup ISM frequency
  rf95.setTxPower(13); // Setup Power,dBm
  rf95.setSpreadingFactor(7); // Setup Spreading Factor (6 ~ 12)
  rf95.setSignalBandwidth(125000);   // Setup BandWidth, option: 7800,10400,15600,20800,31200,41700,62500,125000,250000,500000
  rf95.setCodingRate4(5);  // Setup Coding Rate:5(4/5),6(4/6),7(4/7),8(4/8) 
}

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  while (!Serial);
  loraInit();
}

void loop() {
  Process p;
  uint8_t buf[18];
  uint8_t len = sizeof(buf);
  if (rf95.waitAvailableTimeout(3000)) { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len)) {
      int16_t* d = (int16_t)buf;
      for (int i = 0; i < 9; i++) {
        Serial.print(d[i]);
        Serial.print('\t');
      }
      Serial.print('\n');
    } else {
      Serial.println("recv failed");
    }
  } else {
    Serial.println("No reply, is LoRa server running?");
  }
}

