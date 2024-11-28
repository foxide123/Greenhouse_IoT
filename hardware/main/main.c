#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "temperature.h"
#include "light_sensor.h"
#include "light_actuator.h"
//#include "light_sensor.h"


void systemSetup(void);

int main(void)
{
    systemSetup();
}

void systemSetup(void)
{
    float temperature, humidity, adc;

    temp_init(&temperature, &humidity);
    light_sensor_init(&adc);
    light_actuator_init(50);

    char* json_data = malloc(256);
    snprintf(json_data, 256, "{\"temperature\":%.2f, \"humidity\":%.2f, \"adc\": %.0f}", temperature, humidity, adc);

    printf("%s\n", json_data);
}