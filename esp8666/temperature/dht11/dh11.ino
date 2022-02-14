#include <DHT.h>
#define DHT_PIN 2
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHT_PIN, DHTTYPE);

void setup()
{
    dht.begin();
    Serial.begin(115200);
}

void loop()
{
    float newT = dht.readTemperature();
    Serial.print("temp : ");
    Serial.println(newT);

    float newH = dht.readHumidity();
    Serial.print("hump : ");
    Serial.println(newH);
    delay(1000);
}
