#pragma once

#include "Arduino.h"
#include "DHT20.h"
#include "scheduler.h"
#include "softwareTimer.h"

extern float temperature;
extern float humidity;

void HTSensor_Read(void);