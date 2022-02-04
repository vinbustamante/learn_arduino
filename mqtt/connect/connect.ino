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
bool is_mqtt_connected = false;

void setup()
{
	Serial.begin(115200);    
    pinMode(ledPin, OUTPUT);
    setup_wifi();
}

void loop()
{
    if (is_wifi_connected && is_mqtt_connected == false) {
        client.setClient(espClient);
        client.setServer("192.168.1.33",1883);
        client.setCallback(on_message_arrive);
        client.connect("esp-client", "gatewayuser", WIFI_PASSWORD);
        while (client.connected() == false) {
            Serial.println("attempting to connect....");
            delay(500);
        }
        is_mqtt_connected = true;
        client.subscribe(TOPIC);
        Serial.println("sucessfully conncted");
    }
    client.loop();
}

void setup_wifi() {
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   WiFi.onEvent(WiFiEvent);
}


void WiFiEvent(WiFiEvent_t event) { 
    Serial.printf("[WiFi-event] event: %d\n", event); 
    switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            is_wifi_connected = true;
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            is_wifi_connected = false;
            Serial.println("WiFi lost connection"); 
            break;
    }
}

void on_message_arrive(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);  
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.println(". Message: " + messageTemp);

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}