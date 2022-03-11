#include <SoftwareSerial.h>

#define RXD2 16
#define TXD2 17

// SoftwareSerial mySerial(16, 17); //(RX, TX) check correct GPS pin assignments.

void setup() {
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2); //gps baud
  Serial.begin(115200);  //make sure Baud rate is correct
  Serial.println("GPS start");
}

void loop() {
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}