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
    char greeting[] = "Hello World";
    printf("%s", greeting);

    temp_init();
    light_init();
    //server_init();
    //task_scheduling_init();
}