const int LED = 15;
// const int BUTTON = 0;
const int BUTTON = 15;
int buttonState = 0;
int touchValue;
const int THRESHOLD = 20;

void setup()
{
	Serial.begin(115200);
    pinMode(LED, OUTPUT);
    // pinMode(BUTTON, INPUT);
}

void loop()
{

    // int newState = digitalRead(BUTTON);
    // if (newState != buttonState) {
    //     buttonState = newState;
    //     digitalWrite(LED, buttonState);
    //     if (buttonState == HIGH) {
    //         Serial.println("button is off");
    //     } else {
    //         Serial.println("button is press");
    //     }        
    // }
    // touchValue = touchRead(BUTTON);
    // if (touchValue < THRESHOLD) {
    //     digitalWrite(LED, HIGH);
    //     Serial.println("LED IS ON");
    // } else {
    //     digitalWrite(LED, LOW);
    //     Serial.println("LED IS OFF");
    // }
    // delay(100);
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
}
