#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "light_actuator.h"

void pwm_light(int intensity)
{
    if (intensity < 0) intensity = 0;
    if (intensity > 100) intensity = 100;

    int period = 20000000; // (20ms)
    
    // PWM pin configuration
    int config_result = system("config-pin P9_14 pwm > /dev/null 2>&1");
    if (config_result != 0) {
        fprintf(stderr, "Failed to configure P9_14 as PWM\n");
        exit(1);
    }

    // Duty cycle based on intensity
    int duty_cycle = (intensity * period) / 100;

    // PWM period
    int period_result = system("sudo sh -c 'echo 20000000 > /dev/bone/pwm/1/a/period'");
    if (period_result != 0) {
        fprintf(stderr, "Failed to set PWM period\n");
        exit(1);
    }

    // Setting duty cycle
    char duty_cycle_cmd[100];
    snprintf(duty_cycle_cmd, sizeof(duty_cycle_cmd), "sudo sh -c 'echo %d > /dev/bone/pwm/1/a/duty_cycle'", duty_cycle);

    // Executing duty cycle command
    int duty_result = system(duty_cycle_cmd);
    if (duty_result != 0) {
        fprintf(stderr, "Failed to set PWM duty cycle\n");
        exit(1);
    }

    // Enable PWM
    int enable_result = system("sudo sh -c 'echo 1 > /dev/bone/pwm/1/a/enable'");
    if (enable_result != 0) {
        fprintf(stderr, "Failed to enable PWM\n");
        exit(1);
    }
}

void light_actuator_init(int intensity)
{
    pwm_light(intensity);
}
