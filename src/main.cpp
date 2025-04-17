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
}

void loop(){
    SCH_Update();
    SCH_Dispatch_Tasks();
    delay(10); // Prevent watchdog timer reset
}