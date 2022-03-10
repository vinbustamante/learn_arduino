#define GPIO_BUTTON 0
#define GPIO_LED 2
#define TASK_PRIORITY 1

static QueueHandle_t queue;

static void button_task(void *argp) {
    bool state;
    bool toggle = false;
    for(;;) {        
        int isPress = digitalRead(GPIO_BUTTON) == 0;
        if (isPress) {
            delay(100);
            if (digitalRead(GPIO_BUTTON) == 0) {
                state = !toggle;
                Serial.printf("Sending to queue %s\n", String(state));
                if (xQueueSendToBack(queue, &state, 1) == pdPASS) {
                    toggle = state;
                }
            }
        }        
    }
}

static void led_task(void *argp) {
    BaseType_t rc;
    bool state, led = false;

    digitalWrite(GPIO_LED, LOW);
    for(;;) {
        rc = xQueueReceive(queue, &state, portMAX_DELAY);
        assert(rc == pdPASS);
        Serial.printf("Received from queue %s\n", String(state));
        digitalWrite(GPIO_LED, state);        
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    int app_cpu = xPortGetCoreID();
    TaskHandle_t h;
    BaseType_t rc;

    delay(2000);
    queue = xQueueCreate(40, sizeof(bool));
    assert(queue);

    pinMode(GPIO_LED, OUTPUT);
    pinMode(GPIO_BUTTON, INPUT_PULLDOWN);

    rc = xTaskCreatePinnedToCore(
        button_task,
        "debounce",
        2048,
        nullptr,
        TASK_PRIORITY,
        &h,
        app_cpu
    );
    assert(rc == pdPASS);
    assert(h);

    rc = xTaskCreatePinnedToCore(
        led_task,
        "led",
        2048,
        nullptr,
        TASK_PRIORITY,
        &h,
        app_cpu
    );
    assert(rc == pdPASS);
    assert(h);
}

void loop()
{
	vTaskDelete(nullptr);
}
