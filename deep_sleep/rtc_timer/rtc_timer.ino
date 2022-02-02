/* Conversion factor for micro seconds to seconds */
#define uS_TO_S_FACTOR 1000000

/* Time ESP32 will go to sleep (in seconds) */
#define TIME_TO_SLEEP 5

// RTC_DATA_ATTR int bootCount = 0;
 RTC_DATA_ATTR int bootCount = 0;

void print_wakeup_reason() {
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    switch (wakeup_reason) {
        case ESP_SLEEP_WAKEUP_EXT0:
            Serial.println("Wakeup caused by external signal using RTC_IO"); 
            break;
        case ESP_SLEEP_WAKEUP_EXT1 : 
            Serial.println("Wakeup caused by external signal using RTC_CNTL"); 
            break;
        case ESP_SLEEP_WAKEUP_TIMER : 
            Serial.println("Wakeup caused by timer"); 
            break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD : 
            Serial.println("Wakeup caused by touchpad"); 
            break;
        case ESP_SLEEP_WAKEUP_ULP : 
            Serial.println("Wakeup caused by ULP program"); 
            break;
        default : 
            Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); 
            break;
    }
}


void setup()
{
    Serial.begin(115200);
    // allow serial to setup
    delay(1000);
    Serial.println("Boot Nubmer: " + String(++bootCount));
    print_wakeup_reason();
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +" Seconds");

    // esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);

    Serial.println("Going to sleep now");
    Serial.flush();
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}

void loop()
{
	
}
