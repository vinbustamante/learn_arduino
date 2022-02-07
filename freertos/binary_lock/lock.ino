#define BUTTON_PIN 0

static SemaphoreHandle_t lock;

static void say_hello(void * argp) {
    for(;;) {
        auto rc = xSemaphoreTake(lock, portMAX_DELAY);
        assert(rc == pdPASS);
        Serial.println("Hello world");
    }
}

static void allow_send(void * argp) {
    pinMode(BUTTON_PIN, INPUT);
    for(;;) {
        int state = digitalRead(BUTTON_PIN);       
        if (state == 0) {
            delay(100);
            int checkState = digitalRead(BUTTON_PIN);
            if (state == checkState) {
                auto rc = xSemaphoreGive(lock);
                assert(rc == pdPASS);
            }
        }
    }
    
}

void setup()
{
    Serial.begin(115200);
    delay(500);
    lock = xSemaphoreCreateBinary();
    auto rc = xTaskCreatePinnedToCore(
        say_hello,
        "say_hello",
        2048,
        nullptr,
        1,
        nullptr,
        1
    );
    rc = xTaskCreatePinnedToCore(
        allow_send,
        "allow_send",
        2048,
        nullptr,
        1,
        nullptr,
        1
    );
}

void loop()
{
	vTaskDelete(nullptr);
}
