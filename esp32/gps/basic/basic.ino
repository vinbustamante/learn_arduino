/**
 * Rob 5/16/2019
 * Github: Rob4226
 * 
 * Basic code using U-blox based GPS module via UART 
 * using HardwareSerial and NeoGPS Arudino library to 
 * parse various NMEA sentences with ESP32 or other boards.
 * 
 * */

#include <Arduino.h>
#include <NMEAGPS.h>

#define RXD2 16
#define TXD2 17

//-------------------------------------------------------------------------
// Check that the config files are set up properly
#if !defined(NMEAGPS_PARSE_RMC) & \
    !defined(NMEAGPS_PARSE_GGA) & \
    !defined(NMEAGPS_PARSE_GLL)
#error You must uncomment at least one of NMEAGPS_PARSE_RMC, NMEAGPS_PARSE_GGA or NMEAGPS_PARSE_GLL in NMEAGPS_cfg.h!
#endif

#if !defined(GPS_FIX_LOCATION)
#error You must uncomment GPS_FIX_LOCATION in GPSfix_cfg.h!
#endif

#define gpsPort Serial1 //ESP32 pins 16RX, 17TX  UART02
#define GPS_PORT_NAME "ESP32_Serial2"
#define DEBUG_PORT Serial
#define BAUD_GPS 9600
#define BAUD_USB_SERIAL 115200
#define fixLEDPin 2

using namespace NeoGPS;
NMEAGPS gps;

void setup()
{
  Serial.begin(BAUD_USB_SERIAL);
  gpsPort.begin(BAUD_GPS, SERIAL_8N1, RXD2, TXD2);

  pinMode(fixLEDPin, OUTPUT);

  // Wait for USB Serial
  while (!Serial)
  {
    yield();
  }

  // By default, "16E TTL" and other U-blox GPS modules output RMC, VTG, CGA, GSA, GSV, GLL messages once a second (these are standard NMEA messages)
  // Configure the GPS to only output what is needed, like just RMC as is shown below by disabling all other default sentences.
  
  //gpsPort.println(F("$PUBX,40,RMC,0,0,0,0*47")); //RMC ON (Comented out to leave RMC on...uncomment this line to disable RMC)
  //delay(100);
  gpsPort.println(F("$PUBX,40,VTG,0,0,0,0*5E")); //VTG OFF
  delay(100);
  gpsPort.println(F("$PUBX,40,GGA,0,0,0,0*5A")); //GGA OFF
  delay(100);
  gpsPort.println(F("$PUBX,40,GSA,0,0,0,0*4E")); //GSA OFF
  delay(100);
  gpsPort.println(F("$PUBX,40,GSV,0,0,0,0*59")); //GSV OFF
  delay(100);
  gpsPort.println(F("$PUBX,40,GLL,0,0,0,0*5C")); //GLL OFF
  delay(100);
}

void loop()
{  
  while (gps.available(gpsPort)) // basically true every second if 1Hz from GPS, only true when the GPS returns a sentence
  {
    // Serial.print(".");
    gps_fix fix = gps.read(); // save the latest

    // Set the "fix" LED to on or off
    bool gpsWasFixed = fix.valid.status && (fix.status >= gps_fix::STATUS_STD);
    digitalWrite(fixLEDPin, gpsWasFixed);

    // DEBUG_PORT.println(fix.status);
    // Serial.print(fix);

    // When we have a valid location, print the latitude and longitude to the USB Serial terminal
    if (fix.valid.location)
    {
      DEBUG_PORT.println("The fix's location is valid!");
      DEBUG_PORT.print("     Latitude: ");
      DEBUG_PORT.println(fix.latitude());
      DEBUG_PORT.print("     Longitude: ");
      DEBUG_PORT.println(fix.longitude());
    }
    delay(1500);
  } 
}
