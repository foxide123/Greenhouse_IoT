#include "server.h"
#include "temperature.h"
#include <stdio.h>


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
    //server_init();
    //task_scheduling_init();
}