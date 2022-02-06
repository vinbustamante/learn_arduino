#define LED 15
#define PERIOD_MS 1000

class AlertLed {
    TimerHandle_t thandle = nullptr;
    volatile bool state;
    volatile unsigned count;
    unsigned period_ms;
    int gpio;
    void reset(bool s);

    public:
        AlertLed(int gpio, unsigned period_ms = 1000);
        void alert();
        void cancel();

        static void callback(TimerHandle_t th);
};

AlertLed::AlertLed(int gpio, unsigned period_ms) {
    this->gpio = gpio;
    this->period_ms = period_ms;
    pinMode(this->gpio, OUTPUT);
    digitalWrite(this->gpio, LOW);
}

void AlertLed::reset(bool s) {
    this->state = s;
    this->count = 0;
    digitalWrite(this->gpio, s?HIGH:LOW);
}

void AlertLed::alert() {
    if (!this->thandle) {
        thandle = xTimerCreate(
            "alert_tmr",
            pdMS_TO_TICKS(this->period_ms/20),
            pdTRUE,
            this,
            AlertLed::callback
        );
        assert(thandle);
    }
    this->reset(true);
    xTimerStart(this->thandle, portMAX_DELAY);
}

void AlertLed::cancel() {
    if (thandle) {
        xTimerStop(thandle, portMAX_DELAY);
        digitalWrite(gpio, LOW);
    }
}

void AlertLed::callback(TimerHandle_t th) {
    AlertLed *obj = (AlertLed*)pvTimerGetTimerID(th);
    assert(obj->thandle == th);
    obj->state ^= true;
    Serial.println(obj->state);
    digitalWrite(obj->gpio, obj->state ? HIGH : LOW);
    if ( ++obj->count >= 5 * 2 ) {
        obj->reset(true);
        xTimerChangePeriod(th, pdMS_TO_TICKS(obj->period_ms/20),portMAX_DELAY);
    } else if(obj->count == 5 * 2 - 1) {
         xTimerChangePeriod(th,pdMS_TO_TICKS(obj->period_ms/20+obj->period_ms/2),portMAX_DELAY);
         assert(!obj->state);
    }
}

static AlertLed alert1(LED, PERIOD_MS);
static AlertLed alert2(4, PERIOD_MS);
static AlertLed alert3(16, PERIOD_MS);
static unsigned loop_count = 0;

void setup()
{
    Serial.begin(115200);
    delay(500);
	alert1.alert();
    alert2.alert();
    alert3.alert();
}

void loop()
{
	if (loop_count >= 70) {
        alert1.alert();
        alert2.alert();
        alert3.alert();
        loop_count = 0;
    }

    delay(1000);

    if (++loop_count >= 50) {
        alert1.cancel();
        alert2.cancel();
        alert3.cancel();
    }
}
