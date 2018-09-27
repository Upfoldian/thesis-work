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
  pinMode(7, OUTPUT);
  loraInit();
}

void loop() {

  uint8_t data = 25;
  rf95.send((uint8_t*) &data, sizeof(data));
  rf95.waitPacketSent();

  
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(1000)) { 
    if (rf95.recv(buf, &len)) {
      Serial.println("reply: " + String(buf[0]));
      if (buf[0] == 25) {
        Serial.println("HIGH");
        digitalWrite(7, HIGH);
        buf[0] = 0;
      }
      
    } else {
      Serial.println("recv failed");
    }
  } else {
    digitalWrite(7, LOW);
  }
  delay(300);
}

