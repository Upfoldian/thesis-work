//Master Unit

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
char state = 0;
int LED = 12;
void setup() {
  Serial.begin(9600);
  Serial.println("Getting commands:");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  mySerial.begin(38400);
}

void loop() {

  if (mySerial.available()) {
    state = mySerial.read();
    Serial.print("Got command.");
    Serial.println(state);
    if (state == '1') {
      digitalWrite(LED, HIGH);
    } else if (state == '0') {
      digitalWrite(LED, LOW);
    }
  }
}
