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
    if (Serial.available())
    {
        // display.clear();
        String inputValue = Serial.readString();
        if (inputValue == "clear")
        {
            display.clear();
        }
        else
        {
            int value = inputValue.toInt();
            display.showNumberDec(value, true, 4, 0);
        }
        Serial.println(inputValue);
    }
}