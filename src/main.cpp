#include "scheduler.h"
#include "DHT20.h"
#include "softwareTimer.h"
#include "Arduino.h"

void setup(){
    SCH_Init();
    timerInit();

    Wire.begin(GPIO_NUM_11, GPIO_NUM_12); // Initialize I2C with data and clock pins
    Serial.begin(115200);
    delay(100); // Wait for serial connection

    SCH_Add_Task([]() { // Schedule a task to read sensor data every 2 seconds
        static DHT20 dht20(&Wire); // Create DHT20 object with I2C interface
        if (dht20.begin() == DHT20_OK) { // Initialize the sensor
            if (dht20.read() == DHT20_OK) { // Read sensor data
                Serial.print("Temperature: ");
                Serial.print(dht20.getTemperature()); // Print temperature
                Serial.print(" °C, Humidity: ");
                Serial.print(dht20.getHumidity()); // Print humidity
                Serial.println(" %");
            } else {
                Serial.println("Failed to read from DHT20 sensor!");
            }
        } else {
            Serial.println("Failed to initialize DHT20 sensor!");
        }
    }, 0, 5000); // Schedule task to run immediately and then every 5 seconds
}

void loop(){
    SCH_Update();
    SCH_Dispatch_Tasks();
    delay(10); // Prevent watchdog timer reset
}