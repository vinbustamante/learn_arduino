#include <PubSubClient.h>
#include <WiFi.h>
#define ledPin 2

// Replace the next variables with your SSID/Password combination
#define WIFI_SSID "redsoft"
#define WIFI_PASSWORD ""
#define TOPIC "esp32/output"
const char* mqtt_server = "192.168.1.33";

WiFiClient espClient;
PubSubClient client;
long lastMsg = 0;
char msg[50];
int value = 0;
bool is_wifi_connected = false;

void setup()
{
	  Serial.begin(115200);    
    pinMode(ledPin, OUTPUT);
    setup_wifi();
}

void loop()
{    
    if (is_wifi_connected) {
      if (client.connected() == false) {
        client.setClient(espClient);
        client.setServer("192.168.1.33",1883);
        client.setCallback(on_message_arrive);
        client.connect("esp-client", "gatewayuser", WIFI_PASSWORD);
        while (client.connected() == false) {
            Serial.println("attempting to connect....");
            delay(500);
        }
        client.subscribe(TOPIC);
        Serial.println("sucessfully conncted");
      } else {
        client.loop();
      }      
    }
}

void setup_wifi() {
   WiFi.onEvent(WiFiEvent);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}


void WiFiEvent(WiFiEvent_t event) { 
    Serial.printf("[WiFi-event] event: %d\n", event); 
    switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            is_wifi_connected = true;
            Serial.println("WiFi connected");
            Serial.println(WiFi.macAddress());
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            is_wifi_connected = false;
            Serial.println("WiFi lost connection");
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
            break;
    }
}

void on_message_arrive(char* topic, byte* message, unsigned int length) {
  String messageTemp;  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  if (String(topic) == "esp32/output") {
    if(messageTemp == "on"){
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      digitalWrite(ledPin, LOW);
    }
  }
}
