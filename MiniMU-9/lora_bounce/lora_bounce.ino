//LoRa libs and variables
#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;
float frequency = 868.0;

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
  loraInit();
}

void loop() {
  uint8_t buf[16];
  uint8_t len = sizeof(buf);
  if (rf95.waitAvailableTimeout(3000)) { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len)) {
      uint8_t data = 5; 
      rf95.send((uint8_t*) &data, sizeof(data));
      rf95.waitPacketSent();
    } else {
      Serial.println("recv failed");
    }
  } else {
    Serial.println("No reply, is LoRa server running?");
  }
}

