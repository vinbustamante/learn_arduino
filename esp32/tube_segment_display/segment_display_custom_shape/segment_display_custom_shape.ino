/* Example code for TM1637 4 digit 7 segment display with Arduino. More info: www.www.makerguides.com */

// Include the library:
#include <TM1637Display.h>

// Define the connections pins:
#define CLK 4
#define DIO 15

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);

// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};

// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
    SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,         // d
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
    SEG_C | SEG_E | SEG_G,                         // n
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G          // E
};

// Create degree Celsius symbol:
const uint8_t celsius[] = {
    SEG_A | SEG_B | SEG_F | SEG_G, // Circle
    SEG_A | SEG_D | SEG_E | SEG_F  // C
};

void setup()
{
    Serial.begin(115200);
    // Clear the display:
    display.setBrightness(7);
    display.clear();
    delay(1000);
}

void loop()
{
    int temperature = 24;
    display.showNumberDec(temperature, false, 2, 0);
    display.setSegments(celsius, 2, 2);
    delay(3000);

    display.setSegments(done);
    delay(3000);
}