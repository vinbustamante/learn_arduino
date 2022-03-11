#include <NMEAGPS.h>

#define gpsPort Serial1
#define RXD2 16
#define TXD2 17
#define GPS_BAUD_RATE 9600

static NMEAGPS   gps;
static const int led = 2;

void setup()
{
  gpsPort.begin(GPS_BAUD_RATE, SERIAL_8N1, RXD2, TXD2);
  pinMode(led, OUTPUT);
}

void loop()
{
  if (gps.available( gpsPort)) {
    gps.read();
    digitalWrite( led, !digitalRead(led) );
  }
}