#include <stdio.h>
#include <stdlib.h>

#define ADC_PATH "/sys/bus/iio/devices/iio\:device0/"
#define AIN "in_voltage0_raw"
#define FIXED_RESISTOR 10000.0

float readADC(char *adcChannelPath) {
    FILE *fd;
    char valueStr[10];
    float value;

    fd = fopen(adcChannelPath, "r");
    if (fd == NULL) {
        perror("Failed to open ADC channel");
        exit(1);
    }

    if (fgets(valueStr, sizeof(valueStr), fd) != NULL) {
        value = atof(valueStr);
    } else {
        perror("Failed to read ADC value");
        fclose(fd);
        exit(1);
    }

    fclose(fd);
    return value;
}

void light_sensor_init(float* adc) {
    char adcChannelPath[100];
    float raw_value, voltage, ldr_resistance;

    // Constructing adc channel path
    snprintf(adcChannelPath, sizeof(adcChannelPath), "%s%s", ADC_PATH, AIN);

    // Raw ADC value
    raw_value = readADC(adcChannelPath);

    *adc = raw_value;

}