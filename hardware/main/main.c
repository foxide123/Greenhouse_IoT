#include <stdio.h>
#include "server.h"
#include "temperature.h"
#include "light_actuator"
#include "light_sensor"


void systemSetup(void);

int main(void)
{
    systemSetup();
}

void systemSetup(void)
{
    char* temp_hum_data = temp_init();
    light_init();
    
}