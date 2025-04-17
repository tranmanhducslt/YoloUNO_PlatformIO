#include "scheduler.h"
#include "ht_sensor.h"
#include "softwareTimer.h"
#include "Arduino.h"

void setup(){
    SCH_Init();
    timerInit();
    SCH_Add_Task(HTSensor_Read, 0, 5000); // Read sensor every 5 seconds
}

void loop(){
    SCH_Update();
    SCH_Dispatch_Tasks();
    delay(10); // Prevent watchdog timer reset
}