#define BUTTON_PIN_BITMASK 0x200000000
#define LED 10
RTC_DATA_ATTR int bootCount = 0;


void print_wakeup_reason(){
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    switch(wakeup_reason)
    {
        case 1 : 
            Serial.println("Wakeup caused by external signal using RTC_IO"); 
            break;
        case 2 : 
            Serial.println("Wakeup caused by external signal using RTC_CNTL"); 
            digitalWrite(LED, HIGH);
            delay(500);
            digitalWrite(LED, LOW);
            break;
        case 3 : 
            Serial.println("Wakeup caused by timer"); 
            break;
        case 4 : 
            Serial.println("Wakeup caused by touchpad"); 
                break;
        case 5 : 
            Serial.println("Wakeup caused by ULP program"); 
            break; 
        default : 
            Serial.println("Wakeup was not caused by deep sleep"); 
            break;
    } 
}



void setup()
{
	Serial.begin(115200);
    delay(1000); //Take some time to open up the Serial Monitor
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    Serial.println("Boot number: " + String(++bootCount));

    print_wakeup_reason();
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 0); //1 = High, 0 = Low
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, 0); //1 = High, 0 = Low
    Serial.println("Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
}

void loop()
{
	
}
