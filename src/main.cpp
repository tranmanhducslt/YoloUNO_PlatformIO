#include "scheduler.h"
#include "DHT20.h"
#include "softwareTimer.h"
#include "Arduino.h"

void setup(){
    SCH_Init();
    timerInit();

    Wire.begin(4, 5); // Initialize I2C with data and clock pins
    Serial.begin(115200);
    delay(1000); 

    SCH_Add_Task([]() {
        static DHT20 dht20;
        static bool initialized = false;
        if (!initialized) {
            dht20.begin(4, 5); // Initialize DHT20 with data and clock pins
            initialized = true;
        }
        int status = dht20.read();
        if (status == DHT20_OK) {
            Serial.print("Temperature: ");
            Serial.print(dht20.getTemperature());
            Serial.print(" °C, Humidity: ");
            Serial.print(dht20.getHumidity());
            Serial.println(" %");
        } else {
            Serial.print("Error reading DHT20: ");
            Serial.println(status);
        }
    }, 5000, 5000); // Schedule measuring every 5 seconds

    SCH_Add_Task([]() {
        static int ledState = LOW;
        ledState = !ledState; // Toggle LED state
        digitalWrite(LED_BUILTIN, ledState); // Set LED state
    }, 500, 500); // Schedule LED toggle every .5 seconds
}

void loop(){
    SCH_Update();
    SCH_Dispatch_Tasks();
    delay(10); // Prevent watchdog timer reset
}