import machine
import time

LED_PIN = 0

led = machine.Pin(LED_PIN, machine.Pin.OUT)

while True:
    led.toggle()
    time.sleep(0.5)
