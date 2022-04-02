/* Example code for TM1637 4 digit 7 segment display with Arduino. More info: www.www.makerguides.com */

// Include the library:
#include <TM1637Display.h>

// Define the connections pins:
#define CLK 4
#define DIO 15

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);

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
    int counter = 1;
    for (int counter = 1; counter < 10000; counter++)
    {
        display.showNumberDec(counter, true, 4, 0);
        delay(100);
    }
    delay(5000);
}