#pragma once

#include "Arduino.h"
#include "DHT20.h"
#include "scheduler.h"
#include "softwareTimer.h"

extern float temperature;
extern float humidity;

void ht_sensor_init(uint8_t i2c_address, uint8_t pin, uint8_t type, uint32_t interval);
void ht_sensor_read(void);