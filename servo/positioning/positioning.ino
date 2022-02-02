#include <ESP32Servo.h>

#define POT_PIN 15

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

int oldPosition = 0;

void setup()
{
    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(4, 500, 2400); // attaches the servo on pin 18 to the servo object
	// myservo.attach(4);
}

void loop()
{
	// for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    //     // in steps of 1 degree
    //     myservo.write(pos);
    //     delay(15);
    // }
    // // tell servo to go to position in
    // // waits 15ms for the servo to reach
    // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //     myservo.write(pos);
    //     delay(15);
    // }
    int position = map(analogRead(POT_PIN), 0, 4095, 0, 180);
    if (oldPosition != position) {
        oldPosition = position;
        myservo.write(position);
    }
}
