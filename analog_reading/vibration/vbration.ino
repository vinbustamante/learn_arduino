#define POT_PIN 15

void setup()
{
	Serial.begin(115200);
    delay(1000);
    pinMode(POT_PIN, INPUT_PULLDOWN);
}

void loop()
{	
    // int reading = map(analogRead(POT_PIN), 0, 4095, 0, 255);
    Serial.println(analogRead(POT_PIN));
    delay(500);
}
