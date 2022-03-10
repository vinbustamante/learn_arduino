#define GPIO 17

static void gpio_on(void *argp) {
    for(;;) {
        digitalWrite(GPIO, HIGH);
    }
}

static void gpio_off(void *argp) {
    for(;;) {
        digitalWrite(GPIO, LOW);
    }
}

void setup()
{
	int cpuId = xPortGetCoreID();
    pinMode(GPIO, OUTPUT);
    delay(1000);
    printf("Setup started..\n");
    xTaskCreatePinnedToCore(
        gpio_on,
        "gpio_on",
        2048,
        nullptr,
        1,
        nullptr,
        cpuId
    );
    xTaskCreatePinnedToCore(
        gpio_off,
        "gpio_off",
        2048,
        nullptr,
        1,
        nullptr,
        cpuId
    );
}

void loop()
{
	vTaskDelete(xTaskGetCurrentTaskHandle());
}
