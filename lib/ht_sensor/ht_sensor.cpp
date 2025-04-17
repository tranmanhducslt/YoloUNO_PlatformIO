#include "ht_sensor.h"

DHT20 dht20;
int sensorStatus = 0;

float temperature = 0.0f;
float humidity = 0.0f;

void HTSensor_Read(){
    switch(sensorStatus){
        case 0:
            sensorStatus = 1;
            Wire.begin(GPIO_NUM_11, GPIO_NUM_12); 
            Serial.begin(115200); // Initialise serial communication
            dht20.begin();
        case 1:
            temperature = dht20.getTemperature();
            humidity = dht20.getHumidity();
            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.print(" °C, Humidity: ");
            Serial.print(humidity);
            Serial.println(" %");
            sensorStatus = 1;
            break;
        default:
            sensorStatus = 0;
            break;
    }
}