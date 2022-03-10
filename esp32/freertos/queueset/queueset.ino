// LED GPIOs:
#define GPIO_LED1     15
#define GPIO_LED2     4
#define GPIO_LED3     16

// Button GPIOs:
#define GPIO_BUTTON1     13
#define GPIO_BUTTON2     12
#define GPIO_BUTTON3     14

#define Threshold     20
#define N_BUTTONS     3
#define Q_DEPTH       8

// ISR Routines, forward decls:
static void IRAM_ATTR isr_gpio1();
static void IRAM_ATTR isr_gpio2();
static void IRAM_ATTR isr_gpio3();

typedef void (*isr_t)();    // ISR routine type


static struct s_button {
    int button_gpio;
    int led_gpio;
    QueueHandle_t qh;
    isr_t   isr; // ISR ROUTINE
} buttons[N_BUTTONS] = {
    { GPIO_BUTTON1, GPIO_LED1, nullptr, isr_gpio1 },
    { GPIO_BUTTON2, GPIO_LED2, nullptr, isr_gpio2 },
    { GPIO_BUTTON3, GPIO_LED3, nullptr, isr_gpio3 }
};

static void evtask(void *arg) {
    QueueSetHandle_t hqset = (QueueSetHandle_t*)arg;
    QueueSetMemberHandle_t mh;
    bool state;
    BaseType_t rc;

    for(;;){
        mh = xQueueSelectFromSet(hqset, portMAX_DELAY);
        for(unsigned ux=0;ux<N_BUTTONS;++ux) {
            s_button& button = buttons[ux];
            if (mh == button.qh) {
                rc = xQueueReceive(mh, &state, 0);
                assert(rc == pdPASS);
                digitalWrite(button.led_gpio, state);
            }
        }
    }
}

inline static BaseType_t IRAM_ATTR isr_gpiox(uint8_t gpiox) {
    s_button& button = buttons[gpiox];
    int value = touchRead(buttons->button_gpio);
    Serial.println(value);
    bool state = value <=  Threshold;

    BaseType_t woken = false;

    (void)xQueueSendFromISR(button.qh, &state, &woken);
    return woken;
}

// BUTTON 1
static void IRAM_ATTR isr_gpio1() {    
     Serial.println("button 2");
    if (isr_gpiox(0)) {
        portYIELD_FROM_ISR();
    }
}

// BUTTON 2
static void IRAM_ATTR isr_gpio2() {
    Serial.println("button 2");
    if (isr_gpiox(1)) {
        portYIELD_FROM_ISR();
    }
}

// button 3
static void IRAM_ATTR isr_gpio3() {
    Serial.println("button 3");
    if (isr_gpiox(2)) {
        portYIELD_FROM_ISR();
    }
}

void setup()
{
    Serial.begin(115200);
	int app_cpu = xPortGetCoreID();
    QueueSetHandle_t hqset;
    BaseType_t rc;

    hqset = xQueueCreateSet(Q_DEPTH * N_BUTTONS);
    assert(hqset);
    
    for(unsigned ux=0;ux<N_BUTTONS;++ux) {
        s_button& button = buttons[ux];
        button.qh = xQueueCreate(Q_DEPTH, sizeof(bool));
        assert(button.qh);
        rc = xQueueAddToSet(button.qh, hqset);
        assert(rc == pdPASS);
        pinMode(button.led_gpio, OUTPUT);
        digitalWrite(button.led_gpio, HIGH);
        pinMode(button.button_gpio, INPUT_PULLUP);
        touchAttachInterrupt(button.button_gpio, button.isr, Threshold);
    }

    // start the task
    rc = xTaskCreatePinnedToCore(
        evtask,
        "evtask",
        4096, // stack size
        (void *) hqset, // argument
        1, // priority
        nullptr,
        app_cpu
    );
    assert(rc == pdPASS);
}

void loop()
{
    // vTaskDelete(nullptr);
}
