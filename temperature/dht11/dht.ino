#include <Adafruit_Sensor.h>
#include <DHT.h>
#define TEMPERATURE_PIN 15
#define TEMPERATURE_TYPE DHT11

DHT temperature_sensor(TEMPERATURE_PIN, TEMPERATURE_TYPE);



void setup()
{
    Serial.begin(115200);
    temperature_sensor.begin();
}

void loop()
{
	Serial.println("Temperature: " + String(temperature_sensor.readTemperature()));
    Serial.println("Humidity: " + String(temperature_sensor.readHumidity()));
    delay(2000);
}
