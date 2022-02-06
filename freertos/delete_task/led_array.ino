#define LED1  15
#define LED2  4 
#define LED3  16
#define TASK_PRIORITY 1
#define TASK_NAME "led_task"
#define TASK_STACK_SIZE 2048

struct s_led {
    byte pin;
    byte state;
    unsigned delay;
    TaskHandle_t taskh;
};

static s_led leds[3] = {
    {LED1, 0, 500, 0},
    {LED2, 0, 200, 0},
    {LED3, 0, 750, 0}
};

static void led_task_func(void *argp) {
    s_led *ledp = (s_led*)argp;

    Serial.printf("GPIO %d \n", ledp->pin);

    unsigned stack_hwm = 0, temp;
    delay(1000);    
    for(;;) {
        digitalWrite(ledp->pin, ledp->state ^=1);
        temp = uxTaskGetStackHighWaterMark(ledp->taskh);
        if ( !stack_hwm || temp < stack_hwm ) {
            stack_hwm = temp;
            printf("Task for gpio %d has stack hwm %u\n", ledp->pin, stack_hwm);
        }
        delay(ledp->delay);
    }
}


void setup()
{
    Serial.begin(115200);
	int app_cpu = 0;  // CPU number
    delay(500);       // Pause for serial setup
    app_cpu = xPortGetCoreID();
    Serial.printf("app_cpu is %d (%s core)\n",  app_cpu, app_cpu > 0 ? "Dual" : "Single");
    Serial.printf("LEDs on gpios: ");
    for (auto &led : leds ) {
        pinMode(led.pin, OUTPUT);
        digitalWrite(led.pin, LOW);
        xTaskCreatePinnedToCore(
            led_task_func,
            TASK_NAME,
            TASK_STACK_SIZE,
            &led, // TASK PARAMETER
            TASK_PRIORITY,
            &led.taskh, // task handle
            app_cpu 
        );
        Serial.printf("%d ",led.pin);
    }
    putchar('\n');     
}

void loop()
{
    Serial.println("main task executing");
    vTaskDelete(nullptr);
   
	delay(1000);
}
