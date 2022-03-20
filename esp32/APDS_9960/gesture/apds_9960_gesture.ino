/***************************************************************************
  This is a library for the APDS9960 digital proximity, ambient light, RGB, and gesture sensor

  This sketch puts the sensor in gesture mode and decodes gestures.
  To use this, first put your hand close to the sensor to enable gesture mode.
  Then move your hand about 6" from the sensor in the up -> down, down -> up, 
  left -> right, or right -> left direction.

  Designed specifically to work with the Adafruit APDS9960 breakout
  ----> http://www.adafruit.com/products/3595

  These sensors use I2C to communicate. The device's I2C address is 0x39

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_APDS9960.h"
#define LED 2
#define INT_PIN 18
Adafruit_APDS9960 apds;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else {    
    Serial.println("Device initialized!");
    digitalWrite(LED, HIGH);
  }

  //gesture mode will be entered once proximity mode senses something close
  apds.enableProximity(true);
  apds.enableGesture(true);
  apds.setGestureProximityThreshold(1);
  apds.setGestureFIFOThreshold(APDS9960_GFIFO_16);
  apds.setGestureGain(APDS9960_GGAIN_4);
  apds.resetCounts();
}

// the loop function runs over and over again forever
void loop() {
    if (apds.gestureValid()) {
      // apds.clearInterrupt();
      // Serial.println("gesture found");
      uint8_t gesture = apds.readGesture();
      if(gesture == APDS9960_DOWN){
        Serial.println("down");
      } else if(gesture == APDS9960_UP) {
        Serial.println("up");
      } else if(gesture == APDS9960_LEFT) {
        Serial.println("left");      
      } else if(gesture == APDS9960_RIGHT) {
        Serial.println("right");
      } else {
        //
      }
    }
}