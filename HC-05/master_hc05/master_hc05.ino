//Master Unit

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int state = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter LED command (On 1, Off 0):");
  mySerial.begin(38400);
}

void loop() {
  //getting info
  if (mySerial.available()) {
    Serial.print("Got back:");
    Serial.print(mySerial.read());
  }
  //Sending info
  if (Serial.available()) {
    char info = Serial.read();
    Serial.print("sent ");
    Serial.println(info); 
    mySerial.write(info);
  }

}
