#include <WiFi.h>
#define WIFI_SSID "redsoft"
#define WIFI_PASSWORD ""

void setup()
{
	Serial.begin(115200);
    Serial.println("connecting to wifi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.onEvent(WiFiEvent);
}

void loop()
{
	
}

void WiFiEvent(WiFiEvent_t event) { Serial.printf("[WiFi-event] event: %d\n", event); switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection"); 
        break;
} }
