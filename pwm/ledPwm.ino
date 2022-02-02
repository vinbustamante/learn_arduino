const int LED = 2;

// PWM SETTINGS
const int freq = 5000;
int ledChannel = 0;
int resolution = 8;



void setup()
{
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(LED, ledChannel);
}

void loop()
{
	for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
        ledcWrite(ledChannel, dutyCycle);
        delay(15);
    }    
    for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
        ledcWrite(ledChannel, dutyCycle);
        delay(15);
    }
    delay(5000);
}
