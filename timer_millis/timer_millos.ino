const int LED = 2;
// const int MOTION_PIN = 4;
const int MOTION_PIN = 16;
int ledState = LOW;
unsigned long previousMillis = 0;
int interval = 1000;
const int DURATION = 5000;

unsigned long now = millis();
unsigned lastTrigger = 0;
boolean startTimer = false;

void IRAM_ATTR detectMovement() {
    Serial.println("MOTION DETECTED");
    digitalWrite(LED, HIGH);
    startTimer = true;
    lastTrigger = millis();
}


void setup()
{
    Serial.begin(115200);
    // pinMode(MOTION_PIN, INPUT);

    pinMode(MOTION_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(MOTION_PIN), detectMovement, FALLING);

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}

void loop()
{
	unsigned now = millis();
    if (startTimer && (now - lastTrigger > (DURATION))) {
        Serial.println("MOTION STOP");
        digitalWrite(LED, LOW);
        startTimer = false;
    }
    /* if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if (ledState == LOW) {
            ledState = HIGH;
        } else {
            ledState = LOW;
        }
        digitalWrite(LED, ledState);
    }*/
}
