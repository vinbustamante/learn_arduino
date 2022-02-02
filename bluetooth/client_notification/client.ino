#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "BLEDevice.h"

#define bleServerName "ESP32"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
//UUID's of the service, characteristic that we want to read and characteristic that we want to write.
static BLEUUID serviceId("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID charactericId("beb5483e-36e1-4688-b7f5-ea07361b26a8");

//Address of the peripheral device. Address will be found during scanning... Hopefully.
static BLEAddress *pServerAddress;

static BLERemoteCharacteristic* counterCharacteristic;
bool newValue = false;
char* counterValue;

bool connectToServer(BLEAddress pAddress) {
   BLEClient* pClient = BLEDevice::createClient();
   // Connect to the remove BLE Server. 
   pClient->connect(pAddress);
   Serial.println(" - Connected to server");
   // Obtain a reference to the service we are after in the remote BLE server.
   BLERemoteService* pRemoteService = pClient->getService(serviceId);
   if (pRemoteService == nullptr) {
        Serial.print("Failed to find our service UUID: "); 
        Serial.println(pAddress.toString().c_str()); 
        return (false);        
    }
    // Obtain a reference to the characteristics in the service of the remote BLE server.
    counterCharacteristic = pRemoteService->getCharacteristic(charactericId);
    if (counterCharacteristic == nullptr) {
        Serial.print("Failed to find our characteristic UUID");
        return false;
    }
    counterCharacteristic->registerForNotify(counterCharacteristicCallback);
}

//Callback function that gets called, when another advertisement has been received
class MyAdvertisedDeviceCallbacks: BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        //Check if the name of the advertiser matches
        if (advertisedDevice.getName() == bleServerName) {
            //Scan can be stopped, we found what we are looking for
            advertisedDevice.getScan()->stop();

            //Address of advertiser is the one we need
            pServerAddress = new BLEAddress(advertisedDevice.getAddress());
            Serial.println("Device found. Connecting!");
        }
    }
};


//When the BLE Server sends a new temperature reading with the notify property
static void counterCharacteristicCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    counterValue = (char*)pData;
    newValue = true;
}

void displayValue() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print("Counter: ");
    display.setCursor(0, 20);
    display.print(counterValue);
    Serial.print("Counter: ");
    Serial.println(counterValue);
}

void setup()
{
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(1);
    // display.setTextColor(WHITE,0);
    display.setCursor(0,0);
    display.print("INITIALISATION");
    display.display();
    //Start serial communication
    Serial.begin(115200);
    Serial.println("Starting Arduino BLE Client application...");
}

void loop()
{
	
}
