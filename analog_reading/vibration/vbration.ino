const int analogInPin = A0;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    // pinMode(A0, INPUT);
}

void loop()
{
    // int reading = map(analogRead(POT_PIN), 0, 4095, 0, 255);
    Serial.println(analogRead(A0));
    delay(500);
}
